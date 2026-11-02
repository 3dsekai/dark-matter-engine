//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Shader: Colored Cube Fragment Shader
// Source File: [colored_cube.frag]
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

//version declaration
#version 330	

//input vertex color attribute
in vec4 color;

//input color output to the screen
out vec4 outputF;

// main function
//set the color for the vertex to the output fragment shader
void main(void)
{
	outputF = color;
}
