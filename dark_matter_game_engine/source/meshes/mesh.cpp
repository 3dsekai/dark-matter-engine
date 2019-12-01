//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: Mesh
// Source File: [mesh.cpp]
//
// License:
// Copyright(C) <2019> <Christopher Tall>
//
// This software is copyrighted.
// The copyright notice and license information in this document must be
// preserved in every copy of the document AS IS. Attribution to the
// original author of this software must be given in either the
// modified source OR in the product's documentation.
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
#include <GL/glew.h>
#include <iostream>
#include "mesh.h"
#include "../draw/shaderManager.h"
#include "../resource/meshManager.h"
#include "../resource/textureManager.h"
#include "../draw/shader.h"
#include "../math_lib/mat4.h"

Mesh::Mesh(const char* shaderName, const Vec3& pos, const Quat& rot, const Vec3& scale) :
		  _pos(pos),
		  _rot(rot),
		  _scale(scale)
{
	_mDrawParam = new RenderMesh::MeshRenderParam;
	{ //initialize shader parameters
		_mDrawParam->shaderName = shaderName;
		_mDrawParam->mesh.VAO = 0;
		_mDrawParam->mesh.vertNum = 0;
		_mDrawParam->mesh.idxNum = 0;
	}
	{ //initialize material parameters
		_mDrawParam->material.diffuse[0]   = 0;
		_mDrawParam->material.specular[0]  = 1;
		_mDrawParam->material.diffTexId[0] = 0;
		_mDrawParam->material.specTexId[0] = 0;
		_mDrawParam->material.diffMaterialNum = 0;
		_mDrawParam->material.specMaterialNum = 0;
		_mDrawParam->material.shininess = 64;
	}
	//initialize textures
	SetTexture(BLACK_TEXTURE, MATERIAL_DIFFUSE);
	SetTexture(BLACK_TEXTURE, MATERIAL_SPECULAR);
	_mDrawParam->material.diffMaterialNum = 0;
	_mDrawParam->material.specMaterialNum = 0;
};

Mesh::~Mesh()
{
	Delete();
}


//*************************************************************************
// default initialization
//*************************************************************************
void Mesh::Init(std::string meshName, const float* vertices, const uint32_t* indices, int vertNum, int idxNum)
{
	if(MeshManager::GetInstance()->GetMesh(meshName, &_mDrawParam->mesh) == false)
	{
		std::vector<RenderMesh::VAParams> va;
		{ //position coordinates
			RenderMesh::VAParams va1;
			va1.size = 3; //size of attribute
			va1.type = GL_FLOAT; //vertex attribute type
			va1.norm = GL_FALSE; //vertex attribute normalization bool
			va1.stride = 14*sizeof(float); //size of vertex stride
			va1.offset = 0; //offset attribute
			va.push_back(va1);
		}
		{ //texture coordinates
			RenderMesh::VAParams va2;
			va2.size = 2;
			va2.type = GL_FLOAT;
			va2.norm = GL_FALSE;
			va2.stride = 14*sizeof(float);
			va2.offset = 3*sizeof(float);
			va.push_back(va2);
		}
		{ //normals
			RenderMesh::VAParams va3;
			va3.size = 3;
			va3.type = GL_FLOAT;
			va3.norm = GL_FALSE;
			va3.stride = 14*sizeof(float);
			va3.offset = 5*sizeof(float);
			va.push_back(va3);
		}
		{ //tangent
			RenderMesh::VAParams va4;
			va4.size = 3;
			va4.type = GL_FLOAT;
			va4.norm = GL_FALSE;
			va4.stride = 14*sizeof(float);
			va4.offset = 8*sizeof(float);
			va.push_back(va4);
		}
		{ //bitangent
			RenderMesh::VAParams va5;
			va5.size = 3;
			va5.type = GL_FLOAT;
			va5.norm = GL_FALSE;
			va5.stride = 14*sizeof(float);
			va5.offset = 11*sizeof(float);
			va.push_back(va5);
		}

		//initialize the mesh for rendering
		MeshManager::GetInstance()->InitMesh(meshName, vertices, indices, vertNum, idxNum, va);
		MeshManager::GetInstance()->GetMesh(meshName, &_mDrawParam->mesh);
	}
}

//*************************************************************************
// Render Mesh
//*************************************************************************
void Mesh::Draw()
{
	//prepare model matrix
	Mat4 translation = Mat4::Identity().Translate(_pos);
	Mat4 rotation = Mat4::Identity().Rotate(_rot);
	Mat4 scale = Mat4::Identity().Scale(_scale);
	Mat4 model = translation * rotation * scale;

	//draw the mesh
	RenderMesh::DrawMesh(model, *_mDrawParam);
}

//*************************************************************************
// Delete Mesh
//*************************************************************************
void Mesh::Delete()
{
	delete _mDrawParam;
	_mDrawParam = nullptr;
}

//*************************************************************************
// Set Texture to Mesh
//*************************************************************************
void Mesh::SetTexture(const char* texName, MATERIAL_TYPE type)
{
	GLuint texId = TextureManager::GetInstance()->GetTextureId(texName);

	//set the cube color and texture to the shader
	Shader* shader = ShaderManager::GetInstance()->GetShader(_mDrawParam->shaderName);
	if (shader != nullptr)
	{
		shader->UseProgram();
		switch(type)
		{
		case MATERIAL_DIFFUSE:
			{
				if((_mDrawParam->material.diffMaterialNum+1) < MATERIAL_SAMPLER_MAX_NUM)
				{
					int idx = _mDrawParam->material.diffMaterialNum;
					std::string diffSamplerName = "material.diffuse" + std::to_string(idx);
					shader->SetUniformInt(_mDrawParam->material.diffuse[idx], diffSamplerName.c_str());
					_mDrawParam->material.diffTexId[idx] = texId;
					_mDrawParam->material.diffMaterialNum++;
				}
			}
			break;
		case MATERIAL_SPECULAR:
			{
				if ((_mDrawParam->material.specMaterialNum+1) < MATERIAL_SAMPLER_MAX_NUM)
				{
					int idx = _mDrawParam->material.specMaterialNum;
					std::string name = "material.specular" + std::to_string(idx);
					shader->SetUniformInt(_mDrawParam->material.specular[idx], name.c_str());
					_mDrawParam->material.specTexId[idx] = texId;
					_mDrawParam->material.specMaterialNum++;
				}
			}
			break;
		}
	}
}
