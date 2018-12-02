//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: Window
// Source File: [window.h]
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
#ifndef _WINDOW_H_
#define _WINDOW_H_

//*************************************************************************
// Window Class
//*************************************************************************
class Window
{
public:
	static Window* GetInstance();
	static void DestroyInstance();

	inline void SetWindowWidth(float w) { _width = w; };     //set window width
	inline void SetWindowHeight(float h) { _height = h; };   //set window height
	inline float GetWindowWidth() const { return _width; };    //get window width
	inline float GetWindowHeight() const { return _height; };  //get window height

private:
	Window() {};
	~Window() {};

	Window(const Window &obj) {};

private:
	float _width; //window width;
	float _height; //window height;
	static Window* _instance; //singleton instance
};

#endif