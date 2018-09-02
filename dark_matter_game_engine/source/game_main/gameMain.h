//*************************************************************************
// DarkMatter OpenGL 3D Engine Framework
// Class Name: GameMain
// Source File: [gameMain.h]
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
#ifndef _GAMEMAIN_H_
#define _GAMEMAIN_H_

//*************************************************************************
// Includes
//*************************************************************************
#include "../meshes/cube.h"
#include "../input/mouse.h"
#include "../input/keyboard.h"
#include "../camera/camera.h"
#include "../game_object/gameObjMan.h"
#include "../game_object/gameObjBase.h"

//*************************************************************************
// Game Loop Class
//*************************************************************************
class GameMain
{
public:
	GameMain();
	~GameMain();

	//initialization
	void Start();

	//game update
	void Update();

	//rendering
	void Draw();

	//user input
	void ProcessKeys(unsigned int state, unsigned char key);
	void ProcessMouseButtons(int button, int state, int x, int y);
	void ProcessMouseMotion(int x, int y);

	//game termination
	void Terminate();
	
	//add a new game object to the game
	static void AddGameObject(GameObjBase* obj);

private:
	Cube* _cube;
	Keyboard* _keyboard;
	Mouse* _mouse;
	Camera* _cam;
	static GameObjManager* _game_obj;
};

#endif
