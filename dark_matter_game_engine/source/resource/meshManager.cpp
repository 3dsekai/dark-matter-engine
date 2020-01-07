//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: MeshManager
// Source File: [meshManager.cpp]
//
// License:
// Copyright(C) <2019>  <Christopher Tall>
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
#include "meshManager.h"

//*************************************************************************
// static member definition
//*************************************************************************
MeshManager* MeshManager::_instance = nullptr;
std::map <std::string, RenderMesh::MeshParam* > MeshManager::_meshes;

//*************************************************************************
// Class: MeshManager
// Function Name: GetInstance
// Explanation: Get the instance to this static singleton class
// Argument{s}:
// Other: -
//*************************************************************************
MeshManager* MeshManager::GetInstance()
{
	if(_instance == nullptr)
	{
		_instance = new MeshManager;
	}
	return _instance;
}

//*************************************************************************
// Class: MeshManager
// Function Name: DestroyInstance
// Explanation: Destroy the instance to this static singleton class
// Argument{s}:
// Other: -
//*************************************************************************
void MeshManager::DestroyInstance()
{
	//release all mesh resources
	ClearAllMeshes();

	//release the singleton instance
	delete _instance;
	_instance = nullptr;
}

//*************************************************************************
// Class: MeshManager
// Function Name: InitAllMeshes
// Explanation: Init all meshes
// Argument{s}:
// Other: -
//*************************************************************************
void MeshManager::InitAllMeshes()
{
}

//*************************************************************************
// Class: MeshManager
// Function Name: InitMesh
// Explanation: Initialize a mesh
// Argument{s}:
// const char* name: the name of the mesh
// Other: -
//*************************************************************************
void MeshManager::InitMesh(const char* name, const float* vertices, const uint32_t* indices, int vertNum, int idxNum, const std::vector<RenderMesh::VAParams>& va)
{
	if (_meshes.find(name) == _meshes.end())
	{
		_meshes.insert(std::pair<std::string, RenderMesh::MeshParam*>(name, new RenderMesh::MeshParam));
		_meshes[name]->vertNum = vertNum;
		_meshes[name]->idxNum = idxNum;
		RenderMesh::InitMesh(vertices, indices, _meshes[name], va);
	}
}

//*************************************************************************
// Class: MeshManager
// Function Name: DeleteMesh
// Explanation: delete specified mesh
// Argument{s}:
// const char* name: name of the mesh to delete
// Other: -
//*************************************************************************
void MeshManager::DeleteMesh(const char* name)
{
	if(_meshes.find(name) != _meshes.end())
	{
		RenderMesh::DeleteMesh(_meshes[name]);
		delete _meshes[name];
		_meshes[name] = nullptr;
		_meshes.erase(name);
	}
}

//*************************************************************************
// Class: MeshManager
// Function Name: GetMesh
// Explanation: Get a specified mesh
// Argument{s}:
// const char* name: name of the mesh to retrieve
// Other: -
//*************************************************************************
bool MeshManager::GetMesh(const char* name, RenderMesh::MeshParam* mesh)
{
	bool success = true;
	if(_meshes.find(name) != _meshes.end())
	{
		*mesh = *_meshes[name];
	}
	else
	{
		std::cout << "Could not find mesh: " << name << std::endl;
		success = false;
	}
	return success;
}

//*************************************************************************
// Class: MeshManager
// Function Name: ClearAllMeshes
// Explanation: Clear all meshes
// Argument{s}:
// Other: -
//*************************************************************************
void MeshManager::ClearAllMeshes()
{
	for(auto it = _meshes.begin(); it != _meshes.end(); it++)
	{
		RenderMesh::DeleteMesh(it->second);
		delete it->second;
		it->second = nullptr;
	}
	_meshes.clear();
}
