//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Shader: Textured Mesh Vertex Shader
// Source File: [tex_mesh.vert]
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
layout (location = 0) in vec3 attrPos;
layout (location = 1) in vec2 attrTex;
layout (location = 2) in vec3 attrNormal;

out vec2 texCoord; //texture coordinates
out vec4 ambientCol; //the ambient light
out vec3 pixelPos; //position of the fragment
out vec3 normal; //vertex normal

//*************************************************************************
// Uniform Buffer Objects
//*************************************************************************
layout (std140) uniform UBOParams
{
	mat4 projView; //world matrix
	vec4 ambientLight; //ambient light color
};

//*************************************************************************
// Uniforms
//*************************************************************************
uniform mat4 model; //model matrix
uniform mat3 normModelMat; //normalized model matrix to avoid scaling issues with light

//*************************************************************************
// Shader Function
//*************************************************************************
void main()
{
	gl_Position = projView * model * vec4(attrPos, 1.0);//calculate position
	texCoord = attrTex; //pass the texture coordinates
	ambientCol = ambientLight;//pass the ambient light color
	pixelPos = vec3(model * vec4(attrPos, 1.0));
	normal = normModelMat * attrNormal; //calculate the vertex normal
//	normal = mat3(transpose(inverse(model))) * attrNormal;
}
