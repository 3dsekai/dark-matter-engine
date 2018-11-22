//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: ShaderManager
// Source File: [shaderManager.cpp]
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
#include "shaderManager.h"
#include "shader.h"

//*************************************************************************
// static member definition
//*************************************************************************
ShaderManager* ShaderManager::_instance = nullptr;
std::map<const char*, Shader*> ShaderManager::_shaders;

//*************************************************************************
// Class: ShaderManager
// Function Name: GetInstance
// Explanation: Get the instance to this static singleton class
// Argument{s}:
// Other: -
//*************************************************************************
ShaderManager* ShaderManager::GetInstance()
{
	if(_instance == nullptr)
	{
		_instance = new ShaderManager;
	}
	return _instance;
}

//*************************************************************************
// Class: ShaderManager
// Function Name: GetInstance
// Explanation: Destroy the instance to this static singleton class
// Argument{s}:
// Other: -
//*************************************************************************
void ShaderManager::DestroyInstance()
{
	//release all shader resources
	ClearAllShaders();

	//release the singleton instance
	delete _instance;
	_instance = nullptr;
}


//*************************************************************************
// Class: ShaderManager
// Function Name: LoadShader
// Explanation: Load a shader resource
// // Argument{s}:
// const char* vert_file: the full path to the vertex shader file
// const char* frag_file: the full path to the fragment shader file
// const char* geom_file: the full path to the geometry shader file
// const char* name: the name of this shader object
// Other: -
//*************************************************************************
void ShaderManager::LoadShader(const char* name, const GLchar* vert_file, const GLchar* frag_file, const GLchar* geom_file)
{
	if (_shaders.find(name) == _shaders.end())
	{
		_shaders[name] = new Shader;
		_shaders[name]->Compile(vert_file, frag_file, geom_file);
	}
}

//*************************************************************************
// Class: ShaderManager
// Function Name: UseShader
// Explanation: use a specified shader program
// Argument{s}:
// const char* name: name of the shader to use
// Other: -
//*************************************************************************
void ShaderManager::UseShader(const char* name)
{
	if(_shaders.find(name) != _shaders.end())
	{
		_shaders[name]->UseProgram();
	}
}

//*************************************************************************
// Class: ShaderManager
// Function Name: DeleteShader
// Explanation: delete specified shader
// Argument{s}:
// const char* name: name of the shader to delete
// Other: -
//*************************************************************************
void ShaderManager::DeleteShader(const char* name)
{
	if(_shaders.find(name) != _shaders.end())
	{
		delete _shaders[name];
		_shaders[name] = nullptr;
		_shaders.erase(name);
	}
}

//*************************************************************************
// Class: ShaderManager
// Function Name: GetShader
// Explanation: Get a specified shader resource
// Argument{s}:
// const char* name: name of the shader to retrieve
// Other: -
//*************************************************************************
Shader* ShaderManager::GetShader(const char* name)
{
	Shader* shader = nullptr;
	if(_shaders.find(name) != _shaders.end())
	{
		shader = _shaders[name];
	}
	return shader;
}

//*************************************************************************
// Class: ShaderManager
// Function Name: ClearAllShaders
// Explanation: Clear all shader data
// Argument{s}:
// Other: -
//*************************************************************************
void ShaderManager::ClearAllShaders()
{
	for(auto it = _shaders.begin(); it != _shaders.end(); it++)
	{
		delete it->second;
		it->second = nullptr;
	}
	//delete all shaders
	_shaders.clear();
}


//*************************************************************************
// Class: ShaderManager
// Function Name: ShaderManager
// Explanation: constructor
// Argument{s}:
// Other: -
//*************************************************************************
ShaderManager::ShaderManager()
{
}

//*************************************************************************
// Class: ShaderManager
// Function Name: ShaderManager
// Explanation: destructor
// Argument{s}:
// Other: -
//*************************************************************************
ShaderManager::~ShaderManager()
{
}

//*************************************************************************
// Class: ShaderManager
// Function Name: ShaderManager
// Explanation: copy constructor (to prevent the copying of this singleton class)
// Argument{s}:
// Other: -
//*************************************************************************
ShaderManager::ShaderManager(const ShaderManager &obj)
{
}
