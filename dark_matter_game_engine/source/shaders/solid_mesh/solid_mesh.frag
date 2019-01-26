//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Shader: Solid Mesh Fragment Shader
// Source File: [solid_mesh.frag]
//
// License:
// Copyright(C) <2018, 2019>  <Christopher Tall>
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
in vec4 ambientCol; //ambient color
in vec3 normal; //fragment normal vector
in vec3 pixelPos; //the position of this fragment (pixel)
out vec4 color; //output color

//*************************************************************************
// Uniforms
//*************************************************************************
uniform vec4 meshColor; //mesh color
uniform vec3 difLightPos; //diffuse light position
uniform vec3 difLightColor; //diffuse light color

//*************************************************************************
// Shader Program
//*************************************************************************
void main()
{
	//////////////////////////////////////////////
	//ambient light
	//////////////////////////////////////////////

	//strength of the ambient light
	float ambientStrength = ambientCol.w;
	//calculate the ambient light (color of light * strength of light)
	vec4 ambient = vec4(ambientCol.x * ambientStrength,
						ambientCol.y * ambientStrength,
						ambientCol.z * ambientStrength,
						1.0);

	//////////////////////////////////////////////
	//diffuse light
	//////////////////////////////////////////////

	//normalize the fragment's normal
	vec3 norm = normalize(normal);

	//get the direction of the fragment to the light
	vec3 dir = normalize(difLightPos - pixelPos);

	//get the dot product of cosine angle between frag normal and light.
	//calculates the "strength" of the light on this fragment.
	float strength = max(dot(norm, dir), 0.0);

	//calculate diffuse light (color of light * strength of light)
	vec3 diffuse = difLightColor * strength;

	//////////////////////////////////////////////
	//output color
	//////////////////////////////////////////////
	color = (ambient + diffuse) * meshColor;
}
