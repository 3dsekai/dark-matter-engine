//*************************************************************************
// DarkMatter OpenGL 3D Engine Framework
// Class Name: GameObjFactory
// Source File: [gameObjFactory.cpp]
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
#include "gameObjFactory.h"
#include "objects/multBoxes.h"

//*************************************************************************
// Class: GameObjFactory
// Function Name: CreateGameObject
// Explanation: create a new instance of the specified object
// Argument{s}:
// Other: -
//*************************************************************************
GameObjBase* GameObjFactory::GenerateGameObject(CREATE_ID id)
{
	switch (id)
	{
	case CREATE_OBJ_ID_BOXES:
		return new MultBoxes;
		break;
	}
	return nullptr;
}