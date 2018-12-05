//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: Cube
// Source File: [cube.cpp]
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
#include "../main.h"
#include "../meshes/cube.h"
#include "../draw/shaderManager.h"
#include "../draw/shader.h"
#include "../define/draw_define.h"
#include "../math_lib/mat4.h"
#include "../camera/camera.h"
#include "../window/window.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../third_party_lib/stb_image.h"

//*************************************************************************
// Macro Definitions
//*************************************************************************
#define POS_ELEM_NUM (24)
#define TEX_ELEM_NUM (8)
#define INDICES_NUM (36)

//*************************************************************************
// constants definitions
//*************************************************************************
namespace
{
	//cube vertices
	const GLfloat coords[] =
	{
		/*pos coord           tex coord */
		//front
		-1.0, -1.0,  1.0,    0.0f, 0.0f, //bottom left
		 1.0, -1.0,  1.0,    1.0f, 0.0f, //bottom right
		 1.0,  1.0,  1.0,    1.0f, 1.0f, //top right
		-1.0,  1.0,  1.0,    0.0f, 1.0f, //top left
		 //back
		 1.0, -1.0, -1.0,    0.0f, 0.0f,
		-1.0, -1.0, -1.0,    1.0f, 0.0f,
		-1.0,  1.0, -1.0,    1.0f, 1.0f,
		 1.0,  1.0, -1.0,    0.0f, 1.0f,
		//top
		-1.0,  1.0, -1.0,    0.0f, 0.0f, //bottom left
		 1.0,  1.0, -1.0,    1.0f, 0.0f, //bottom right
		 1.0,  1.0,  1.0,    1.0f, 1.0f, //top right
		-1.0,  1.0,  1.0,    0.0f, 1.0f, //top left
		//bottom
		-1.0, -1.0,  1.0,    0.0f, 0.0f,
		 1.0, -1.0,  1.0,    1.0f, 0.0f,
		 1.0, -1.0, -1.0,    1.0f, 1.0f,
		-1.0, -1.0, -1.0,    0.0f, 1.0f,
		//right
		 1.0, -1.0,  1.0,    0.0f, 0.0f, //bottom left
		 1.0, -1.0, -1.0,    1.0f, 0.0f, //bottom right
		 1.0,  1.0, -1.0,    1.0f, 1.0f, //top right
		 1.0,  1.0,  1.0,    0.0f, 1.0f, //top left
		//left
		-1.0, -1.0, -1.0,    0.0f, 0.0f,
		-1.0, -1.0,  1.0,    1.0f, 0.0f,
		-1.0,  1.0,  1.0,    1.0f, 1.0f,
		-1.0,  1.0, -1.0,    0.0f, 1.0f
	};

	//cube indices
	const GLuint indices[INDICES_NUM] =
	{
		// front
		0, 1, 2,
		2, 3, 0,
		// back
		4, 5, 6,
		6, 7, 4,
		// top
		8,  9,  10,
		10, 11, 8,
		// bottom
		12, 13, 14,
		14, 15, 12,
		// right
		16, 17, 18,
		18, 19, 16,
		// left
		20, 21, 22,
		22, 23, 20
	};
}
//*************************************************************************
// Class: Cube
// Function Name: Cube
// Argument{s}: -
// Explanation: Cube constructor
//*************************************************************************
Cube::Cube(const char* shaderName, const Vec3& pos, const Vec3& scale, const Quat& rot, const Vec4& color) :
	MeshBase(shaderName, pos, scale, rot, color, 0)
{
	Init();
}

//*************************************************************************
// Class: Cube
// Function Name: ~Cube
// Argument{s}: -
// Explanation: Cube destructor
//*************************************************************************
Cube::~Cube()
{
	Delete();
}

//*************************************************************************
// Class: Cube
// Function Name: Init
// Argument{s}: -
// Explanation: Initialize the cube
//*************************************************************************
void Cube::Init()
{
	//do depth comparisons and update the z-buffer
	glEnable(GL_DEPTH_TEST);

	//generate a vertex array object
	glGenVertexArrays(1, &_VAO);

	//declare the buffer objects
	GLuint _buffObj[2];

	//generate the vertex buffer and element buffer objects
	glGenBuffers(2, _buffObj);

	//bind the vertex array object
	glBindVertexArray(_VAO);

	//bind the vertex data to the position vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, _buffObj[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);

	//bind the index data to the element buffer object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffObj[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//define how the vertex buffer data should be interpreted when a draw call is made for vertex position
	glEnableVertexAttribArray(POS_COORD_ATTRIB);
	glVertexAttribPointer(
	POS_COORD_ATTRIB,	//index for vertex attribute
	3,					//number of elements in vertex attribute
	GL_FLOAT,			//data type
	GL_FALSE,			//value normalization
	5*sizeof(float),	//stride: the offset between consecutive vertex attributes in the array (0 is tightly packed)
	(GLvoid*)0);		//offset to the first vertex attribute in the array

	//define how the vertex buffer data should be interpreted when a draw call is made for texture vertex
	glEnableVertexAttribArray(TEX_COORD_ATTRIB);
	glVertexAttribPointer(
	TEX_COORD_ATTRIB,
	2,
	GL_FLOAT,
	GL_FALSE,
	5*sizeof(float),
	(void*)(3*sizeof(float)));

	//unbind the vertex buffer object
	/*NOTE: can't unbind the element buffer object until the VAO is done being used*/
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//unbind the vertex array object
	glBindVertexArray(0);

	//delete the buffer objects
	for (int i = 0; i < 2; i++)
	{
		glDeleteBuffers(1, &_buffObj[i]);
	}
}


//*************************************************************************
// Class: Cube
// Function Name: Draw
// Argument{s}: -
// Explanation: Draw cube
//*************************************************************************
void Cube::Draw(const Camera& cam)
{
	//prepare model matrix
	Mat4 rotation = Mat4::Identity().Rotate(_rot);
	Mat4 translation = Mat4::Identity().Translate(_pos);
	Mat4 scale = Mat4::Identity().Scale(_scale);
	Mat4 model = translation * rotation * scale;
	//get view matrix
	Mat4 view = cam.GetViewMatrix();
	//prepare projection matrix.
	float w = Window::GetInstance()->GetWindowWidth();
	float h = Window::GetInstance()->GetWindowHeight();
	Mat4 proj = Mat4::Identity().Perspective(MathUtil::Deg2Rad(cam.GetFieldOfView()), 1.0f * (w/h), 0.1f, 100.0f);
	//model-view-projection transform
	Mat4 mvp = proj * view * model;

	Shader* shader = ShaderManager::GetInstance()->GetShader(_shaderName);
	if (shader != nullptr)
	{
		//set the model-view-projection matrix to the shader
		shader->UseProgram();
		shader->SetUniformVec4(_color, "cubeColor");
		shader->SetUniformMat4(mvp, "mvp");
	}

	if (_texture != -1)
	{
		//activate and bind the texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _texture);
	}

	//bind the vertex array object
	glBindVertexArray(_VAO);

	//draw the triangles to the buffer
	glDrawElements(GL_TRIANGLES, INDICES_NUM, GL_UNSIGNED_INT, 0);
}

//*************************************************************************
// Class: Cube
// Function Name: Delete
// Argument{s}: -
// Explanation: Delete cube
//*************************************************************************
void Cube::Delete()
{
	glDeleteVertexArrays(1, &_VAO);
}

//*************************************************************************
// Class: Cube
// Function Name: SetTexture
// Argument{s}: -
// Explanation: Load image and set texture to cube shader
//*************************************************************************
void Cube::SetTexture(const char* texName)
{
	glGenTextures(1, &_texture); //generate texture name
	glBindTexture(GL_TEXTURE_2D, _texture); //bind the texture to the texture target

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
	Shader* shader = ShaderManager::GetInstance()->GetShader(_shaderName);
	if (shader != nullptr)
	{
		shader->UseProgram();
		shader->SetUniformInt(_texture, "texture");
	}
}
