//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: Nanosuit
// Source File: [nanosuit.cpp]
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
#include "nanosuit.h"
#include "../../define/shader_define.h"
#include "../../model/model.h"
//*************************************************************************
// Class: MultiBoxes
// Function Name: MulBoxes
// Argument{s}: -
// Explanation: Nanosuit constructor
//*************************************************************************
Nanosuit::Nanosuit()
{
}

//*************************************************************************
// Class: MultiBoxes
// Function Name: MulBoxes
// Argument{s}: -
// Explanation: Nanosuit destructor
//*************************************************************************
Nanosuit::~Nanosuit()
{
	delete _nanosuit;
	_nanosuit = nullptr;
}

//*************************************************************************
// Class: MultiBoxes
// Function Name: Init
// Argument{s}: -
// Explanation: initialize game object
//*************************************************************************
void Nanosuit::Init()
{
	_nanosuit = new Model(TEXTURE_MESH_SHADER_NAME, "resources/models/nanosuit/nanosuit.obj");
}

//*************************************************************************
// Class: MultiBoxes
// Function Name: Update
// Argument{s}: -
// Explanation: update game object
//*************************************************************************
void Nanosuit::Update(const Mouse& mouse, const Keyboard& keyboard, Camera* cam)
{
}

//*************************************************************************
// Class: MultiBoxes
// Function Name: Draw
// Argument{s}: -
// Explanation: draw game object
//*************************************************************************
void Nanosuit::Draw()
{
	_nanosuit->Draw();
}

//*************************************************************************
// Class: MultiBoxes
// Function Name: Release
// Argument{s}: -
// Explanation: delete game object
//*************************************************************************
void Nanosuit::Release()
{
	_is_kill = true;
}
