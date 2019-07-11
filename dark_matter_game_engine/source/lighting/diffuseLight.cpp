//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: DiffuseLight
// Source File: [diffuseLight.cpp]
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
#include <iostream>
#include "diffuseLight.h"
#include "../draw/shaderManager.h"
#include "../draw/shader.h"

//*************************************************************************
// Class: DiffuseLight
// Function Name: DiffuseLight
// Argument{s}: -
// Explanation: DiffuseLight constructor
//*************************************************************************
DiffuseLight::DiffuseLight(const char* shader_name, const Vec3& pos, const Vec3& color)
		: LightBase(shader_name, pos, color)
{
};

//*************************************************************************
// Class: DiffuseLight
// Function Name: ~DiffuseLight
// Argument{s}: -
// Explanation: Diffuse light destructor
//*************************************************************************
DiffuseLight::~DiffuseLight()
{
}

//*************************************************************************
// Class: DiffuseLight
// Function Name: Draw
// Argument{s}: -
// Explanation: Diffuse light draw
//*************************************************************************
void DiffuseLight::Draw()
{
	Shader* shader = ShaderManager::GetInstance()->GetShader(_shader);
	if(shader != nullptr)
	{
		shader->UseProgram();

		//diffuse light pos
		shader->SetUniformVec3(_pos, "lightPos");

		//diffuse light color
		shader->SetUniformVec3(_color, "lightColor");
	}
	else
	{
		std::cout << "Couldn't load shader: " << _shader << std::endl;
	}
}
