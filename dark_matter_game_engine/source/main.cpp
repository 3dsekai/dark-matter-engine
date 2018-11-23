//*************************************************************************
// Dark Matter OpenGL 3D Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Source file: [main.cpp]
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
//standard C/C++ libraries
#include <stdlib.h>
#include <stdio.h>

//engine headers
#include "main.h"
#include "game_main/gameMain.h"
#include "window/window.h"

//*************************************************************************
// Function Declarations
//*************************************************************************
int mainGameLoop();
void updateGame();
void renderGame();
void resizeWindow(int width, int height);
void keyboardPress(unsigned char key, int x, int y);
void keyboardRelease(unsigned char key, int x, int y);
void mouseButtonInput(int button, int state, int x, int y);
void mouseMotionInput(int x, int y);
void deleteGame();
void idleProc();
void closeProc();

//*************************************************************************
// Global Variables
//*************************************************************************
static GameMain* game = nullptr;

//*************************************************************************
// [Class] -
// [Function Name] Main
// [Argument{s}]:
// int argc: the number of command line arguments
// char **argv: a character string array of command line arguments
// [Explanation] The main function for the DeepFreeze game engine.
// Initializes GLUT, GLEW, OPENGL and the game loop.
// [Other] -
// [Resources] -
//*************************************************************************
int main(int argc, char **argv)
{
	//GLUT man pages and initialization:
	//http://www.cs.uccs.edu/~ssemwal/man.html
	//http://www.lighthouse3d.com/tutorials/glut-tutorial/initialization/

	//initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE); //initializes the modes of display for the window

	glutInitContextVersion(3, 3); //select which OpenGL version is requested when the context is actually created
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitContextFlags(GLUT_DEBUG);

	//initialize and create window
	glutInitWindowPosition(SCREEN_POS_X, SCREEN_POS_Y); //sets the position of the window
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT); //sets the dimensions of the window
	glutCreateWindow("DarkMatter OpenGL Game Engine"); //sets the text in the window's title bar

	//register draw callbacks
	glutDisplayFunc(idleProc); //calls draw function everytime the screen needs to be redrawn
	glutReshapeFunc(resizeWindow); //manages the height and width of a window when it is resized
	glutIdleFunc(idleProc); //sets idle callback function to perform background processing when window system events aren't being received
	glutCloseFunc(closeProc); //callback for when a glut window is closed

	//mouse and keyboard callbacks
	glutKeyboardFunc(keyboardPress); //processes keyboard key press
	glutKeyboardUpFunc(keyboardRelease); //processes keyboard key release
	glutMouseFunc(mouseButtonInput); //processes mouse click events
	glutMotionFunc(mouseMotionInput); //processes mouse motion when a button is being pressed
	//glutPassiveMotionFunc(MouseMotionInput); //processes mouse motion without button press
	//glutMouseWheelFunc(mouseWheel); //processes mouse wheel events (this function isn't portable and maybe shouldn't be used)

	//return from main loop when the window is closed
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	//initialize glew
	glewExperimental = GL_TRUE;
	glewInit();

	//print context information
	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));
	printf("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
 
	//create the main game object
	game = new GameMain;

	//start the engine!
	game->Start();

	// enter the game loop
	mainGameLoop();

	//delete the entire game object
	deleteGame();
	//destroy window
	Window::getInstance()->destroyInstance();

	return 0;
}

//*************************************************************************
// [Class] -
// [Function Name] mainGameLoop
// [Argument{s}]: -
// [Explanation] The main game loop. Implements a fixed time step for
// updating with variable rendering
// [Other] -
// [Resources]
// cudos to Bob Nystrom's excellent chapter on the Game Loop pattern:
// http://gameprogrammingpatterns.com/game-loop.html
//*************************************************************************
int mainGameLoop()
{
	double prevTime = glutGet(GLUT_ELAPSED_TIME) * 1.0;
	double lag = 0.0;

	//commence the game loop
	while (1)
	{
		//break out of game loop if user quit the game
		if (game->IsTerminate())
		{
			glutLeaveMainLoop();
			break;
		}

		double crntTime = glutGet(GLUT_ELAPSED_TIME) * 1.0;	//get current real world time
		double elapTime = crntTime - prevTime;				//get the elapsed time from the previous update cycle to now
		prevTime = crntTime;								//record the previous real world time
		lag += elapTime;									//get lag between real world time and game time

		//update the game enough times to make up for lag
		while (lag >= FPS_TO_MS_60)
		{
			updateGame();
			lag -= FPS_TO_MS_60;
		}
		renderGame();
		//renderGame(lag / FPS_TO_MS_60);

		//process window events (keyboard, mouse, win resize, etc)
		glutMainLoopEvent();
	}
	return 0;
}

//*************************************************************************
// [Class] -
// [Function Name] updateGame
// [Argument{s}]: -
// [Explanation] Updates the entire game.
// [Other] -
// [Resources] -
//*************************************************************************
void updateGame()
{
	game->Update();
}
//*************************************************************************
// [Class] -
// [Function Name] renderGame
// [Argument{s}]: -
// [Explanation] Calls the draw function from the game loop to draw
// the current scene.
// [Other] glutDisplayFunc and glutIdleFunc requires this method to
// render scenes to the application window.
// [Resources]
// https://www.opengl.org/resources/libraries/glut/spec3/node46.html
//*************************************************************************
void renderGame()
{
	//clear the color buffer/depth buffer, and make the background grey
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	game->Draw();
	glutSwapBuffers();
}

//*************************************************************************
// [Class] -
// [Function Name] resizeWindow
// [Argument{s}]
// int width: window width
// int height: window height
// [Explanation] Manages the dimensions of a window when it is resized
// [Other] glutReshapeFunc requires this function to
// resize the application window.
// [Resources]
// https://www.opengl.org/resources/libraries/glut/spec3/node48.html
//*************************************************************************
void resizeWindow(int width, int height)
{
	//set opengl viewport dimensions
	if (height == 0) height = 1;
	glViewport(0, 0, width, height);

	Window::getInstance()->setWindowWidth(width * 1.0f);
	Window::getInstance()->setWindowHeight(height * 1.0f);
}

//*************************************************************************
// [Class] -
// [Function Name] keyboardPress
// [Argument{s}]
// unsigned char key: the pressed ASCII character key
// int x: x position of the mouse when the key was pressed
// int y: y position of the mouse when the key was pressed
// [Explanation] Makes calls to the method that processes keyboard press events.
// [Other] glutKeyboardFunc requires this callback function to
// process key presses.
// [Resources]
// https://www.opengl.org/resources/libraries/glut/spec3/node49.html
//*************************************************************************
void keyboardPress(unsigned char key, int x, int y)
{
	game->ProcessKeys(1, key);
}

//*************************************************************************
// [Class] -
// [Function Name] keyboardRelease
// [Argument{s}]
// unsigned char key: the released ASCII character key
// int x: x position of the mouse when the key was released
// int y: y position of the mouse when the key was released
// [Explanation] Makes calls to the method that processes keyboard release events.
// [Other] glutKeyboardUpFunc requires this callback function to
// process key releases.
// [Resources]
// http://dindinx.net/OpenGL/Introduction/glutKeyboardUpFunc.php
//*************************************************************************
void keyboardRelease(unsigned char key, int x, int y)
{
	game->ProcessKeys(0, key);
}

//*************************************************************************
// [Class] -
// [Function Name] mouseButtonInput
// [Argument{s}]
// int button: The button being pressed (GLUT_LEFT_BUTTON,GLUT_MIDDLE_BUTTON,GLUT_RIGHT_BUTTON)
// int state: The state of the button input (GLUT_UP,GLUT_DOWN)
// int x: the mouse x position relative to the window
// int y: the mouse y position relative to the window
// [Explanation]
// [Other] glutMouseFunc requires this callback function to process mouse
// button input.
// [Resources]
// https://www.opengl.org/resources/libraries/glut/spec3/node50.html
//*************************************************************************
void mouseButtonInput(int button, int state, int x, int y)
{
	game->ProcessMouseButtons(button, state, x, y);
}

//*************************************************************************
// [Class] -
// [Function Name] mouseMotionInput
// [Argument{s}]
// int x: the mouse x position relative to the window
// int y: the mouse y position relative to the window
// [Explanation]
// [Other] glutMotionFunc requires this callback function to process mouse
// motion when a button is being pressed.
// [Resources]
// https://www.opengl.org/resources/libraries/glut/spec3/node51.html
//*************************************************************************
void mouseMotionInput(int x, int y)
{
	game->ProcessMouseMotion(x, y);
}

//*************************************************************************
// [Class] -
// [Function Name] deleteGame
// [Argument{s}] -
// [Explanation] Delete the main game object
// [Other] -
// [Resources] -
//*************************************************************************
void deleteGame()
{
	delete game;
	game = nullptr;
}

//*************************************************************************
// [Class] -
// [Function Name] idleProc
// [Argument{s}] -
// [Explanation]
// [Other] glutIdleFunc processes this function when no other
// events have been registered
// [Resources]
// https://www.opengl.org/resources/libraries/glut/spec3/node63.html
//*************************************************************************
void idleProc()
{
}

//*************************************************************************
// [Class] -
// [Function Name] closeProc
// [Argument{s}] -
// [Explanation]
// [Other] glutCloseFunc processes this function when a glut window has
// been closed
// [Resources]
// http://freeglut.sourceforge.net/docs/api.php
//*************************************************************************
void closeProc()
{
	game->Terminate();
}
