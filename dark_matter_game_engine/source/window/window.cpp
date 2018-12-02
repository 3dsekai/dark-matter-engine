//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: Window
// Source File: [window.cpp]
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
// Include
//*************************************************************************
#include "window.h"

//*************************************************************************
// static member definition
//*************************************************************************
Window* Window::_instance = nullptr;

//*************************************************************************
// Class: Window
// Function Name: getInstance
// Explanation: Get the instance to this static singleton class
// Argument{s}:
// Other: -
//*************************************************************************
Window* Window::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = new Window;
	}
	return _instance;
}

//*************************************************************************
// Class: Window
// Function Name: destroyInstance
// Explanation: Destroy the instance to this static singleton class
// Argument{s}:
// Other: -
//*************************************************************************
void Window::DestroyInstance()
{
	delete _instance;
	_instance = nullptr;
}