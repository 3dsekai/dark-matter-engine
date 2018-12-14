//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: GameMain
// Source File: [gameMain.cpp]
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
// include
//*************************************************************************
#include "gameMain.h"
#include "../main.h"
#include "../input/inputCodes.h"

#include "../draw/shaderManager.h"
#include "../define/shader_define.h"

//*************************************************************************
// static member definitions
//*************************************************************************
GameObjManager* GameMain::_game_obj = nullptr;

//*************************************************************************
// Class: GameMain
// Function Name: GameMain
// Explanation: GameMain Class constructor
// Other: -
//*************************************************************************
GameMain::GameMain()
{
	_isQuit = false;
	_cam = new Camera;
	_keyboard = new Keyboard;
	_mouse = new Mouse;
	_game_obj = new GameObjManager;
}

//*************************************************************************
// Class: GameMain
// Function Name: GameMain
// Explanation: GameMain Class Destructor
// Other: -
//*************************************************************************
GameMain::~GameMain()
{
	//delete mouse
	delete _mouse;
	_mouse = nullptr;
	//delete keyboard
	delete _keyboard;
	_keyboard = nullptr;
	//delete camera
	delete _cam;
	_cam = nullptr;
	//delete game objects
	delete _game_obj;
	_game_obj = nullptr;
	//delete shaders
	ShaderManager::GetInstance()->DestroyInstance();
}

//*************************************************************************
// Class: GameMain
// Function Name: Start
// Explanation: initialize game
// Other: -
//*************************************************************************
void GameMain::Start()
{
	//initialize the game objects
	_game_obj->Init();

	//compile the solid cube shader
	ShaderManager::GetInstance()->LoadShader(
	SOLID_MESH_SHADER_NAME,
	SOLID_MESH_VERTEX_SHADER,
	SOLID_MESH_FRAGMENT_SHADER);

	//compile the texture cube shader
	ShaderManager::GetInstance()->LoadShader(
	TEXTURE_MESH_SHADER_NAME,
	TEXTURE_MESH_VERTEX_SHADER,
	TEXTURE_MESH_FRAGMENT_SHADER);
}

//*************************************************************************
// Class: GameMain
// Function Name: Update
// Explanation: update game
// Other: -
//*************************************************************************
void GameMain::Update()
{
	_cam->ProcessMouseMotion(*_mouse);
	if (_keyboard->IsKeyPressed(KEY_W))
	{ //move forward
		_cam->Move(Camera::CamDir::DIR_FORWARD);
	}
	if (_keyboard->IsKeyPressed(KEY_S))
	{ //move back
		_cam->Move(Camera::CamDir::DIR_BACK);
	}
	if (_keyboard->IsKeyPressed(KEY_A))
	{ //move left
		_cam->Move(Camera::CamDir::DIR_LEFT);
	}
	if (_keyboard->IsKeyPressed(KEY_D))
	{ //move right
		_cam->Move(Camera::CamDir::DIR_RIGHT);
	}

	//update the game objects
	_game_obj->Update(*_mouse, *_keyboard);
}

//*************************************************************************
// Class: GameMain
// Function Name: Draw
// Explanation: draw game
// Other: -
//*************************************************************************
void GameMain::Draw()
{
	//draw the game objects
	_game_obj->Draw(*_cam);
}

//*************************************************************************
// Class: GameMain
// Function Name: ProcessKeys
// [Argument{s}]
// unsigned int state: the new state of the key
// unsigned char key: the detected pressed key
// Explanation: process user keyboard input
// Other: -
//*************************************************************************
void GameMain::ProcessKeys(unsigned int state, unsigned char key)
{
	switch(state)
	{
	case Keyboard::KeyState::KEY_RELEASED:
		_keyboard->OnKeyRelease(key);
		break;
	case Keyboard::KeyState::KEY_PRESSED:
		_keyboard->OnKeyPress(key);
		break;
	default:
		break;
	}

	//quit program when 'escape' is pressed
	if(_keyboard->IsKeyPressed(KEY_ESC))
	{
		Terminate();
	}
}

//*************************************************************************
// Class: GameMain
// Function Name: ProcessMouseButtons
// [Argument{s}]
// int button: The mouse button being pressed
// int state: The state of the button input
// int x: the mouse x position relative to the window
// int y: the mouse y position relative to the window
// Explanation: process mouse button input
// Other: -
//*************************************************************************
void GameMain::ProcessMouseButtons(int button, int state, int x, int y)
{
	switch(button)
	{
	case GLUT_LEFT_BUTTON:
		if(state == GLUT_UP)
		{
			_mouse->OnLeftButtonRelease(x, y);
		}
		else if(state == GLUT_DOWN)
		{
			_mouse->OnLeftButtonPress(x, y);
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if(state == GLUT_UP)
		{
			_mouse->OnRightButtonRelease(x, y);
		}
		else if(state == GLUT_DOWN)
		{
			_mouse->OnRightButtonPress(x, y);
		}
		break;
	case GLUT_MIDDLE_BUTTON:
		//no functionality for the middle button yet...
		break;
	default:
		break;
	}
}

//*************************************************************************
// Class: GameMain
// Function Name: ProcessMouseMotion
// [Argument{s}]
// int x: the mouse x position relative to the window
// int y: the mouse y position relative to the window
// Explanation: process mouse motion
// Other: -
//*************************************************************************
void GameMain::ProcessMouseMotion(int x, int y)
{
	_mouse->OnMouseMove(x, y);
}

//*************************************************************************
// Class: GameMain
// Function Name: Terminate
// Explanation: terminate the game
// Other: -
//*************************************************************************
void GameMain::Terminate()
{
	//quit application
	_isQuit = true;
}

//*************************************************************************
// Class: GameMain
// Function Name: IsTerminate
// Explanation: checks if the game has been terminated
// Other: -
//*************************************************************************
bool GameMain::IsTerminate()
{
	return _isQuit;
}

//*************************************************************************
// Class: GameMain
// Function Name: AddGameObject
// Explanation: add a new game object to the manager list
// Other: -
//*************************************************************************
void GameMain::AddGameObject(GameObjBase* obj)
{
	_game_obj->AddNewGameObject(obj);
}
