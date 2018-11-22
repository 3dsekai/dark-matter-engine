//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: Shader
// Source File: [shader.h]
//
// License:
// Copyright(C) <2018>  <Christopher Tall>
//
// This software is copyrighted.
// The copyright notice and license information in this document must be
// preserved in every copy of the document AS IS. Attribution to the
// original author of this software (see name/website next to "Author:")
// must be given in either the modified source OR in the
// product's documentation.
//
// This software is licensed under the terms of the GNU General Public License
// version 3, as published by the Free Software Foundation.
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

class Vec2;
class Vec3;
class Vec4;
class Mat3;
class Mat4;

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
	void SetUniformVec2(const Vec2& val, const char* name);
	void SetUniformVec3(const Vec3& val, const char* name);
	void SetUniformVec4(const Vec4& val, const char* name);
	void SetUniformMat3(const Mat3& val, const char* name);
	void SetUniformMat4(const Mat4& val, const char* name);

private:
	std::string ReadShaderFile(const char* dir);
	GLenum GetGLShaderType(ShaderType type);

private:
	GLuint _program;
	GLuint _shader[ALL_SHADERS];
};

#endif

