//*************************************************************************
// DarkMatter OpenGL 3D Engine Framework
// Class Name: Mouse
// Source File: [mouse.h]
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
#ifndef _MOUSE_H_
#define _MOUSE_H_

//*************************************************************************
// include
//*************************************************************************
#include "../math_lib/vec2.h"

//*************************************************************************
// Mouse Class
//*************************************************************************
class Mouse
{
public:
	enum MouseButtonState
	{
		BUTTON_RELEASED = 0, //mouse button is released
		BUTTON_PRESSED //mouse button is pressed
	};

public:
	Mouse();
	~Mouse();

	void OnLeftButtonPress(int x, int y);
	void OnLeftButtonRelease(int x, int y);
	void OnRightButtonPress(int x, int y);
	void OnRightButtonRelease(int x, int y);

	bool IsLeftButtonPressed() const;
	bool IsLeftButtonReleased() const;
	bool IsRightButtonPressed() const;
	bool IsRightButtonReleased() const;

	unsigned int GetLeftButtonState() const;
	unsigned int GetRightButtonState() const;

	void OnMouseMove(int x, int y);

	Vec2 GetPos() const;
	int GetPosX() const;
	int GetPosY() const;

private:
	int _x; //mouse x-coord
	int _y; //mouse Y-coord
	unsigned int _left_btn_state; //left button state
	unsigned int _right_btn_state; //right button state
};

#endif
