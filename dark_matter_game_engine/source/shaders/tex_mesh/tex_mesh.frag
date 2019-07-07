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
in vec2 texCoord; //texture coordinates
in vec4 ambientCol; //ambient color
in vec3 normal; //fragment normal vector
in vec3 pixelPos; //the position of this fragment (pixel)
out vec4 color; //output color

//*************************************************************************
// Uniforms
//*************************************************************************
uniform sampler2D texture; //texture data
uniform vec4 meshColor; //mesh color
uniform vec3 lightPos; //diffuse light position
uniform vec3 lightColor; //diffuse light color

//*************************************************************************
// Shader Program
//*************************************************************************
void main()
{
	//////////////////////////////////////////////
	//ambient light
	//////////////////////////////////////////////

	float ambientStrength = ambientCol.w; //strength of the ambient light
	vec3 ambient = vec3(ambientCol) * ambientStrength; //calculate the ambient light (color of light * strength of light)

	//////////////////////////////////////////////
	//diffuse light
	//////////////////////////////////////////////

	vec3 norm = normalize(normal); //normalize the fragment's normal
	vec3 dir = normalize(lightPos - pixelPos); //get the direction of the fragment to the light
	float diff = max(dot(norm, dir), 0.0); //get the dot product of cosine angle between frag normal and light. calculates the "strength" of the light on this fragment.
	vec3 diffuse = diff * lightColor; //calculate diffuse light (color of light * strength of light)

	//////////////////////////////////////////////
	//specular light
	//////////////////////////////////////////////
	
	float specStrength = 10.0; //specular strength
	vec3 reflectDir = reflect(-dir, norm); //get the direction of the reflection
	float spec = pow(max(dot(normalize(pixelPos), reflectDir), 0.0f), 32); //specular value: cos(angle between frag and view dir)^32
	vec3 specular = specStrength * spec * lightColor;

	//////////////////////////////////////////////
	//output color
	//////////////////////////////////////////////
	color = texture(texture, texCoord) * vec4(ambient + diffuse, 1.0f) * meshColor;
}
