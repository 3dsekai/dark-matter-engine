//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: ModelResourceLib
// Source File: [modelResourceManager.cpp]
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
// Include
//*************************************************************************
#include <iostream>
#include <ostream>
#include "modelResourceLib.h"
#include "../meshes/mesh.h"
#include "../draw/renderMesh.h"
#include "../resource/textureManager.h"
#include "../define/material_define.h"
#include "../define/shader_define.h"

//global variables
std::string g_modelPath;
std::string g_modelName = "new_mesh"; //name of model
int meshNum = 0; //number of mesh
//*************************************************************************
// Function Name: InitModel
// Argument{s}:
// const char* path: path for the model data
// std::vector<Mesh*> model: raw mesh container to store model data
// Explanation: load and initialize the model
//*************************************************************************
void lib_initModel(std::string path, std::vector<Mesh*>* model)
{
	Assimp::Importer aiImporter;
	const aiScene* aiScene = aiImporter.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if(aiScene != nullptr)
	{
		if(aiScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || aiScene->mRootNode == nullptr)
		{
			// retrieve the directory path of the filepath
			std::cout << "Assimp Error: " << aiImporter.GetErrorString() << std::endl;
			return;
		}
	}
	g_modelPath = path.substr(0, path.find_last_of('/')) + "/";
	std::string extName = path.substr(path.find_last_of('/') + 1); //name with extension
	g_modelName = extName.substr(0, extName.find_last_of('.')).c_str(); //name without extension
	lib_aiProcessNode(aiScene->mRootNode, aiScene, model);
}
//*************************************************************************
// Function Name: aiProcessNodes
// Argument{s}:
// aiNode *aiNode: The assimp mesh nodes
// const aiScene *aiScene: the loaded assimp scene
// Explanation: process all nodes within an assimp scene
//*************************************************************************
void lib_aiProcessNode(aiNode *aiNode, const aiScene *aiScene, std::vector<Mesh*>* model)
{
	for(uint32_t i = 0; i < aiNode->mNumMeshes; i++)
	{
		aiMesh* aiMesh = aiScene->mMeshes[aiNode->mMeshes[i]];
		model->push_back(lib_aiProcessMesh(aiMesh, aiScene));
	}
	for(uint32_t i = 0; i < aiNode->mNumChildren; i++)
	{
		lib_aiProcessNode(aiNode->mChildren[i], aiScene, model);
	}
}
//*************************************************************************
// Class: ModelResourceLib
// Function Name: aiProcessMesh
// Argument{s}:
// aiMesh *aiMesh: The assimp mesh data
// const aiScene *aiScene: the loaded assimp scene
// Explanation: process all assimp mesh data
//*************************************************************************
Mesh* lib_aiProcessMesh(aiMesh *aiMesh, const aiScene *aiScene)
{
	std::vector<RenderMesh::Vertex> vertices;
	std::vector<uint32_t> indices;

	vertices.reserve(aiMesh->mNumVertices);
	for (unsigned int i = 0; i < aiMesh->mNumVertices; i++)
	{
		RenderMesh::Vertex vtx;
		// positions
		vtx.pos.x = aiMesh->mVertices[i].x;
		vtx.pos.y = aiMesh->mVertices[i].y;
		vtx.pos.z = aiMesh->mVertices[i].z;
		//vertices.push_back(aiMesh->mVertices[i].x);
		//vertices.push_back(aiMesh->mVertices[i].y);
		//vertices.push_back(aiMesh->mVertices[i].z);
		// texture coordinates
		float texCoords[2] = { 0.0f, 0.0f };
		if (aiMesh->mTextureCoords[0])
		{
			texCoords[0] = aiMesh->mTextureCoords[0][i].x;
			texCoords[1] = aiMesh->mTextureCoords[0][i].y;
		}
		vtx.tex_coord.x = texCoords[0];
		vtx.tex_coord.y = texCoords[1];
		//vertices.push_back(texCoords[0]);
		//vertices.push_back(texCoords[1]);
		// normals
		vtx.normal.x = aiMesh->mNormals[i].x;
		vtx.normal.y = aiMesh->mNormals[i].y;
		vtx.normal.z = aiMesh->mNormals[i].z;
		//vertices.push_back(aiMesh->mNormals[i].x);
		//vertices.push_back(aiMesh->mNormals[i].y);
		//vertices.push_back(aiMesh->mNormals[i].z);
		// tangent
		vtx.tangent.x = aiMesh->mTangents[i].x;
		vtx.tangent.y = aiMesh->mTangents[i].y;
		vtx.tangent.z = aiMesh->mTangents[i].z;
		//vertices.push_back(aiMesh->mTangents[i].x);
		//vertices.push_back(aiMesh->mTangents[i].y);
		//vertices.push_back(aiMesh->mTangents[i].z);
		// bitangent
		vtx.bitangent.x = aiMesh->mBitangents[i].x;
		vtx.bitangent.y = aiMesh->mBitangents[i].y;
		vtx.bitangent.z = aiMesh->mBitangents[i].z;
		//vertices.push_back(aiMesh->mBitangents[i].x);
		//vertices.push_back(aiMesh->mBitangents[i].y);
		//vertices.push_back(aiMesh->mBitangents[i].z);
		vertices.push_back(vtx);
	}
	for (uint32_t j = 0; j < aiMesh->mNumFaces; j++)
	{
		aiFace aiFace = aiMesh->mFaces[j];
		for (uint32_t k = 0; k < aiFace.mNumIndices; k++)
		{
			indices.push_back(aiFace.mIndices[k]);
		}
	}
	// process materials
	aiMaterial* aiMaterial = aiScene->mMaterials[aiMesh->mMaterialIndex];

	//diffuse maps
	std::vector<materialData> diffuseMaps;
	lib_loadMaterials(aiMaterial, aiTextureType_DIFFUSE, &diffuseMaps);
	//specular maps
	std::vector<materialData> specularMaps;
	lib_loadMaterials(aiMaterial, aiTextureType_SPECULAR, &specularMaps);
	//normal maps
	//height maps

	//create and return mesh
	Mesh* mesh = new Mesh(TEXTURE_MESH_SHADER_NAME);
	
	std::string meshName = g_modelName + "_mesh" + std::to_string(++meshNum);
	mesh->Init(meshName.c_str(), vertices, indices);
	for (auto it = diffuseMaps.begin(); it != diffuseMaps.end(); it++)
	{
		mesh->SetTexture(it->texName.c_str(), it->type);
	}
	for (auto it = specularMaps.begin(); it != specularMaps.end(); it++)
	{
		mesh->SetTexture(it->texName.c_str(), it->type);
	}
	return mesh;
}

//*************************************************************************
// Function Name: lib_loadMaterials
// Argument{s}:
// aiMaterial* aiMat: assimp material data
// aiTextureType matType: the type of material to retrieve
// vector<materialData>* maps: the material data array to set
//*************************************************************************
void lib_loadMaterials(aiMaterial* aiMat, aiTextureType matType, std::vector<materialData>* maps)
{
	if(aiMat != nullptr)
	{
		for (uint32_t i = 0; i < aiMat->GetTextureCount(matType); i++)
		{
			//load texture
			aiString aiPath;
			aiMat->GetTexture(matType, i, &aiPath);
			std::string path = g_modelPath + std::string(aiPath.C_Str());
			TextureManager::GetInstance()->LoadTexture(path.c_str());
			if (TextureManager::GetInstance()->GetTextureId(path.c_str()) == 0)
			{
				std::cout << "modelResourceLib Error: Texture could not be loaded." << std::endl;
			}
			//set material data
			materialData data;
			data.texName = path;
			data.type = static_cast<MATERIAL_TYPE>(matType);
			maps->push_back(data);
		}
	}
}
