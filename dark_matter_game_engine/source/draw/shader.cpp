//*************************************************************************
// DarkMatter OpenGL 3D Engine Framework
// Class Name: Shader
// Source File: [shader.cpp]
//
// License:
// Copyright(C) <2018>  <https://github.com/3dsekai/>
//
// This program is free software : you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.If not, see <https://www.gnu.org/licenses/>.
//*************************************************************************

#define	_CRT_SECURE_NO_WARNINGS
//*************************************************************************
// Includes
//*************************************************************************
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shader.h"

//*************************************************************************
// Class: Shader
// Function Name: Shader
// Explanation: Shader Class constructor
// Other: -
//*************************************************************************
Shader::Shader()
{
	_program = 0;
	std::fill(_shader, _shader + ALL_SHADERS, 0);
}

//*************************************************************************
// Class: Shader
// Function Name: Shader
// Explanation: Shader Class constructor
// Other: -
//*************************************************************************
Shader::~Shader()
{
	//delete program object
	if(_program != 0)
	{
		glDeleteProgram(_program);
	}

	//delete shaders objects
	for(int i = 0; i < ALL_SHADERS; i++)
	{
		if(_shader[i] != 0)
		{
			glDeleteShader(_shader[i]);
		}
	}
}

//*************************************************************************
// Class: Shader
// Function Name: CreateProgram
// Explanation: create the program object for the shader
// Other: -
//*************************************************************************
void Shader::CreateProgram()
{
	_program = glCreateProgram();
};

//*************************************************************************
// Class: Shader
// Function Name: InitializeShader
// Argument{s}:
// ShaderType type: the shader object type to initialize
// char* path: the full path to the shader file
// Explanation: initialize the shader object
// Other: -
//*************************************************************************
void Shader::InitializeShader(ShaderType type, const char* path)
{
	if(_program == 0) return;
	if(type >= ALL_SHADERS) return;

	char* src = ReadShaderFile(path);	//get the shader source code

	if(src != nullptr)
	{
		const GLchar* src_cpy = src;
		GLint compiled;
		GLchar info_log[256];
		GLenum gl_shader = GetGLShaderType(type);

		_shader[type] = glCreateShader(gl_shader);		//create the shader object
		glShaderSource(_shader[type], 1, &src, NULL);	//replace source code in shader object
		glAttachShader(_program, _shader[type]);	 	//attach shader object to program object
		glCompileShader(_shader[type]);				 	//compile shader

		//check for compile errors
		glGetShaderiv(_shader[type], GL_COMPILE_STATUS, &compiled);
		if(!compiled)
		{
			glGetShaderInfoLog(_shader[type], 256, nullptr, info_log);
			std::cout << "error: shader object compilation failed\n" << info_log << std::endl;
		}
	}
	free(src);
};

//*************************************************************************
// Class: Shader
// Function Name: DeleteShader
// Argument{s}:
// ShaderType type: the shader object type to delete
// Explanation: Delete the specified shader object
// Other: If type is set to ALL_SHADERS, all shader objects are deleted
//*************************************************************************
void Shader::DeleteShader(ShaderType type)
{
	if(type == ALL_SHADERS)
	{
		for(int i = 0; i < ALL_SHADERS; i++)
		{
			if(_shader[i] != 0)
			{
				glDeleteShader(_shader[i]);
			}
		}
	}
	else
	{
		if(_shader[type] != 0)
		{
			glDeleteShader(_shader[type]);
		}
	}
};

//*************************************************************************
// Class: Shader
// Function Name: LinkProgram
// Explanation: Links the program object (creates executables for any
// attached shader objects to run on the graphics processors)
// Other: -
//*************************************************************************
void Shader::LinkProgram()
{
	if(_program == 0) return;
	glLinkProgram(_program);

	//check for linking errors
	GLint linked;
	GLchar info_log[256];
	glGetProgramiv(_program, GL_LINK_STATUS, &linked);
	if(!linked)
	{
		glGetProgramInfoLog(_program, 256, nullptr, info_log);
		std::cout << "error: program object link failed\n" << info_log << std::endl;
	}
}
//*************************************************************************
// Class: Shader
// Function Name: UseProgram
// Explanation: uses the program object
// Other: -
//*************************************************************************
void Shader::UseProgram()
{
	if (_program == 0) return;
	glUseProgram(_program);
}

//*************************************************************************
// Class: Shader
// Function Name: Compile
// Argument{s}:
// const char* vertex_source: the full path to the vertex shader file
// const char* fragment_source: the full path to the fragment shader file
// const char* geometry_source: the full path to the geometry shader file
// Other: -
//*************************************************************************
void Shader::Compile(const char* vertex_source, const char* fragment_source, const char* geometry_source)
{
	//create the shader program object
	CreateProgram();

	//initialize the shader objects
	InitializeShader(Shader::VERTEX_SHADER, vertex_source);
	InitializeShader(Shader::FRAGMENT_SHADER, fragment_source);
	if(geometry_source != nullptr)
	{
		InitializeShader(Shader::FRAGMENT_SHADER, fragment_source);
	}

	//link the shader objects to the program object
	LinkProgram();

	//shaders are no longer needed - delete them
	DeleteShader(Shader::ALL_SHADERS);
}
//*************************************************************************
// Class: Shader
// Function Name: ReadShaderFile
// Argument{s}:
// const char* path: the full path to the shader file
// Explanation: read and store the contents of the specified shader file
// Other: -
//*************************************************************************
char* Shader::ReadShaderFile(const char* path)
{
	FILE *file_ptr = nullptr;
	char* buff = nullptr;
	size_t size = 0;
	size_t read_size = 0;

	if(path != "")
	{
		//open the file for reading
		file_ptr = fopen(path, "rt");
		if(file_ptr != nullptr)
		{
			//get the file's size
			fseek(file_ptr, 0, SEEK_END);
			size = ftell(file_ptr);
			rewind(file_ptr);

			if(size > 0)
			{
				//allocate enough memory for the file's contents
				buff = (char*)calloc(1, size + 1);
				if(buff != nullptr)
				{
					//copy file contents into buffer
					read_size = fread(buff, 1, size, file_ptr);
					if(read_size != size)
					{
						buff = nullptr;
					}
				}
			}
		}
		fclose(file_ptr);
	}
	return buff;
};

//*************************************************************************
// Class: Shader
// Function Name: GetGLShaderType
// Argument{s}:
// ShaderType type: the shader object type
// Explanation: gets the OpenGL enumerated shader type
// Other: returns GL_VERTEX_SHADER by default
//*************************************************************************
GLenum Shader::GetGLShaderType(ShaderType type)
{
	GLenum shader;
	switch(type)
	{
	case VERTEX_SHADER:
		shader = GL_VERTEX_SHADER;
		break;
	case GEOMETRY_SHADER:
		shader = GL_GEOMETRY_SHADER;
		break;
	case FRAGMENT_SHADER:
		shader = GL_FRAGMENT_SHADER;
		break;
	default:
		shader = GL_VERTEX_SHADER;
		break;
	}
	return shader;
}
//*************************************************************************
// Class: Shader
// Function Name: SetUniformFloat
// Argument{s}:
// float val: the value to set into the uniform
// const char* name: the name of the uniform variable
// Explanation: sets one float value [val] to the uniform variable [name]
//*************************************************************************
void Shader::SetUniformFloat(float val, const char* name)
{
	glUniform1f(glGetUniformLocation(_program, name), val);
}
//*************************************************************************
// Class: Shader
// Function Name: SetUniformInt
// Argument{s}:
// int val: the value to set into the uniform
// const char* name: the name of the uniform variable
// Explanation: sets one signed int value [val] to the uniform variable [name]
//*************************************************************************
void Shader::SetUniformInt(int val, const char* name)
{
	glUniform1i(glGetUniformLocation(_program, name), val);
}
//*************************************************************************
// Class: Shader
// Function Name: SetUniformUint
// Argument{s}:
// unsigned int val: the value to set into the uniform
// const char* name: the name of the uniform variable
// Explanation: sets one unsigned int value [val] to the uniform variable [name]
//*************************************************************************
void Shader::SetUniformUint(unsigned int val, const char* name)
{
	glUniform1ui(glGetUniformLocation(_program, name), val);
}
//*************************************************************************
// Class: Shader
// Function Name: SetUniformBool
// Argument{s}:
// bool val: the value to set into the uniform
// const char* name: the name of the uniform variable
// Explanation: sets one bool value [val] to the uniform variable [name]
//*************************************************************************
void Shader::SetUniformBool(bool val, const char* name)
{
	glUniform1i(glGetUniformLocation(_program, name), val);
}
//*************************************************************************
// Class: Shader
// Function Name: SetUniformVec2
// Argument{s}:
// Vec2 val: the value to set into the uniform
// const char* name: the name of the uniform variable
// Explanation: sets a 2d vector value [val] to the uniform variable [name]
//*************************************************************************
void Shader::SetUniformVec2(Vec2 val, const char* name)
{
	glUniform2f(glGetUniformLocation(_program, name), val.x, val.y);
}
//*************************************************************************
// Class: Shader
// Function Name: SetUniformVec3
// Argument{s}:
// Vec3 val: the value to set into the uniform
// const char* name: the name of the uniform variable
// Explanation: sets a 3d vector value [val] to the uniform variable [name]
//*************************************************************************
void Shader::SetUniformVec3(Vec3 val, const char* name)
{
	glUniform3f(glGetUniformLocation(_program, name), val.x, val.y, val.z);
}
//*************************************************************************
// Class: Shader
// Function Name: SetUniformVec4
// Argument{s}:
// Vec4 val: the value to set into the uniform
// const char* name: the name of the uniform variable
// Explanation: sets a 4d vector value [val] to the uniform variable [name]
//*************************************************************************
void Shader::SetUniformVec4(Vec4 val, const char* name)
{
	glUniform4f(glGetUniformLocation(_program, name), val.x, val.y, val.z, val.w);
}
//*************************************************************************
// Class: Shader
// Function Name: SetUniformMat3
// Argument{s}:
// Mat3 val: the value to set into the uniform
// const char* name: the name of the uniform variable
// Explanation: sets a 3x3 matrix [val] to the uniform variable [name]
//*************************************************************************
void Shader::SetUniformMat3(Mat3 val, const char* name)
{
	glUniformMatrix3fv(glGetUniformLocation(_program, name), 1, GL_FALSE, val.elem);
}
//*************************************************************************
// Class: Shader
// Function Name: SetUniformMat4
// Argument{s}:
// Mat4 val: the value to set into the uniform
// const char* name: the name of the uniform variable
// Explanation: sets a 4x4 matrix [val] to the uniform variable [name]
//*************************************************************************
void Shader::SetUniformMat4(Mat4 val, const char* name)
{
	glUniformMatrix4fv(glGetUniformLocation(_program, name), 1, GL_FALSE, val.elem);
}
