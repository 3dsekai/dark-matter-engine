//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Shader: Hello World Fragment Shader
// Source File: [helloWorld.frag]
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

#version 330	//version declaration

//default color output to the screen
out vec4 outputF;

// main function
//set the color to the geometry on the screen
void main(void)
{
	outputF = vec4(1.0, 0.0, 0.0, 1.0);
}
