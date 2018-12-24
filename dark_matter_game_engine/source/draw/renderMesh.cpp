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
#include "../draw/shaderManager.h"
#include "../draw/shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../third_party_lib/stb_image.h"

//*************************************************************************
// Class: RenderMesh
// Function Name: InitMesh
// Argument{s}:
// const float* vertices: the mesh's vertices
// const int* indices: the mesh's indices
// Explanation: initializes the mesh for rendering
//*************************************************************************
void RenderMesh::InitMesh(const float* vertices, const int* indices)
{
	//do depth comparisons and update the z-buffer
	glEnable(GL_DEPTH_TEST);

	//generate a vertex array object
	glGenVertexArrays(1, &_mParams.VAO);

	//generate the vertex buffer and element buffer objects
	GLuint buffObj[2];
	glGenBuffers(2, buffObj);

	//bind the vertex array object
	glBindVertexArray(_mParams.VAO);

	//bind the vertex data to the position vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, buffObj[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*_mParams.vertNum, vertices, GL_STATIC_DRAW);

	//bind the index data to the element buffer object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffObj[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float)*_mParams.idxNum, indices, GL_STATIC_DRAW);

	//set vertex attributes
	for(unsigned int i = 0; i < _mParams.vertAttr.size(); i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(
		i,
		_mParams.vertAttr[i].size,
		_mParams.vertAttr[i].type,
		_mParams.vertAttr[i].norm,
		_mParams.vertAttr[i].stride,
		(GLvoid*)(_mParams.vertAttr[i].offset));
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

//*************************************************************************
// Class: RenderMesh
// Function Name: DrawMesh
// Argument{s}:
// const Camera& cam: the world camera
// Mat4 model: the local matrix for the mesh
// Explanation: draw mesh
//*************************************************************************
void RenderMesh::DrawMesh(const Mat4& model)
{
	Shader* shader = ShaderManager::GetInstance()->GetShader(_mParams.shaderName);
	if(shader != nullptr)
	{
		//set the model-view-projection matrix to the shader
		shader->UseProgram();
		shader->SetUniformVec4(_mParams.color, "meshColor");
		shader->SetUniformMat4(model, "model");
	}
	else
	{
		std::cout << "Couldn't load shader: " << _mParams.shaderName << std::endl;
	}

	if(_mParams.texId != -1)
	{
		//activate and bind the texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _mParams.texId);
	}

	//bind the vertex array object
	glBindVertexArray(_mParams.VAO);

	//draw the triangles to the buffer
	glDrawElements(GL_TRIANGLES, _mParams.idxNum, GL_UNSIGNED_INT, 0);
}
//*************************************************************************
// Class: RenderMesh
// Function Name: SetTextureMesh
// Argument{s}:
// const char* texName: the name of the texture to load
// Explanation: set the texture onto the mesh
//*************************************************************************
void RenderMesh::SetTextureMesh(const char* texName)
{
	glGenTextures(1, &_mParams.texId); //generate texture name
	glBindTexture(GL_TEXTURE_2D, _mParams.texId); //bind the texture to the texture target

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//flip texture's y-axis
	stbi_set_flip_vertically_on_load(true);

	//load image data
	std::string dir = "resources/img/" + std::string(texName);
	int w, h, n;
	unsigned char* imgData = stbi_load(dir.c_str(), &w, &h, &n, 0);

	if (imgData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData); //generate texture image on currently bound texture object
		glGenerateMipmap(GL_TEXTURE_2D); //generate mipmaps for currently bound texture object
	}
	else
	{
		std::cout << "Texture load Failure" << std::endl;
	}
	stbi_image_free(imgData);

	//set the cube color and texture to the shader
	Shader* shader = ShaderManager::GetInstance()->GetShader(_mParams.shaderName);
	if (shader != nullptr)
	{
		shader->UseProgram();
		shader->SetUniformInt(_mParams.texId, "texture");
	}
}

//*************************************************************************
// Class: RenderMesh
// Function Name: DeleteMesh
// Argument{s}:
// Explanation: delete mesh renderer
//*************************************************************************
void RenderMesh::DeleteMesh()
{
	glDeleteVertexArrays(1, &_mParams.VAO);
}