//*************************************************************************
// Dark Matter OpenGL 3D Engine Framework Main Process [main.h]
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
//standard C/C++ libraries
#include <stdlib.h>
#include <stdio.h>

//engine headers
#include "main.h"
#include "game_main/gameMain.h"

//*************************************************************************
// Function Declarations
//*************************************************************************
void RenderScene();
void ResizeWindow(int width, int height);
void KeyboardPress(unsigned char key, int x, int y);
void KeyboardRelease(unsigned char key, int x, int y);
void MouseButtonInput(int button, int state, int x, int y);
void MouseMotionInput(int x, int y);
void DeleteGame();

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
	glutDisplayFunc(RenderScene); //calls draw function everytime the screen needs to be redrawn
	glutReshapeFunc(ResizeWindow); //manages the height and width of a window when it is resized
	glutIdleFunc(RenderScene); //sets idle callback function to perform background processing when window system events aren't being received

	//mouse and keyboard callbacks
	glutKeyboardFunc(KeyboardPress); //processes keyboard key press
	glutKeyboardUpFunc(KeyboardRelease); //processes keyboard key release
	glutMouseFunc(MouseButtonInput); //processes mouse click events
	glutMotionFunc(MouseMotionInput); //processes mouse motion when a button is being pressed
	//glutPassiveMotionFunc(MouseMotionInput); //processes mouse motion without button press
	//glutMouseWheelFunc(mouseWheel); //processes mouse wheel events (this function isn't portable and maybe shouldn't be used)

	//return from main loop when the window is closed
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

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

	// enter GLUT event processing cycle
	glutMainLoop();

	//delete the main game object
	DeleteGame();

	return 0;
}

//*************************************************************************
// [Class] -
// [Function Name] RenderScene
// [Argument{s}]: -
// [Explanation] Calls the draw function from the game loop to draw
// the current scene.
// [Other] glutDisplayFunc and glutIdleFunc requires this method to
// render scenes to the application window.
// [Resources]
// https://www.opengl.org/resources/libraries/glut/spec3/node46.html
//*************************************************************************
void RenderScene()
{
	game->Update();
	game->Draw();
	glutSwapBuffers();
}

//*************************************************************************
// [Class] -
// [Function Name] ResizeWindow
// [Argument{s}]
// int width: window width
// int height: window height
// [Explanation] Manages the dimensions of a window when it is resized
// [Other] glutReshapeFunc requires this function to
// resize the application window.
// [Resources]
// https://www.opengl.org/resources/libraries/glut/spec3/node48.html
//*************************************************************************
void ResizeWindow(int width, int height)
{
}

//*************************************************************************
// [Class] -
// [Function Name] KeyboardPress
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
void KeyboardPress(unsigned char key, int x, int y)
{
	game->ProcessKeys(1, key);
}

//*************************************************************************
// [Class] -
// [Function Name] KeyboardRelease
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
void KeyboardRelease(unsigned char key, int x, int y)
{
	game->ProcessKeys(0, key);
}

//*************************************************************************
// [Class] -
// [Function Name] MouseButtonInput
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
void MouseButtonInput(int button, int state, int x, int y)
{
	game->ProcessMouseButtons(button, state, x, y);
}

//*************************************************************************
// [Class] -
// [Function Name] MouseMotionInput
// [Argument{s}]
// int x: the mouse x position relative to the window
// int y: the mouse y position relative to the window
// [Explanation]
// [Other] glutMotionFunc requires this callback function to process mouse
// motion when a button is being pressed.
// [Resources]
// https://www.opengl.org/resources/libraries/glut/spec3/node51.html
//*************************************************************************
void MouseMotionInput(int x, int y)
{
	game->ProcessMouseMotion(x, y);
}

//*************************************************************************
// [Class] -
// [Function Name] DeleteGame
// [Argument{s}] -
// [Explanation] Delete the main game object
// [Other] -
// [Resources] -
//*************************************************************************
void DeleteGame()
{
	delete game;
	game = nullptr;
}