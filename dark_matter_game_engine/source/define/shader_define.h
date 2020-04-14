//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: -
// Source File: [shader_define.h]
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
//solid cube shader files
//*************************************************************************
#define SOLID_MESH_SHADER_NAME ("solid_mesh")
//*************************************************************************
//texture cube shader files
//*************************************************************************
#define TEXTURE_MESH_SHADER_NAME ("tex_mesh")
//*************************************************************************
//colored cube shader files
//*************************************************************************
#define COLORED_CUBE_SHADER_NAME ("colored_cube")

//*************************************************************************
//shader paths
//*************************************************************************
#ifdef __linux__ //linux
#define SOLID_MESH_VERTEX_SHADER   ("../source/shaders/solid_mesh/solid_mesh.vert")
#define SOLID_MESH_FRAGMENT_SHADER ("../source/shaders/solid_mesh/solid_mesh.frag")
#define TEXTURE_MESH_VERTEX_SHADER   ("../source/shaders/tex_mesh/tex_mesh.vert")
#define TEXTURE_MESH_FRAGMENT_SHADER ("../source/shaders/tex_mesh/tex_mesh.frag")
#define COLORED_CUBE_VERTEX_SHADER   ("../source/shaders/color_cube/colored_cube.vert")
#define COLORED_CUBE_FRAGMENT_SHADER ("../source/shaders/color_cube/colored_cube.frag")
#else //windows
#define SOLID_MESH_VERTEX_SHADER   ("source/shaders/solid_mesh/solid_mesh.vert")
#define SOLID_MESH_FRAGMENT_SHADER ("source/shaders/solid_mesh/solid_mesh.frag")
#define TEXTURE_MESH_VERTEX_SHADER   ("source/shaders/tex_mesh/tex_mesh.vert")
#define TEXTURE_MESH_FRAGMENT_SHADER ("source/shaders/tex_mesh/tex_mesh.frag")
#define COLORED_CUBE_VERTEX_SHADER   ("source/shaders/color_cube/colored_cube.vert")
#define COLORED_CUBE_FRAGMENT_SHADER ("source/shaders/color_cube/colored_cube.frag")
#endif
