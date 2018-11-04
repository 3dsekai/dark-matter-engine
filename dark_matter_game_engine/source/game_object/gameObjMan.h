//*************************************************************************
// DarkMatter OpenGL 3D Engine Framework
// Class Name: GameObjManager
// Source File: [gameObjMan.h]
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
#ifndef _GAME_OBJ_MAN_H_
#define _GAME_OBJ_MAN_H_

//*************************************************************************
// Includes
//*************************************************************************
#include <vector>

class GameObjBase;
class Mouse;
class Keyboard;
class Camera;

//*************************************************************************
// Class
//*************************************************************************
class GameObjManager
{
public:
	GameObjManager();
	~GameObjManager();

private:

	void DestroyAllObjects();
public:
	void Init();
	void Update(float time, const Mouse& mouse, const Keyboard& keyboard);
	void Draw(Camera& cam);
	void AddNewGameObject(GameObjBase* obj);

private:
	std::vector<GameObjBase*> _obj_list;
};


#endif
