//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: RenderMesh
// Source File: [renderMesh.cpp]
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
#include "renderMesh.h"
#include "shaderManager.h"
#include "shader.h"
#include "../math_lib/mat3.h"
#include "../math_lib/mat4.h"
#include "../math_lib/vec3.h"

//*************************************************************************
// Class: RenderMesh
// Function Name: InitMesh
// Argument{s}:
// const float* vertices: the mesh's vertices
// const int* indices: the mesh's indices
// Explanation: initializes the mesh for rendering
//*************************************************************************
void RenderMesh::InitMesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, MeshParam* mParam, const std::vector<VAParams>& va)
{
	if(mParam != nullptr)
	{
		//generate a vertex array object
		glGenVertexArrays(1, &mParam->VAO);
	
		//generate the vertex buffer and element buffer objects
		GLuint buffObj[2];
		glGenBuffers(2, buffObj);
	
		//bind the vertex array object
		glBindVertexArray(mParam->VAO);
	
		//bind the vertex data to the position vertex buffer object
		glBindBuffer(GL_ARRAY_BUFFER, buffObj[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertices.size(), &vertices[0], GL_STATIC_DRAW);
	
		//bind the index data to the element buffer object
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffObj[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t)*indices.size(), &indices[0], GL_STATIC_DRAW);
	
		//set vertex attributes
		for(unsigned int i = 0; i < va.size(); i++)
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(
			i,
			va[i].size,
			va[i].type,
			va[i].norm,
			va[i].stride,
			(GLvoid*)(va[i].offset));
		}
	
		//unbind the vertex buffer object
		//NOTE: can't unbind the element buffer object until the VAO is done being used
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	
		//unbind the vertex array object
		glBindVertexArray(0);
	
		//delete the buffer objects
		for (int i = 0; i < 2; i++)
		{
			glDeleteBuffers(1, &buffObj[i]);
		}
	}
	else
	{
		std::cout << "Error: could not initialize mesh." << std::endl;
	}
}

//*************************************************************************
// Class: RenderMesh
// Function Name: DrawMesh
// Argument{s}:
// Mat4 model: the local matrix for the mesh
// MeshRenderParam mDrawParam: the mesh parameters necessary for rendering 
// Explanation: draw mesh
//*************************************************************************
void RenderMesh::DrawMesh(const Mat4& model, const MeshRenderParam& mDrawParam)
{
	Shader* shader = ShaderManager::GetInstance()->GetShader(mDrawParam.shaderName);
	if(shader != nullptr)
	{
		//set the model-view-projection matrix to the shader
		shader->UseProgram();
		shader->SetUniformMat4(model, "model");
		
		//get matrix normal		
		Mat4 norm = model;
		norm = norm.GetMatrixNormal();
		shader->SetUniformMat3(Mat3::Mat4ToMat3(norm), "normModelMat");

		// set material
		shader->SetUniformFloat(mDrawParam.material.shininess, "material.shininess");
	}
	int samplerIdx = 0;
	for(int i = 0; i < mDrawParam.material.diffMaterialNum; i++)
	{
		//activate and bind the texture
		glActiveTexture(GL_TEXTURE0 + samplerIdx++);
		glBindTexture(GL_TEXTURE_2D, mDrawParam.material.diffTexId[i]);
	}
	for(int i = 0; i < mDrawParam.material.specMaterialNum; i++)
	{
		glActiveTexture(GL_TEXTURE0 + samplerIdx++);
		glBindTexture(GL_TEXTURE_2D, mDrawParam.material.specTexId[i]);
	}

	//bind the vertex array object
	glBindVertexArray(mDrawParam.mesh.VAO);

	//draw the triangles to the buffer
	glDrawElements(GL_TRIANGLES, mDrawParam.mesh.idxNum, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0); //reset vao bind
	glActiveTexture(GL_TEXTURE0); //reset active texture
}

//*************************************************************************
// Class: RenderMesh
// Function Name: DeleteMesh
// Argument{s}:
// Explanation: delete mesh renderer
//*************************************************************************
void RenderMesh::DeleteMesh(MeshParam* mParam)
{
	if(mParam != nullptr)
	{
		glDeleteVertexArrays(1, &mParam->VAO);
	}
}
