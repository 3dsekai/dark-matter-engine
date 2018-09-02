//*************************************************************************
// DarkMatter OpenGL 3D Engine Framework
// Class Name: MeshBase
// Source File: [meshBase.h]
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
#ifndef _MESH_BASE_H_
#define _MESH_BASE_H_

//*************************************************************************
// Includes
//*************************************************************************
#include <GL/glew.h>
#include "../camera/camera.h"
#include "../math_lib/vec4.h"

//*************************************************************************
// MeshBase Class
//*************************************************************************
class MeshBase
{
public:
	MeshBase() = default;
	~MeshBase() = default;

protected:
	MeshBase(const char* shader_name,
		const Vec3& pos,
		const Vec3& scale,
		const Vec3& rot,
		const Vec4& color,
		GLuint vao);

protected:
	virtual void Init() = 0;

public:
	virtual void Draw(const Camera& cam) = 0;
	virtual void Delete() = 0;

public:
	void SetPosition(const Vec3& pos);
	void SetRotation(const Vec3& rot);
	void SetScale(const Vec3& scale);
	void SetColor(const Vec4& color);

	const Vec3 GetPosition() const;
	const Vec3 GetRotation() const;
	const Vec3 GetScale() const;
	const Vec4 GetColor() const;

protected:
	const char* _shader_name;	//the name of the shader
	GLuint _VAO;				//vertex array object

	Vec3 _pos;					//position
	Vec3 _scale;				//scale
	Vec3 _rot;					//rotation
	Vec4 _color;				//color
};

#endif
