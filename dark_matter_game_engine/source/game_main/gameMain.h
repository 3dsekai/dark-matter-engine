//*************************************************************************
// DarkMatter OpenGL 3D Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: GameMain
// Source File: [gameMain.h]
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
#ifndef _GAMEMAIN_H_
#define _GAMEMAIN_H_

//*************************************************************************
// Includes
//*************************************************************************
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
	bool IsTerminate();
	
	//add a new game object to the game
	static void AddGameObject(GameObjBase* obj);

private:
	bool _isQuit; //check if user quit game
	Keyboard* _keyboard;
	Mouse* _mouse;
	Camera* _cam;
	static GameObjManager* _game_obj;
};

#endif
