//*************************************************************************
// DarkMatter OpenGL 3D Engine Framework
// Class Name: GameObjectManager
// Source File: [gameObjMan.cpp]
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
#include "gameObjMan.h"
#include "objects/multBoxes.h"

//*************************************************************************
// Class: GameObjManager
// Function Name: GameObjManager
// Explanation: constructor
// Argument{s}:
// Other: -
//*************************************************************************
GameObjManager::GameObjManager()
{
}

//*************************************************************************
// Class: GameObjManager
// Function Name: GameObjManager
// Explanation: destructor
// Argument{s}:
// Other: -
//*************************************************************************
GameObjManager::~GameObjManager()
{
	DestroyAllObjects();
}

//*************************************************************************
// Class: GameObjManager
// Function Name: Init
// Explanation: Initialize game objects
// Argument{s}:
// Other: -
//*************************************************************************
void GameObjManager::Init()
{
	AddNewGameObject(new MultBoxes);
}

//*************************************************************************
// Class: GameObjManager
// Function Name: Update
// Explanation: Update game objects
// Argument{s}:
// Other: -
//*************************************************************************
void GameObjManager::Update(float time, const Mouse& mouse, const Keyboard& keyboard)
{
	for(auto it = _obj_list.begin(); it != _obj_list.end();)
	{
		(*it)->Update(time, mouse, keyboard);
		if((*it)->IsKill())
		{
			delete (*it);
			it = _obj_list.erase(it);
		}
		else
		{
			it++;
		}
	}
}

//*************************************************************************
// Class: GameObjManager
// Function Name: Draw
// Explanation: Draw game objects
// Argument{s}:
// Other: -
//*************************************************************************
void GameObjManager::Draw(Camera& cam)
{
	for(auto it = _obj_list.begin(); it != _obj_list.end(); it++)
	{
		(*it)->Draw(cam);
	}
}

//*************************************************************************
// Class: GameObjManager
// Function Name: AddNewGameObjet
// Explanation: Add a new game object to the list
// Argument{s}:
// Other: -
//*************************************************************************
void GameObjManager::AddNewGameObject(GameObjBase* obj)
{
	if (obj != nullptr)
	{
		_obj_list.push_back(obj);
		_obj_list.back()->Init();
	}
}

//*************************************************************************
// Class: GameObjManager
// Function Name: DestroyAllObjects
// Explanation: destroys all objects in the game
// Argument{s}:
// Other: -
//*************************************************************************
void GameObjManager::DestroyAllObjects()
{
	for(auto it = _obj_list.begin(); it != _obj_list.end(); it++)
	{
		delete (*it);
		*it = nullptr;
	}
	_obj_list.clear();
}
