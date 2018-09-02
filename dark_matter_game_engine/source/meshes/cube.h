//*************************************************************************
// DarkMatter OpenGL 3D Engine Framework
// Class Name: Cube
// Source File: [cube.h]
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
#ifndef _CUBE_H_
#define _CUBE_H_

//*************************************************************************
// Includes
//*************************************************************************
#include <GL/glew.h>
#include "meshBase.h"

//*************************************************************************
// Cube Class
//*************************************************************************
class Cube : public MeshBase
{
public:
	Cube(const char* shader_name,
		 const Vec3& pos   = Vec3(0.0f, 0.0f, 0.0f),
		 const Vec3& scale = Vec3(1.0f, 1.0f, 1.0f),
		 const Vec3& rot   = Vec3(0.0f, 0.0f, 0.0f),
		 const Vec4& color = Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	~Cube();

private:
	void Init() override;

public:
	void Draw(const Camera& cam) override;
	void Delete() override;
};

#endif
