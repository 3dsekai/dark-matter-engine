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

//*************************************************************************
// constants definitions
//*************************************************************************
namespace
{
	//cube vertices
	const float vertices[VERTICES_NUM] =
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
	const int indices[INDICES_NUM] =
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
	{ //position coordinates
		VAParams va1;
		va1.size = 3; //size of attribute
		va1.type = GL_FLOAT; //vertex attribute type
		va1.norm = GL_FALSE; //vertex attribute normalization bool
		va1.stride = 5*sizeof(float); //size of vertex stride
		va1.offset = 0; //offset attribute
		_renderer->_mParams.vertAttr.push_back(va1);
	}

	{ //texture coordinates
		VAParams va2;
		va2.size = 2;
		va2.type = GL_FLOAT;
		va2.norm = GL_FALSE;
		va2.stride = 5*sizeof(float);
		va2.offset = 3*sizeof(float);
		_renderer->_mParams.vertAttr.push_back(va2);
	}

	//set number of vertices and indices
	_renderer->_mParams.vertNum = VERTICES_NUM;
	_renderer->_mParams.idxNum = INDICES_NUM;

	//initialize the mesh for rendering
	_renderer->InitMesh(vertices, indices);
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

	//draw the mesh
	_renderer->DrawMesh(cam, model);
}

//*************************************************************************
// Class: Cube
// Function Name: Delete
// Argument{s}: -
// Explanation: Delete cube
//*************************************************************************
void Cube::Delete()
{
	glDeleteVertexArrays(1, &_renderer->_mParams.VAO);

	//delete renderer
	delete _renderer;
	_renderer = nullptr;
}

//*************************************************************************
// Class: Cube
// Function Name: SetTexture
// Argument{s}: -
// Explanation: Load image and set texture to cube shader
//*************************************************************************
void Cube::SetTexture(const char* texName)
{
	_renderer->SetTextureMesh(texName);
}
