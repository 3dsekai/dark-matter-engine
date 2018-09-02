//*************************************************************************
// DarkMatter OpenGL 3D Engine Framework
// Class Name: Keyboard
// Source File: [keyboard.h]
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
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

//*************************************************************************
// include
//*************************************************************************
#include <bitset>
//*************************************************************************
// Keyboard Class
//*************************************************************************
class Keyboard
{
public:
	enum KeyState
	{
		KEY_RELEASED = 0,	//key is released
		KEY_PRESSED		//key is pressed
	};

public:
	Keyboard() = default;
	~Keyboard() = default;

	void OnKeyPress(unsigned char key);
	void OnKeyRelease(unsigned char key);
	int GetKeyState(unsigned char key) const;
	bool IsKeyPressed(unsigned char key) const;
	bool IsKeyReleased(unsigned char key) const;

private:
	static constexpr unsigned int KEY_NUM = 256u; //number of keys
	std::bitset<KEY_NUM> _keystate;	//input key state
};

#endif
