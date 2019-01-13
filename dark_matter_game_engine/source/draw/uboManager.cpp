//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: UBOManager
// Source File: [uboManager.cpp]
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
// Include
//*************************************************************************
#include <iostream>
#include <GL/glew.h>
#include "uboManager.h"

//*************************************************************************
// static member variables initialization
//*************************************************************************
UBOManager::UBOParams UBOManager::_uboParams = UBOParams();
GLuint UBOManager::_uboBufferId = 0;

//*************************************************************************
// Class: UBOManager
// Function Name: InitUniformBufferObject
// Argument{s}:
// Explanation: initialize the uniform buffer object
//*************************************************************************
void UBOManager::InitUniformBufferObject()
{
	//create the buffer
	glGenBuffers(1, &_uboBufferId);
	glBindBuffer(GL_UNIFORM_BUFFER, _uboBufferId);
	glBufferData(GL_UNIFORM_BUFFER,UBOPARAMS_SIZE, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

}

//*************************************************************************
// Class: UBOManager
// Function Name: UpdateUniformBufferObject
// Argument{s}:
// Explanation: set all the parameters in the mesh's uniform buffer object
//*************************************************************************
void UBOManager::UpdateUniformBufferObject()
{
	// define the range of the buffer that links to a uniform binding point
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, _uboBufferId, 0, UBOPARAMS_SIZE);

	//store view-projection matrix
	glBindBuffer(GL_UNIFORM_BUFFER, _uboBufferId);
	glBufferSubData(GL_UNIFORM_BUFFER, AO_NONE, BA_MAT4, &_uboParams.projView);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	//store the ambient light
	glBindBuffer(GL_UNIFORM_BUFFER, _uboBufferId);
	glBufferSubData(GL_UNIFORM_BUFFER, AO_MAT4, BA_VEC3, &_uboParams.ambientLight);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

//*************************************************************************
// Class: UBOManager
// Function Name: LinkShaderUBOBlockIndex
// Argument{s}:
// GLuint shaderId: the id of the shader to the uniform binding point
// Explanation: link the shader's uniform block to the uniform binding point
//*************************************************************************
void UBOManager::LinkShaderUBOBlockIndex(GLuint shaderId)
{
	//Get the relevant block index
	unsigned int uBlockIdx = glGetUniformBlockIndex(shaderId, "UBOParams");

	//link the shader's uniform block to this uniform binding point
	glUniformBlockBinding(shaderId, uBlockIdx, 0);
}
