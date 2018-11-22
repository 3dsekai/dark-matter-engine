//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: MeshBase
// Source File: [meshBase.cpp]
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

//*************************************************************************
// Includes
//*************************************************************************
#include "meshBase.h"

//*************************************************************************
// Class: MeshBase
// Function Name: MeshBase
// Argument{s}: -
// Explanation: MeshBase constructor
//*************************************************************************
MeshBase::MeshBase(const char* shader_name, const Vec3& pos, const Vec3& scale, const Quat& rot, const Vec4& color, GLuint vao) :
	_shader_name(shader_name),
	_pos(pos),
	_scale(scale),
	_rot(rot),
	_color(color),
	_VAO(vao)
{
};
//*************************************************************************
// Class: MeshBase
// Function Name: SetPosition
// Argument{s}:
// const Vec& pos: new position
// Explanation: set the mesh's world position
//*************************************************************************
void MeshBase::SetPosition(const Vec3& pos)
{
	_pos = pos;
}

//*************************************************************************
// Class: MeshBase
// Function Name: SetRotation
// Argument{s}:
// const Quat& rot: new rotation
// Explanation: set the mesh's rotation
//*************************************************************************
void MeshBase::SetRotation(const Quat& rot)
{
	_rot = rot;
}

//*************************************************************************
// Class: MeshBase
// Function Name: SetScale
// Argument{s}:
// const Vec& scale: new scale
// Explanation: set the mesh's scale
//*************************************************************************
void MeshBase::SetScale(const Vec3& scale)
{
	_scale = scale;
}

//*************************************************************************
// Class: MeshBase
// Function Name: SetColor
// Argument{s}:
// const Vec& color: new color
// Explanation: set the mesh's color
//*************************************************************************
void MeshBase::SetColor(const Vec4& color)
{
	_color = color;
}

//*************************************************************************
// Class: MeshBase
// Function Name: GetPosition
// Argument{s}: -
// Explanation: get the mesh's world position
//*************************************************************************
const Vec3 MeshBase::GetPosition() const
{
	return _pos;
}

//*************************************************************************
// Class: MeshBase
// Function Name: GetRotation
// Argument{s}: -
// Explanation: get the mesh's rotation
//*************************************************************************
const Quat MeshBase::GetRotation() const
{
	return _rot;
}

//*************************************************************************
// Class: MeshBase
// Function Name: GetScale
// Argument{s}: -
// Explanation: get the mesh's scale
//*************************************************************************
const Vec3 MeshBase::GetScale() const
{
	return _scale;
}

//*************************************************************************
// Class: MeshBase
// Function Name: GetColor
// Argument{s}: -
// Explanation: set the mesh's color
//*************************************************************************
const Vec4 MeshBase::GetColor() const
{
	return _color;
}
