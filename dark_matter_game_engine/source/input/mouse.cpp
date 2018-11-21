//*************************************************************************
// DarkMatter OpenGL 3D Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: Mouse
// Source File: [mouse.cpp]
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

//*************************************************************************
// include
//*************************************************************************
#include "mouse.h"
#include "../math_lib/vec2.h"

//*************************************************************************
// Class: Mouse
// Function Name: Mouse
// Explanation: Mouse Class constructor
// Other: -
//*************************************************************************
Mouse::Mouse() :
	_x(0),
	_y(0),
	_left_btn_state(BUTTON_RELEASED),
	_right_btn_state(BUTTON_RELEASED)
{}

//*************************************************************************
// Class: Mouse
// Function Name: Mouse
// Explanation: Mouse Class destructor
// Other: -
//*************************************************************************
Mouse::~Mouse()
{
	_x = 0;
	_y = 0;
	_left_btn_state = BUTTON_RELEASED;
	_right_btn_state = BUTTON_RELEASED;
}

//*************************************************************************
// Class: Mouse
// Function Name: OnLeftButtonPress
// Argument{s}:
// int x: the current mouse x-position
// int y: the current mouse y-position
// Explanation: changes left-button state to pressed
// Other: -
//*************************************************************************
void Mouse::OnLeftButtonPress(int x, int y)
{
	_left_btn_state = BUTTON_PRESSED;
}

//*************************************************************************
// Class: Mouse
// Function Name: OnLeftButtonRelease
// Argument{s}:
// int x: the current mouse x-position
// int y: the current mouse y-position
// Explanation: changes left-button state to released
// Other: -
//*************************************************************************
void Mouse::OnLeftButtonRelease(int x, int y)
{
	_left_btn_state = BUTTON_RELEASED;
}

//*************************************************************************
// Class: Mouse
// Function Name: OnRightButtonPress
// Argument{s}:
// int x: the current mouse x-position
// int y: the current mouse y-position
// Explanation: changes right-button state to pressed
// Other: -
//*************************************************************************
void Mouse::OnRightButtonPress(int x, int y)
{
	_right_btn_state = BUTTON_PRESSED;
}

//*************************************************************************
// Class: Mouse
// Function Name: OnRightButtonRelease
// Argument{s}:
// int x: the current mouse x-position
// int y: the current mouse y-position
// Explanation: changes right-button state to released
// Other: -
//*************************************************************************
void Mouse::OnRightButtonRelease(int x, int y)
{
	_right_btn_state = BUTTON_RELEASED;
}

//*************************************************************************
// Class: Mouse
// Function Name: IsLeftButtonPressed
// Explanation: Returns the press state of the left mouse button
// Other: -
//*************************************************************************
bool Mouse::IsLeftButtonPressed() const
{
	return _left_btn_state == BUTTON_PRESSED;
}

//*************************************************************************
// Class: Mouse
// Function Name: IsLeftButtonReleased
// Explanation: Returns the release state of the left mouse button
// Other: -
//*************************************************************************
bool Mouse::IsLeftButtonReleased() const
{
	return _left_btn_state == BUTTON_RELEASED;
}

//*************************************************************************
// Class: Mouse
// Function Name: IsRightButtonPressed
// Explanation: Returns the press state of the right mouse button
// Other: -
//*************************************************************************
bool Mouse::IsRightButtonPressed() const
{
	return _right_btn_state == BUTTON_PRESSED;
}

//*************************************************************************
// Class: Mouse
// Function Name: IsRightButtonReleased
// Explanation: Returns the release state of the right mouse button
// Other: -
//*************************************************************************
bool Mouse::IsRightButtonReleased() const
{
	return _right_btn_state == BUTTON_RELEASED;
}

//*************************************************************************
// Class: Mouse
// Function Name: GetLeftButtonState
// Explanation: Returns the state of the left mouse button
// Other: -
//*************************************************************************
unsigned int Mouse::GetLeftButtonState() const
{
	return _left_btn_state;
}

//*************************************************************************
// Class: Mouse
// Function Name: GetRightButtonState
// Explanation: Returns the state of the right mouse button
// Other: -
//*************************************************************************
unsigned int Mouse::GetRightButtonState() const
{
	return _right_btn_state;
}

//*************************************************************************
// Class: Mouse
// Function Name: OnMouseMove
// Argument{s}:
// int x: new mouse x-position
// int y: new mouse y-position
// Explanation: Sets the mouse coordinates its new position
// Other: -
//*************************************************************************
void Mouse::OnMouseMove(int x, int y)
{
	_x = x;
	_y = y;
}

//*************************************************************************
// Class: Mouse
// Function Name: GetMousePos
// Explanation: Returns the mouse coordinates as a 2D vector
// Other: -
//*************************************************************************
Vec2 Mouse::GetPos() const
{
	return Vec2((float)_x, (float)_y);
}

//*************************************************************************
// Class: Mouse
// Function Name: GetMousePosX
// Explanation: Returns the mouse x-coordinate
// Other: -
//*************************************************************************
int Mouse::GetPosX() const
{
	return _x;
}

//*************************************************************************
// Class: Mouse
// Function Name: GetMousePosY
// Explanation: Returns the mouse y-coordinate
// Other: -
//*************************************************************************
int Mouse::GetPosY() const
{
	return _y;
}
