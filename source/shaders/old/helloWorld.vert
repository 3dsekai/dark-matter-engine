//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Shader: Hello World Vertex Shader
// Source File: [helloWorld.vert]
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


//create a uniform block to store the projection, view, and model 4x4 matrix
layout (std140) uniform Matrices
{
	mat4 pvm;
};

//input vertex attribute for the position coordinates
in vec4 position;

out vec4 color;

// main function
//get the opengl position of our geometry by multiplying the matrix by the position
void main()
{
	color = position;
	gl_Position = pvm * position;
}
