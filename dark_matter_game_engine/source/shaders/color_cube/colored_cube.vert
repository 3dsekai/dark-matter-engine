//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Shader: Colored Cube Vertex Shader
// Source File: [colored_cube.vert]
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

#version 330 core
layout (location = 0) in vec3 at_pos;
layout (location = 1) in vec3 at_color; // the color variable has attribute position 1
  
out vec3 color; // output a color to the fragment shader
uniform mat4 mvp;

void main()
{
    gl_Position = mvp * vec4(at_pos, 1.0);
    color = at_color; // set color to the input color we got from the vertex data
}
