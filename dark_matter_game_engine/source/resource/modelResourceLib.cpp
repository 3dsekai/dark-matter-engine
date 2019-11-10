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
#include "../define/material_define.h"
#include "../resource/textureManager.h"
using namespace std;

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
		if(!(aiScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) && aiScene->mRootNode != nullptr)
		{
			// retrieve the directory path of the filepath
			string directory = path.substr(0, path.find_last_of('/'));
			lib_aiProcessNode(aiScene->mRootNode, aiScene, model);
			return;
		}
	}
	cout << "Assimp Error: " << aiImporter.GetErrorString() << endl;
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
	vector<float> vertices;
	vector<uint32_t> indices;

	for(unsigned int i = 0; i < aiMesh->mNumVertices; i++)
	{
		Vec3 vec;
		// positions
		vertices.push_back(aiMesh->mVertices[i].x);
		vertices.push_back(aiMesh->mVertices[i].y);
		vertices.push_back(aiMesh->mVertices[i].z);
		// normals
		vertices.push_back(aiMesh->mNormals[i].x);
		vertices.push_back(aiMesh->mNormals[i].y);
		vertices.push_back(aiMesh->mNormals[i].z);
		// texture coordinates
		float texCoords[2] = {0.0f, 0.0f};
		if(aiMesh->mTextureCoords[0])
		{
			texCoords[0] = aiMesh->mTextureCoords[0][i].x;
			texCoords[1] = aiMesh->mTextureCoords[0][i].y;
		}
		vertices.push_back(texCoords[0]);
		vertices.push_back(texCoords[1]);
//		// tangent
//		vertices.push_back(aiMesh->mTangents[i].x);
//		vertices.push_back(aiMesh->mTangents[i].y);
//		vertices.push_back(aiMesh->mTangents[i].z);
//		// bitangent
//		vertices.push_back(mesh->mBitangents[i].x);
//		vertices.push_back(mesh->mBitangents[i].y);
//		vertices.push_back(mesh->mBitangents[i].z);
	}
	for(uint32_t i = 0; i < aiMesh->mNumFaces; i++)
	{
		aiFace aiFace = aiMesh->mFaces[i];
		for(uint32_t j = 0; j < aiFace.mNumIndices; j++)
		{
			indices.push_back(aiFace.mIndices[j]);
		}
	}
	// process materials
	aiMaterial* aiMaterial = aiScene->mMaterials[aiMesh->mMaterialIndex];
	
	//diffuse maps
	vector<materialData> diffuseMaps;
	lib_loadMaterials(aiMaterial, aiTextureType_DIFFUSE, &diffuseMaps);
	//specular maps
	vector<materialData> specularMaps;
	lib_loadMaterials(aiMaterial, aiTextureType_SPECULAR, &specularMaps);
	//normal maps
	//height maps
	
	//create and return mesh
	Mesh* mesh = new Mesh("someshader");
	mesh->Init("somemesh", vertices.data(), indices.data(), vertices.size(), indices.size());
	for (auto it = diffuseMaps.begin(); it != diffuseMaps.end(); it++) mesh->SetTexture(it->texName, it->type);
	for (auto it = specularMaps.begin(); it != specularMaps.end(); it++) mesh->SetTexture(it->texName, it->type);
	return mesh;
}

//*************************************************************************
// Function Name: lib_loadMaterials
// Argument{s}:
// aiMaterial* aiMat: assimp material data
// aiTextureType matType: the type of material to retrieve
// vector<materialData>* maps: the material data array to set
//*************************************************************************
void lib_loadMaterials(aiMaterial* aiMat, aiTextureType matType, vector<materialData>* maps)
{
	if(aiMat != nullptr)
	{
		for (uint32_t i = 0; i < aiMat->GetTextureCount(matType); i++)
		{
			//load texture
			aiString texPath;
			aiMat->GetTexture(matType, i, &texPath);
			TextureManager::GetInstance()->LoadTexture(texPath.C_Str());
			if (TextureManager::GetInstance()->GetTextureId(texPath.C_Str()) == 0)
			{
				cout << "modelResourceLib Error: Texture could not be loaded." << endl;
			}
			//set material data
			materialData data;
			data.texName = texPath.C_Str();
			data.type = (MATERIAL_TYPE)matType;
			maps->push_back(data);
		}
	}
}
//*************************************************************************
// Class: ModelResourceLib
// Function Name: DeleteModel
// Argument{s}:
// const char* path: path for the model data
// Explanation: delete and release the model data
//*************************************************************************
void lib_deleteModel(const char* path)
{
}
