//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Shader: Textured Mesh Fragment Shader
// Source File: [tex_mesh.frag]
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

#version 330 core

//*************************************************************************
// input/output variables
//*************************************************************************
in vec2 texCoord;
out vec4 color;

//*************************************************************************
// Uniforms
//*************************************************************************
uniform sampler2D texture;
uniform vec4 meshColor;

//*************************************************************************
// Shader Function
//*************************************************************************
void main()
{
	color = texture(texture, texCoord) * meshColor;
}
