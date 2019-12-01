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
#include "cube.h"
#include "../math_lib/mat4.h"
#include "../resource/meshManager.h"

//*************************************************************************
// Macro Definitions
//*************************************************************************
#define CUBE_ATTRIBUTE_NUM (192)
#define CUBE_INDICES_NUM (36)

//*************************************************************************
// constants definitions
//*************************************************************************
namespace
{
	//cube vertices
	const float cubeVerts[CUBE_ATTRIBUTE_NUM] =
	{
		//  pos coords     tex coords   normals
		//front
		-1.0, -1.0,  1.0,  0.0f, 0.0f,  0.0f,  0.0f,  1.0f, //bottom left
		 1.0, -1.0,  1.0,  1.0f, 0.0f,  0.0f,  0.0f,  1.0f, //bottom right
		 1.0,  1.0,  1.0,  1.0f, 1.0f,  0.0f,  0.0f,  1.0f, //top right
		-1.0,  1.0,  1.0,  0.0f, 1.0f,  0.0f,  0.0f,  1.0f, //top left
		// top
		-1.0,  1.0,  1.0,  0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
		 1.0,  1.0,  1.0,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
		 1.0,  1.0, -1.0,  1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
		-1.0,  1.0, -1.0,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
		// back
		 1.0, -1.0, -1.0,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
		-1.0, -1.0, -1.0,  1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
		-1.0,  1.0, -1.0,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
		 1.0,  1.0, -1.0,  0.0f, 1.0f,  0.0f,  0.0f, -1.0f,
		// bottom
		-1.0, -1.0, -1.0,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
		 1.0, -1.0, -1.0,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
		 1.0, -1.0,  1.0,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
		-1.0, -1.0,  1.0,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
		// left
		-1.0, -1.0, -1.0,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
		-1.0, -1.0,  1.0,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
		-1.0,  1.0,  1.0,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
		-1.0,  1.0, -1.0,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
		// right
		 1.0, -1.0,  1.0,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
		 1.0, -1.0, -1.0,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
		 1.0,  1.0, -1.0,  1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
		 1.0,  1.0,  1.0,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
	};

	//cube indices
	const uint32_t cubeIdx[CUBE_INDICES_NUM] =
	{
		// front
		0, 1, 2,
		2, 3, 0,
		// top
		4, 5, 6,
		6, 7, 4,
		// top
		8,  9,  10,
		10, 11, 8,
		// bottom
		12, 13, 14,
		14, 15, 12,
		// left
		16, 17, 18,
		18, 19, 16,
		// right
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
Cube::Cube(const char* shaderName, const Vec3& pos, const Quat& rot, const Vec3& scale) :
	Mesh(shaderName, pos, rot, scale)
{
	Init("cube", cubeVerts, cubeIdx, CUBE_ATTRIBUTE_NUM, CUBE_INDICES_NUM);
}

//*************************************************************************
// Class: Cube
// Function Name: Init
// Explanation: Initialize cube
//*************************************************************************
void Cube::Init(std::string meshName, const float* vertices, const uint32_t* indices, int vertNum, int idxNum)
{
	if(MeshManager::GetInstance()->GetMesh(meshName, &_mDrawParam->mesh) == false)
	{
		std::vector<RenderMesh::VAParams> va;
		{ //position coordinates
			RenderMesh::VAParams va1;
			va1.size = 3; //size of attribute
			va1.type = GL_FLOAT; //vertex attribute type
			va1.norm = GL_FALSE; //vertex attribute normalization bool
			va1.stride = 8*sizeof(float); //size of vertex stride
			va1.offset = 0; //offset attribute
			va.push_back(va1);
		}
		{ //texture coordinates
			RenderMesh::VAParams va2;
			va2.size = 2;
			va2.type = GL_FLOAT;
			va2.norm = GL_FALSE;
			va2.stride = 8*sizeof(float);
			va2.offset = 3*sizeof(float);
			va.push_back(va2);
		}
		{ //normals
			RenderMesh::VAParams va3;
			va3.size = 3;
			va3.type = GL_FLOAT;
			va3.norm = GL_FALSE;
			va3.stride = 8*sizeof(float);
			va3.offset = 5*sizeof(float);
			va.push_back(va3);
		}

		//initialize the mesh for rendering
		MeshManager::GetInstance()->InitMesh(meshName, vertices, indices, vertNum, idxNum, va);
		MeshManager::GetInstance()->GetMesh(meshName, &_mDrawParam->mesh);
	}
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
