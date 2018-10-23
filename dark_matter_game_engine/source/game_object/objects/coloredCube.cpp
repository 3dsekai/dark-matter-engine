//*************************************************************************
// DarkMatter OpenGL 3D Engine Framework
// Class Name: ColoredCube
// Source File: [coloredCube.cpp]
//
// License:
// Copyright(C) <2018>  <https://github.com/3dsekai/>
//
// This program is free software : you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
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
#include "../../main.h"
#include "ColoredCube.h"
#include "../../input/inputCodes.h"
#include "../../draw/shaderManager.h"
#include "../../define/shader_define.h"
#include "../../camera/camera.h"

//*************************************************************************
// constants definitions
//*************************************************************************
//cube position vertices
const float ColoredCube::_pos_verts[VERTICES_ELEM_NUM] =
{
	// front
	-1.0f, -1.0f,  1.0f, //bottom left
	 1.0f, -1.0f,  1.0f, //bottom right
	 1.0f,  1.0f,  1.0f, //top right
	-1.0f,  1.0f,  1.0f, //top left
	// back
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f
};

//cube position vertices
const float ColoredCube::_col_verts[COL_VERTS_ELEM_NUM] =
{
	// front colors
	0.0f, 0.0,  1.0, //bottom left
	0.0f, 1.0,  0.0, //bottom right
	1.0f, 0.0,  0.0, //top right
	1.0f, 1.0,  0.0, //top left
	// back colors
	1.0f, 0.0f,  1.0f,
	0.0f, 1.0f,  1.0f,
	0.56f, 0.0f, 1.0f,
	1.0f, 0.65f, 0.0f,
};

//cube indices
const unsigned int ColoredCube::_indices[INDICES_NUM] =
{
	// front
	0, 1, 2,
	2, 3, 0,
	// right
	1, 5, 6,
	6, 2, 1,
	// back
	7, 6, 5,
	5, 4, 7,
	// left
	4, 0, 3,
	3, 7, 4,
	// bottom
	4, 5, 1,
	1, 0, 4,
	// top
	3, 2, 6,
	6, 7, 3
};

namespace 
{
	//cube rotation
	float deg = 0.0f;
}

//*************************************************************************
// Class: ColoredCube
// Function Name: ColoredCube
// Argument{s}: -
// Explanation: ColoredCube constructor
//*************************************************************************
ColoredCube::ColoredCube() :
	_VAO(0)
{
	for(int i = 0; i < BUFF_OBJ_NUM; i++)
	{
		_buff_obj[i] = 0;
	}
};

//*************************************************************************
// Class: ColoredCube
// Function Name: ~ColoredCube
// Argument{s}: -
// Explanation: ColoredCube destructor
//*************************************************************************
ColoredCube::~ColoredCube() 
{
	Delete();
};

//*************************************************************************
// Class: ColoredCube
// Function Name: Init
// Argument{s}: -
// Explanation: Initialize the cube
//*************************************************************************
void ColoredCube::Init()
{
	//compile the shader
	ShaderManager::GetInstance()->LoadShader(COLORED_CUBE_SHADER_NAME,
											 COLORED_CUBE_VERTEX_SHADER,
											 COLORED_CUBE_FRAGMENT_SHADER);

	//do depth comparisons and update the z-buffer
	glEnable(GL_DEPTH_TEST);

	//generate a vertex array object
	glGenVertexArrays(1, &_VAO);

	//generate the vertex buffer and element buffer objects
	glGenBuffers(BUFF_OBJ_NUM, _buff_obj);

	//bind the vertex array object
	glBindVertexArray(_VAO);

	//bind the vertex data to the position vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, _buff_obj[POS_VERT_BUFF_OBJ]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_pos_verts), _pos_verts, GL_STATIC_DRAW);

	//define how the vertex buffer data should be interpreted when a draw call is made for vertex position
	glEnableVertexAttribArray(POS_COORD_ATTRIB);
	glVertexAttribPointer(POS_COORD_ATTRIB,
						  POS_ATTRIB_ELEM_NUM,
						  GL_FLOAT,
						  GL_FALSE,
						  VERTEX_STRIDE * sizeof(GLfloat),
						  (GLvoid*)0);

	//bind the vertex data to the color vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, _buff_obj[COLOR_VERT_BUFF_OBJ]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_col_verts), _col_verts, GL_STATIC_DRAW);

	//define how the vertex buffer data should be interpreted when a draw call is made for vertex color
	glEnableVertexAttribArray(TEX_COORD_ATTRIB);
	glVertexAttribPointer(TEX_COORD_ATTRIB,
						  COLOR_ATTRIB_ELEM_NUM,
						  GL_FLOAT,
						  GL_FALSE,
						  VERTEX_STRIDE * sizeof(GLfloat),
						  (GLvoid*)0);

	//bind the index data to the element buffer object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buff_obj[INDEX_BUFF_OBJ]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW);

	//unbind the vertex buffer object
	/*NOTE: can't unbind the element buffer object until the VAO is done being used*/
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//unbind the vertex array object
	glBindVertexArray(0);
};

//*************************************************************************
// Class: ColoredCube
// Function Name: Update
// Argument{s}:
// const Keyboard& keyboard: the global keyboard instance
// const Mouse& mouse: the global keyboard instance
// Explanation: Update cube
//*************************************************************************
void ColoredCube::Update(const Keyboard& keyboard, const Mouse& mouse)
{
	_cam.ProcessMouseMotion(mouse);

	if(keyboard.IsKeyPressed(KEY_W))
	{ //move forward
		_cam.Move(Camera::CamDir::DIR_FORWARD);
	}
	if(keyboard.IsKeyPressed(KEY_S))
	{ //move back
		_cam.Move(Camera::CamDir::DIR_BACK);
	}
	if(keyboard.IsKeyPressed(KEY_A))
	{ //move left
		_cam.Move(Camera::CamDir::DIR_LEFT);
	}
	if(keyboard.IsKeyPressed(KEY_D))
	{ //move right
		_cam.Move(Camera::CamDir::DIR_RIGHT);
	}
};

//*************************************************************************
// Class: ColoredCube
// Function Name: Draw
// Argument{s}: -
// Explanation: Draw cube
//*************************************************************************
void ColoredCube::Draw()
{
	//prepare model matrix
	Mat4 model = Mat4::Identity().RotateYAxis(MathUtil::Deg2Rad(45.0f));
	//get view matrix
	Mat4 view = _cam.GetViewMatrix();
	//prepare projection matrix.
	Mat4 proj = Mat4::Identity().Perspective(MathUtil::Deg2Rad(_cam.GetFieldOfView()), 1.0f * SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);
	//model-view-projection transform
	Mat4 mvp = proj * view * model;
	//set the model-view-projection matrix to the shader
	ShaderManager::GetInstance()->GetShader(COLORED_CUBE_SHADER_NAME)->SetUniformMat4(mvp, "mvp");

	//clear the color buffer/depth buffer, and make the background black
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//begin using the shader program object
	ShaderManager::GetInstance()->UseShader(COLORED_CUBE_SHADER_NAME);

	//set opengl viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	//bind the vertex array object
	glBindVertexArray(_VAO);

	//draw the triangles to the buffer
	glDrawElements(GL_TRIANGLES, INDICES_NUM, GL_UNSIGNED_INT, 0);
};

//*************************************************************************
// Class: ColoredCube
// Function Name: Delete
// Argument{s}: -
// Explanation: Delete cube
//*************************************************************************
void ColoredCube::Delete()
{
	glDeleteVertexArrays(1, &_VAO);
	for(int i = 0; i < BUFF_OBJ_NUM; i++)
	{
		glDeleteBuffers(1, &_buff_obj[i]);
	}
};
