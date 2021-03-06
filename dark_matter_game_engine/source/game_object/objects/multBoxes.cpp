//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: MultBoxes
// Source File: [multBoxes.cpp]
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
#include "multBoxes.h"
#include "../../define/shader_define.h"
#include "../../meshes/cube.h"
#include "../../define/texture_define.h"
#include "../../math_lib/mat4.h"
#include "../../math_lib/mathUtil.h"
//*************************************************************************
// Class: MultiBoxes
// Function Name: MulBoxes
// Argument{s}: -
// Explanation: MultBoxes constructor
//*************************************************************************
MultBoxes::MultBoxes()
{
}

//*************************************************************************
// Class: MultiBoxes
// Function Name: MulBoxes
// Argument{s}: -
// Explanation: MultBoxes destructor
//*************************************************************************
MultBoxes::~MultBoxes()
{
	for (auto it = _cubes.begin(); it != _cubes.end(); it++)
	{
		delete *it;
		(*it) = nullptr;
	}
	_cubes.clear();
}

//*************************************************************************
// Class: MultiBoxes
// Function Name: Init
// Argument{s}: -
// Explanation: initialize game object
//*************************************************************************
void MultBoxes::Init()
{
	//cube 1
	_cubes.push_back(new Cube(TEXTURE_MESH_SHADER_NAME,
					 		  Vec3(0.0f, 0.0f, 0.0f),
							  Quat(Quat::Identity())));
	//cube 2 
	_cubes.push_back(new Cube(TEXTURE_MESH_SHADER_NAME,
					 		  Vec3(5.0f, 0.0f, 0.0f),
							  Quat(Quat::Identity())));
	//cube 3
	_cubes.push_back(new Cube(TEXTURE_MESH_SHADER_NAME,
					 		  Vec3(2.5f, 5.0f, 0.0f),
							  Quat(Quat::Identity())));

	for (auto it = _cubes.begin(); it != _cubes.end(); it++)
	{
		(*it)->SetTexture(BOX2_TEXTURE, MATERIAL_DIFFUSE);
		(*it)->SetTexture(BOX2_SPEC_TEX, MATERIAL_SPECULAR);
	}
}

//*************************************************************************
// Class: MultiBoxes
// Function Name: Update
// Argument{s}: -
// Explanation: update game object
//*************************************************************************
void MultBoxes::Update(const Mouse& mouse, const Keyboard& keyboard, Camera* cam)
{
//	for(auto it = _cubes.begin(); it != _cubes.end(); it++)
//	{
//		(*it)->SetRotation(Quat::Euler2Quat(Vec3::Deg2RadVec3(_rot)));
//	}
//	_rot.x += 0.5f;
//	_rot.y += 0.5f;
}

//*************************************************************************
// Class: MultiBoxes
// Function Name: Draw
// Argument{s}: -
// Explanation: draw game object
//*************************************************************************
void MultBoxes::Draw()
{
	for(auto it = _cubes.begin(); it != _cubes.end(); it++)
	{
		(*it)->Draw();
	}
}

//*************************************************************************
// Class: MultiBoxes
// Function Name: Release
// Argument{s}: -
// Explanation: delete game object
//*************************************************************************
void MultBoxes::Release()
{
	_is_kill = true;
}
