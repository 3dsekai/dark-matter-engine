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
#include "../resource/textureResourceManager.h"
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
		shader->SetUniformMat4(model, "model");
		
		//get matrix normal		
		Mat4 norm = model;
		norm = norm.GetMatrixNormal();
		shader->SetUniformMat3(Mat3::Mat4ToMat3(norm), "normModelMat");

		// set material
		shader->SetUniformVec3(_mParams.material.specular, "material.specular");
		shader->SetUniformFloat(_mParams.material.shininess, "material.shininess");
	}
	else
	{
		std::cout << "Couldn't load shader: " << _mParams.shaderName << std::endl;
	}

	if(_mParams.material.diffuse != 0)
	{
		//activate and bind the texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _mParams.material.diffuse);
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
void RenderMesh::Set2DTextureMesh(const char* texName)
{
	//load texture
	std::string dir = "resources/img/" + std::string(texName);
	TextureResourceManager::stbImgData texData;
	TextureResourceManager::LoadTexture(dir.c_str(), &texData);

	if (texData.imgData != nullptr)
	{
		GLenum format;
		if      (texData.n == 1) format = GL_RED;
		else if (texData.n == 2) format = GL_RG;
		else if (texData.n == 3) format = GL_RGB;
		else if (texData.n == 4) format = GL_RGBA;

		glGenTextures(1, &_mParams.material.diffuse); //generate texture name
		glBindTexture(GL_TEXTURE_2D, _mParams.material.diffuse); //bind the texture to the texture target

		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//generate texture image on currently bound texture object
		glTexImage2D(GL_TEXTURE_2D,
					 0,
					 format,
					 texData.w,
					 texData.h,
					 0,
					 format,
					 GL_UNSIGNED_BYTE,
					 texData.imgData);
		//generate mipmaps for currently bound texture object
		glGenerateMipmap(GL_TEXTURE_2D);

		//set the cube color and texture to the shader
		Shader* shader = ShaderManager::GetInstance()->GetShader(_mParams.shaderName);
		if (shader != nullptr)
		{
			shader->UseProgram();
			shader->SetUniformUint(0, "material.diffuse");
		}
		else
		{
			std::cout << "Couldn't load shader: " << _mParams.shaderName << std::endl;
		}
	}

	//unload texture
	TextureResourceManager::UnloadTexture(&texData);
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
