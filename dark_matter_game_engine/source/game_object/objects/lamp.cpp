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
#include "../../define/light_define.h"
#include "../../meshes/cube.h"
#include "../../lighting/light.h"
#include "../../math_lib/mat4.h"
//*************************************************************************
// Class: Lamp
// Function Name: Lamp
// Argument{s}: -
// Explanation: Lamp constructor
//*************************************************************************
Lamp::Lamp() :
	_lamp(nullptr),
	_light(nullptr)
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
					 Quat(Quat::Identity()),
					 Vec3(0.5, 0.5f, 0.5f));

	//lamp light
	Vec4 col = Vec4(1.0f, 1.0f, 1.0f, 1.0f);

	lightDef light;
	light.position = _lamp->GetPosition();
	light.ambient = Vec3(col.x, col.y, col.z) * 0.1f;
	light.diffuse = Vec3(col.x, col.y, col.z) * 0.5f;
	light.specular = Vec3(1.0f, 1.0f, 1.0f);
	_light = new Light(TEXTURE_MESH_SHADER_NAME, light);

}

//*************************************************************************
// Class: Lamp
// Function Name: Update
// Argument{s}: -
// Explanation: update game object
//*************************************************************************
void Lamp::Update(const Mouse& mouse, const Keyboard& keyboard, Camera* cam)
{
	Mat4 t = Mat4::TranslateMat(Vec3(10.0f, 0.0f, 0.0f));
	Mat4 r = Mat4::Identity().Rotate(Vec3::Deg2RadVec3(_rot));
	Mat4 w = r * t;

	if(_lamp != nullptr)
	{
		_lamp->SetPosition(w.GetTranslation());
		_lamp->SetRotation(Quat::Mat2Quat(w));
	}
	if(_light != nullptr)
	{
		_light->SetPosition(w.GetTranslation());
	}

	_rot.y += 0.5f;

}

//*************************************************************************
// Class: Lamp
// Function Name: Draw
// Argument{s}: -
// Explanation: draw game object
//*************************************************************************
void Lamp::Draw()
{
	if(_lamp != nullptr)
	{
		_lamp->Draw();
	}
	if(_light != nullptr)
	{
		_light->Draw();
	}
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
