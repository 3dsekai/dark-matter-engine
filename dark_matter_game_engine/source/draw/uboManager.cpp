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
#include "shaderManager.h"
#include "drawUtil.h"
#include "shader.h"

UBOManager::UBOParams UBOManager::_uboParams = UBOParams();
//*************************************************************************
// Class: UBOManager
// Function Name: SetUniformBufferObject
// Argument{s}:
// Explanation: set all the parameters in the mesh's uniform buffer object
//*************************************************************************
void UBOManager::SetUniformBufferObject(const Camera& cam)
{
	//get the projection-view matrix for this frame
	_uboParams.projView = DrawUtil::GenerateProjectionViewMatrix(cam);

	//get the relevant shader program id
	GLuint shaderIdSolid = ShaderManager::GetInstance()->GetShader("solid_mesh")->GetProgramID();
	if (shaderIdSolid == 0)
	{
		std::cout << "InitUniformBufferObject(): couldn't load shader: " << "solid_mesh" << std::endl;
	}
	GLuint shaderIdTex = ShaderManager::GetInstance()->GetShader("tex_mesh")->GetProgramID();
	if (shaderIdTex == 0)
	{
		std::cout << "InitUniformBufferObject(): couldn't load shader: " << "tex_mesh" << std::endl;
	}

	//Get the relevant block indices
	unsigned int uBlockIdxSolid = glGetUniformBlockIndex(shaderIdSolid, "UBOParams");
	unsigned int uBlockIdxTex = glGetUniformBlockIndex(shaderIdTex, "UBOParams");

	//link each shader's uniform block to this uniform binding point
	glUniformBlockBinding(shaderIdSolid, uBlockIdxSolid, 0);
	glUniformBlockBinding(shaderIdTex, uBlockIdxTex, 0);

	//create the buffer
	unsigned int uboMatrices;
	glGenBuffers(1, &uboMatrices);
	glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(Mat4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	// define the range of the buffer that links to a uniform binding point
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, sizeof(Mat4));

	//store mview-projection matrix
	glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Mat4), &_uboParams.projView);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}