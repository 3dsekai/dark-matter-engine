//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: ModelManager
// Source File: [modelManager.cpp]
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
#include <iostream>
#include "modelManager.h"
#include "modelResourceLib.h"
#include "../meshes/mesh.h"

//*************************************************************************
// static member definition
//*************************************************************************
ModelManager* ModelManager::_instance = nullptr;
std::map<const char*, std::vector<Mesh*>> ModelManager::_model;

//*************************************************************************
// Class: ModelManager
// Function Name: GetInstance
// Explanation: Get the instance to this static singleton class
// Argument{s}:
// Other: -
//*************************************************************************
ModelManager* ModelManager::GetInstance()
{
	if(_instance == nullptr)
	{
		_instance = new ModelManager;
	}
	return _instance;
}

//*************************************************************************
// Class: ModelManager
// Function Name: DestroyInstance
// Explanation: Destroy the instance to this static singleton class
// Argument{s}:
// Other: -
//*************************************************************************
void ModelManager::DestroyInstance()
{
	//release all models
	UnloadAllModels();

	//release the singleton instance
	delete _instance;
	_instance = nullptr;
}

//*************************************************************************
// Class: ModelManager
// Function Name: LoadModel
// Explanation: load model 
// Argument{s}:
// const char* name: the name of the model
// Other: -
//*************************************************************************
void ModelManager::LoadModel(const char* name)
{
	if (_model.find(name) == _model.end())
	{
		_model[name] = std::vector<Mesh*>(0);
		lib_initModel(name, &_model[name]);
	}
}

//*************************************************************************
// Class: ModelManager
// Function Name: UnloadModel
// Explanation: delete specified model
// Argument{s}:
// const char* name: name of the model to delete
// Other: -
//*************************************************************************
void ModelManager::UnloadModel(const char* name)
{
	if(_model.find(name) != _model.end())
	{
//		lib_deleteModel(_model[name]);
		for (auto it = _model[name].begin(); it != _model[name].end(); it++)
		{
			delete *it;
			*it = nullptr;
		}
		_model.erase(name);
	}
}

//*************************************************************************
// Class: ModelManager
// Function Name: GetModel
// Explanation: Get a specified model
// Argument{s}:
// const char* name: name of the model to retrieve
// Other: -
//*************************************************************************
std::vector<Mesh*> ModelManager::GetModel(const char* name)
{
	std::vector<Mesh*> model(0);
	if(_model.find(name) != _model.end())
	{
		model = _model[name];
	}
	else
	{
		std::cout << "Error: Could not find model: " << name << std::endl;
	}
	return model;
}

//*************************************************************************
// Class: ModelManager
// Function Name: UnloadAllModels
// Explanation: Clear all models
// Argument{s}:
// Other: -
//*************************************************************************
void ModelManager::UnloadAllModels()
{
	for(auto it = _model.begin(); it != _model.end(); it++)
	{
		_instance->UnloadModel(it->first);
	}
	_model.clear();
}
