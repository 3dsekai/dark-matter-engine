//*************************************************************************
// DarkMatter OpenGL 3D Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: GameObjFactory
// Source File: [gameObjFactory.h]
//
// License:
// Copyright(C) <2018>  <Christopher Tall>
//
// This is software is copyrighted.
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
#ifndef _GAME_OBJ_FACTORY_H_
#define _GAME_OBJ_FACTORY_H_

//*************************************************************************
// Includes
//*************************************************************************
#include "createGameObjId.h"
#include "../game_main/gameMain.h"

class GameObjBase;
//*************************************************************************
// Game Object Factory Class
//*************************************************************************
class GameObjFactory
{
public:
	GameObjFactory() = default;
	~GameObjFactory() = default;

	template<class T> 
	T* CreateGameObject(CREATE_ID id);

private:
	GameObjBase* GenerateGameObject(CREATE_ID id);
};

//*************************************************************************
// Class: GameObjFactory
// Function Name: CreateNewGameObject
// Explanation: create a new game object and add it to the list
// Argument{s}:
// CREATE_ID id: the id of the object to instantiate
// Other: -
//*************************************************************************
template<class T>
T* GameObjFactory::CreateGameObject(CREATE_ID id)
{
	auto obj = CreateGameObj(id);
	if (obj != nullptr)
	{
		GameMain::AddGameObject(obj);
	}
	return dynamic_cast<T*>(obj);
}

#endif

