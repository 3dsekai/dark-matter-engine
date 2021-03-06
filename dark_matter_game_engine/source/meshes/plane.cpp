//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: Plane
// Source File: [plane.cpp]
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
#include "plane.h"
#include "../math_lib/mat4.h"
#include "../resource/meshManager.h"
//*************************************************************************
// Macro Definitions
//*************************************************************************
#define PLANE_ATTRIBUTE_NUM (32)
#define PLANE_INDICES_NUM (6)
#define PLANE_STRIDE_LENGTH (8)

//*************************************************************************
// constants definitions
//*************************************************************************
namespace
{
	//plane vertices
	const float planeVerts[PLANE_ATTRIBUTE_NUM] =
	{
		/*pos coord           tex coord  normals*/
		//front
		-1.0, -1.0,  1.0,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f, //bottom left
		 1.0, -1.0,  1.0,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,//bottom right
		 1.0,  1.0,  1.0,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,//top right
		-1.0,  1.0,  1.0,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,//top left
	};

	//indices
	const uint32_t planeIdx[PLANE_INDICES_NUM] =
	{
		0, 1, 2,
		2, 3, 0
	};
}
//*************************************************************************
// Class: Plane
// Function Name: Plane
// Argument{s}: -
// Explanation: Plane constructor
//*************************************************************************
Plane::Plane(const char* shaderName, const Vec3& pos, const Quat& rot, const Vec3& scale) :
	Mesh(shaderName, pos, rot, scale)
{
//	Init("plane", planeVerts, planeIdx, PLANE_ATTRIBUTE_NUM, PLANE_INDICES_NUM);
	int vtx_num = PLANE_ATTRIBUTE_NUM/PLANE_STRIDE_LENGTH;
	//set mesh data
	_meshName = "plane";
	_mDrawParam->mesh.vertNum = vtx_num;
	_mDrawParam->mesh.idxNum = PLANE_INDICES_NUM;

	//fill in vertices
	_vertices.reserve(PLANE_ATTRIBUTE_NUM);
	for(int i = 0; i < vtx_num; i++)
	{
		int offset = i*PLANE_STRIDE_LENGTH;
		RenderMesh::Vertex vtx;
		//position
		vtx.pos.x = planeVerts[offset];
		vtx.pos.y = planeVerts[offset+1];
		vtx.pos.z = planeVerts[offset+2];
		// texture coordinates
		vtx.tex_coord.x = planeVerts[offset+3];
		vtx.tex_coord.y = planeVerts[offset+4];
		// normals
		vtx.normal.x = planeVerts[offset+5];
		vtx.normal.y = planeVerts[offset+6];
		vtx.normal.z = planeVerts[offset+7];
		_vertices.push_back(vtx);
	}

	//fill in indices
	_indices = std::vector<uint32_t>(planeIdx, planeIdx+sizeof(planeIdx)/sizeof(uint32_t));

	//prepare vertex attributes
	std::vector<RenderMesh::VAParams> va;
	{ //position coordinates
		RenderMesh::VAParams va1;
		va1.size = 3; //size of attribute
		va1.type = GL_FLOAT; //vertex attribute type
		va1.norm = GL_FALSE; //vertex attribute normalization bool
		va1.stride = sizeof(RenderMesh::Vertex); //size of vertex stride
		va1.offset = 0; //offset attribute
		va.push_back(va1);
	}
	{ //texture coordinates
		RenderMesh::VAParams va2;
		va2.size = 2;
		va2.type = GL_FLOAT;
		va2.norm = GL_FALSE;
		va2.stride = sizeof(RenderMesh::Vertex);
		va2.offset = offsetof(RenderMesh::Vertex, RenderMesh::Vertex::tex_coord);
		va.push_back(va2);
	}
	{ //normals
		RenderMesh::VAParams va3;
		va3.size = 3;
		va3.type = GL_FLOAT;
		va3.norm = GL_FALSE;
		va3.stride = sizeof(RenderMesh::Vertex);
		va3.offset = offsetof(RenderMesh::Vertex, RenderMesh::Vertex::normal);
		va.push_back(va3);
	}
	//initialize the mesh for rendering
	RenderMesh::InitMesh(_vertices, _indices, &_mDrawParam->mesh, va);
}

//*************************************************************************
// Class: Plane
// Function Name: ~Plane
// Argument{s}: -
// Explanation: Plane destructor
//*************************************************************************
Plane::~Plane()
{
	Delete();
}

//*************************************************************************
// Class: Plane
// Function Name: Init
// Explanation: Initialize plane
//*************************************************************************
//void Plane::Init(const char* meshName, const std::vector<RenderMesh::Vertex>& vertices, const std::vector<uint32_t>& indices)
//{
//	if(MeshManager::GetInstance()->GetMesh(meshName, &_mDrawParam->mesh) == false)
//	{
//		std::vector<RenderMesh::VAParams> va;
//		{ //position coordinates
//			RenderMesh::VAParams va1;
//			va1.size = 3; //size of attribute
//			va1.type = GL_FLOAT; //vertex attribute type
//			va1.norm = GL_FALSE; //vertex attribute normalization bool
//			va1.stride = 8*sizeof(float); //size of vertex stride
//			va1.offset = 0; //offset attribute
//			va.push_back(va1);
//		}
//		{ //texture coordinates
//			RenderMesh::VAParams va2;
//			va2.size = 2;
//			va2.type = GL_FLOAT;
//			va2.norm = GL_FALSE;
//			va2.stride = 8*sizeof(float);
//			va2.offset = 3*sizeof(float);
//			va.push_back(va2);
//		}
//		{ //normals
//			RenderMesh::VAParams va3;
//			va3.size = 3;
//			va3.type = GL_FLOAT;
//			va3.norm = GL_FALSE;
//			va3.stride = 8*sizeof(float);
//			va3.offset = 5*sizeof(float);
//			va.push_back(va3);
//		}
//
//		//initialize the mesh for rendering
//		MeshManager::GetInstance()->InitMesh(meshName, vertices, indices, vertNum, idxNum, va);
//		MeshManager::GetInstance()->GetMesh(meshName, &_mDrawParam->mesh);
//	}
//}
