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
#include "../main.h"
#include "../meshes/cube.h"
#include "../draw/shaderManager.h"
#include "../draw/shader.h"
#include "../define/draw_define.h"
#include "../math_lib/mat4.h"
#include "../camera/camera.h"
#include "../window/window.h"
//*************************************************************************
// Macro Definitions
//*************************************************************************
#define VERTICES_NUM				(3)
#define VERTICES_ELEM_NUM			(24)

#define POS_ATTRIB_ELEM_NUM			(3)
#define TEX_ATTRIB_ELEM_NUM			(3)

#define VERTEX_STRIDE				(3)

#define INDICES_NUM					(36)

//*************************************************************************
// constants definitions
//*************************************************************************
namespace
{
	//cube position vertices
	const GLfloat pos_coords[VERTICES_ELEM_NUM] =
	{
		// front
		-1.0, -1.0,  1.0, //bottom left
		 1.0, -1.0,  1.0, //bottom right
		 1.0,  1.0,  1.0, //top right
		-1.0,  1.0,  1.0, //top left
		// back
		-1.0, -1.0, -1.0,
		 1.0, -1.0, -1.0,
		 1.0,  1.0, -1.0,
		-1.0,  1.0, -1.0
	};
	
	//cube indices
	const GLuint indices[INDICES_NUM] =
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
}
//*************************************************************************
// Class: Cube
// Function Name: Cube
// Argument{s}: -
// Explanation: Cube constructor
//*************************************************************************
Cube::Cube(const char* shader_name, const Vec3& pos, const Vec3& scale, const Quat& rot, const Vec4& color) :
	MeshBase(shader_name, pos, scale, rot, color, 0)
{
	Init();
};

//*************************************************************************
// Class: Cube
// Function Name: ~Cube
// Argument{s}: -
// Explanation: Cube destructor
//*************************************************************************
Cube::~Cube()
{
	Delete();
};

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
	GLuint _buff_obj[BUFF_OBJ_NUM];

	//generate the vertex buffer and element buffer objects
	glGenBuffers(BUFF_OBJ_NUM, _buff_obj);
	
	//bind the vertex array object
	glBindVertexArray(_VAO);
	
	//bind the vertex data to the position vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, _buff_obj[POS_COORDS_BUFF_OBJ]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_coords), pos_coords, GL_STATIC_DRAW);
	
	//define how the vertex buffer data should be interpreted when a draw call is made for vertex position
	glEnableVertexAttribArray(POS_COORD_ATTRIB);
	glVertexAttribPointer(POS_COORD_ATTRIB,
	POS_ATTRIB_ELEM_NUM,
	GL_FLOAT,
	GL_FALSE,
	VERTEX_STRIDE * sizeof(GLfloat),
	(GLvoid*)0);
	
//	//bind the vertex data to the color vertex buffer object
//	glBindBuffer(GL_ARRAY_BUFFER, _buff_obj[TEX_COORDS_BUFF_OBJ]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(_col_verts), _col_verts, GL_STATIC_DRAW);
//
//	//define how the vertex buffer data should be interpreted when a draw call is made for vertex color
//	glEnableVertexAttribArray(TEX_COORD_ATTRIB);
//	glVertexAttribPointer(TEX_COORD_ATTRIB,
//	TEX_ATTRIB_ELEM_NUM,
//	GL_FLOAT,
//	GL_FALSE,
//	VERTEX_STRIDE * sizeof(GLfloat),
//	(GLvoid*)0);
	
	//bind the index data to the element buffer object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buff_obj[INDEX_BUFF_OBJ]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	//unbind the vertex buffer object
	/*NOTE: can't unbind the element buffer object until the VAO is done being used*/
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	//unbind the vertex array object
	glBindVertexArray(0);

	//delete the buffer objects
	for (int i = 0; i < BUFF_OBJ_NUM; i++)
	{
		glDeleteBuffers(1, &_buff_obj[i]);
	}
};


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
	float w = Window::getInstance()->getWindowWidth();
	float h = Window::getInstance()->getWindowHeight();
	Mat4 proj = Mat4::Identity().Perspective(MathUtil::Deg2Rad(cam.GetFieldOfView()), 1.0f * (w/h), 0.1f, 100.0f);
	//model-view-projection transform
	Mat4 mvp = proj * view * model;

	Shader* shader = ShaderManager::GetInstance()->GetShader(_shader_name);
	if(shader != nullptr)
	{
		//set the model-view-projection matrix to the shader
		shader->SetUniformMat4(mvp, "mvp");
		//set the cube color to the shader
		shader->SetUniformVec4(_color, "cubeColor");
		//begin using the shader program object
		shader->UseProgram();
	}
	//bind the vertex array object
	glBindVertexArray(_VAO);

	//draw the triangles to the buffer
	glDrawElements(GL_TRIANGLES, INDICES_NUM, GL_UNSIGNED_INT, 0);
};

//*************************************************************************
// Class: Cube
// Function Name: Delete
// Argument{s}: -
// Explanation: Delete cube
//*************************************************************************
void Cube::Delete()
{
	glDeleteVertexArrays(1, &_VAO);
};
