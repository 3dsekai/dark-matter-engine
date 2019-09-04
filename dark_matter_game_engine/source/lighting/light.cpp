//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: Light
// Source File: [light.cpp]
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
#include <iostream>
#include "light.h"
#include "../draw/shaderManager.h"
#include "../draw/shader.h"

//*************************************************************************
// Class: Light
// Function Name: Light
// Argument{s}: -
// Explanation: Light constructor
//*************************************************************************
Light::Light(const char* shader_name, lightDef light) :
		_shader(shader_name),
		_light(light)
{
}

//*************************************************************************
// Class: Light
// Function Name: ~Light
// Argument{s}: -
// Explanation: Diffuse light destructor
//*************************************************************************
Light::~Light()
{
}

//*************************************************************************
// Class: Light
// Function Name: Draw
// Argument{s}: -
// Explanation: Diffuse light draw
//*************************************************************************
void Light::Draw()
{
	Shader* shader = ShaderManager::GetInstance()->GetShader(_shader);
	if(shader != nullptr)
	{
		shader->UseProgram();

		//set light properties
		shader->SetUniformVec3(_light.position, "light.position");
		shader->SetUniformVec3(_light.ambient, "light.ambient");
		shader->SetUniformVec3(_light.diffuse, "light.diffuse");
		shader->SetUniformVec3(_light.specular, "light.specular");
	}
}
