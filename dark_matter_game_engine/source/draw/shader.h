//*************************************************************************
// DarkMatter OpenGL 3D Engine Framework
// Class Name: Shader
// Source File: [shader.h]
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
#ifndef _SHADER_H_
#define _SHADER_H_

//*************************************************************************
// Includes
//*************************************************************************
#include <GL/glew.h>
#include "../math_lib/vec2.h"
#include "../math_lib/vec3.h"
#include "../math_lib/vec4.h"
#include "../math_lib/mat3.h"
#include "../math_lib/mat4.h"

//*************************************************************************
// Shader Class
//*************************************************************************
class Shader
{
public:
	enum ShaderType
	{
		VERTEX_SHADER = 0,
		GEOMETRY_SHADER,
		FRAGMENT_SHADER,
		ALL_SHADERS
	};

public:
	Shader();
	~Shader();

private:
	void CreateProgram();
	void InitializeShader(ShaderType type, const char* dir);
	void DeleteShader(ShaderType type);
	void LinkProgram();

public:
	void Compile(const char* vertex_source, const char* fragment_source, const char* geometry_source = nullptr);
	void UseProgram();

	void SetUniformFloat(float val, const char* name);
	void SetUniformInt(int val, const char* name);
	void SetUniformUint(unsigned int val, const char* name);
	void SetUniformBool(bool val, const char* name);
	void SetUniformVec2(Vec2 val, const char* name);
	void SetUniformVec3(Vec3 val, const char* name);
	void SetUniformVec4(Vec4 val, const char* name);
	void SetUniformMat3(Mat3 val, const char* name);
	void SetUniformMat4(Mat4 val, const char* name);

private:
	char* ReadShaderFile(const char* dir);
	GLenum GetGLShaderType(ShaderType type);

private:
	GLuint _program;
	GLuint _shader[ALL_SHADERS];
};

#endif

