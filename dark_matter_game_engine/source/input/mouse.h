//*************************************************************************
// DarkMatter OpenGL 3D Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: Mouse
// Source File: [mouse.h]
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
#ifndef _MOUSE_H_
#define _MOUSE_H_

//*************************************************************************
// include
//*************************************************************************
class Vec2;

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
