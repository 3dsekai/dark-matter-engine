//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: Lamp
// Source File: [lamp.cpp]
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
#include "lamp.h"
#include "../../define/shader_define.h"
#include "../../meshes/cube.h"
#include "../../lighting/diffuseLight.h"

//*************************************************************************
// Class: Lamp
// Function Name: Lamp
// Argument{s}: -
// Explanation: Lamp constructor
//*************************************************************************
Lamp::Lamp()
{
}

//*************************************************************************
// Class: Lamp
// Function Name: ~Lamp
// Argument{s}: -
// Explanation: Lamp destructor
//*************************************************************************
Lamp::~Lamp()
{
	delete _lamp;
	_lamp = nullptr;

	delete _light;
	_light = nullptr;
}

//*************************************************************************
// Class: Lamp
// Function Name: Init
// Argument{s}: -
// Explanation: initialize game object
//*************************************************************************
void Lamp::Init()
{
	//lamp
	_lamp = new Cube(SOLID_MESH_SHADER_NAME,
			 		 Vec3(10.0f, 0.0f, 0.0f),
					 Vec3(0.5, 0.5f, 0.5f),
					 Quat(0.0f, 0.0f, 0.0f, 1.0f),
					 Vec4(1.0f, 1.0f, 1.0f, 1.0f));

	//lamp light
	Vec4 col = _lamp->GetColor();
	_light = new DiffuseLight(_lamp->GetPosition(), Vec3(col.x, col.y, col.z));

}

//*************************************************************************
// Class: Lamp
// Function Name: Update
// Argument{s}: -
// Explanation: update game object
//*************************************************************************
void Lamp::Update(const Mouse& mouse, const Keyboard& keyboard)
{
}

//*************************************************************************
// Class: Lamp
// Function Name: Draw
// Argument{s}: -
// Explanation: draw game object
//*************************************************************************
void Lamp::Draw()
{
	_lamp->Draw();
}

//*************************************************************************
// Class: Lamp
// Function Name: Release
// Argument{s}: -
// Explanation: delete game object
//*************************************************************************
void Lamp::Release()
{
	_is_kill = true;
}
