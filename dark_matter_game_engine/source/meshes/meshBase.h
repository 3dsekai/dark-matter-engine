//*************************************************************************
// DarkMatter OpenGL 3D Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: MeshBase
// Source File: [meshBase.h]
//
// License:
// Copyright(C) <2018>  <Christopher Tall>
//
// This is software is copyrighted.
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
#ifndef _MESH_BASE_H_
#define _MESH_BASE_H_

//*************************************************************************
// Includes
//*************************************************************************
#include <GL/glew.h>
#include "../math_lib/vec4.h"
#include "../math_lib/quat.h"

class Camera;

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
		const Quat& rot,
		const Vec4& color,
		GLuint vao);

protected:
	virtual void Init() = 0;

public:
	virtual void Draw(const Camera& cam) = 0;
	virtual void Delete() = 0;

public:
	void SetPosition(const Vec3& pos);
	void SetRotation(const Quat& rot);
	void SetScale(const Vec3& scale);
	void SetColor(const Vec4& color);

	const Vec3 GetPosition() const;
	const Quat GetRotation() const;
	const Vec3 GetScale() const;
	const Vec4 GetColor() const;

protected:
	const char* _shader_name;	//the name of the shader
	GLuint _VAO;				//vertex array object

	Vec3 _pos;					//position
	Vec3 _scale;				//scale
	Quat _rot;					//rotation
	Vec4 _color;				//color
};

#endif
