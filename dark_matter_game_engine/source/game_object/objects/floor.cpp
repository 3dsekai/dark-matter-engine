//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: Floor
// Source File: [floor.cpp]
//
// License:
// Copyright(C) <2019>  <Christopher Tall>
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
#include "floor.h"
#include "../../define/shader_define.h"
#include "../../meshes/plane.h"
#include "../../define/texture_define.h"

//*************************************************************************
// Class: Floor
// Function Name: Floor
// Argument{s}: -
// Explanation: Floor constructor
//*************************************************************************
Floor::Floor() :
	_plane(nullptr)
{
}

//*************************************************************************
// Class: Floor
// Function Name: Floor
// Argument{s}: -
// Explanation: Floor destructor
//*************************************************************************
Floor::~Floor()
{
	delete _plane;
	_plane = nullptr;
}

//*************************************************************************
// Class: Floor
// Function Name: Init
// Argument{s}: -
// Explanation: initialize game object
//*************************************************************************
void Floor::Init()
{
	_plane = new Plane(TEXTURE_MESH_SHADER_NAME,
					  Vec3(1.0f, -13.0f, 0.0f),
					  Quat(Quat::Euler2Quat(Vec3::Deg2RadVec3(Vec3(-90.0f, 0.0f, 0.0f)))),
					  Vec3(10.0f, 10.0f, 10.0f));
	_plane->SetTexture(BOX_TEXTURE, MATERIAL_DIFFUSE);
	_plane->SetTexture(BLACK_TEXTURE, MATERIAL_SPECULAR);
}

//*************************************************************************
// Class: Floor
// Function Name: Update
// Argument{s}: -
// Explanation: update game object
//*************************************************************************
void Floor::Update(const Mouse& mouse, const Keyboard& keyboard, Camera* cam)
{
}

//*************************************************************************
// Class: Floor
// Function Name: Draw
// Argument{s}: -
// Explanation: draw game object
//*************************************************************************
void Floor::Draw()
{
	if(_plane != nullptr)
	{
		_plane->Draw();
	}
}

//*************************************************************************
// Class: Floor
// Function Name: Release
// Argument{s}: -
// Explanation: delete game object
//*************************************************************************
void Floor::Release()
{
	_is_kill = true;
}
