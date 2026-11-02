//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: Keyboard
// Source File: [keyboard.cpp]
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
#include "keyboard.h"

//*************************************************************************
// Class: Keyboard
// Function Name: OnKeyPress
// Argument{s}:
// unsigned char key: the pressed key code
// Explanation: Register a key press
// Other: -
//*************************************************************************
void Keyboard::OnKeyPress(unsigned char key)
{
	_keystate[key] = KEY_PRESSED;
}

//*************************************************************************
// Class: Keyboard
// Function Name: OnKeyRelease
// Argument{s}:
// unsigned char key: the released key code
// Explanation: Register a key release
// Other: -
//*************************************************************************
void Keyboard::OnKeyRelease(unsigned char key)
{
	_keystate[key] = KEY_RELEASED;
}

//*************************************************************************
// Class: Keyboard
// Function Name: GetKeyState
// Argument{s}:
// unsigned char key: the key's code
// Explanation: Gets the key input state
// Other: -
//*************************************************************************
int Keyboard::GetKeyState(unsigned char key) const
{
	return _keystate[key];
}

//*************************************************************************
// Class: Keyboard
// Argument{s}:
// unsigned char key: the key's code
// Function Name: IsKeyPressed
// Explanation: Determines if a key is being pressed
// Other: -
//*************************************************************************
bool Keyboard::IsKeyPressed(unsigned char key) const
{
	return _keystate[key] == KEY_PRESSED;
}

//*************************************************************************
// Class: Keyboard
// Argument{s}:
// unsigned char key: the key's code
// Function Name: IsKeyReleased
// Explanation: Determines if a key has been released
// Other: -
//*************************************************************************
bool Keyboard::IsKeyReleased(unsigned char key) const
{
	return _keystate[key] == KEY_RELEASED;
}
