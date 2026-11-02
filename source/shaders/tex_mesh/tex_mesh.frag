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
// structs
//*************************************************************************

//object lighting material
struct Material
{
	sampler2D diffuse0;
	sampler2D specular0;
	float shininess;
};

//light source
struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

//*************************************************************************
// input/output variables
//*************************************************************************
in vec2 texCoord; //texture coordinates
//in vec4 ambientCol; //ambient color *made redundant for now*
in vec3 normal; //fragment normal vector
in vec3 pixelPos; //the position of this fragment (pixel)
out vec4 color; //output color

//*************************************************************************
// Uniforms
//*************************************************************************
uniform vec3 viewPos; //camera position
uniform Material material; //mesh's material
uniform Light light; //light source


//*************************************************************************
// Shader Program
//*************************************************************************
void main()
{
	//////////////////////////////////////////////
	//ambient light
	//////////////////////////////////////////////

	//calculate the ambient light
	vec3 ambient = light.ambient * texture(material.diffuse0, texCoord).rgb;

	//////////////////////////////////////////////
	//diffuse light
	//////////////////////////////////////////////

	//normalize the fragment's normal
	vec3 fragNorm = normalize(normal);

	//get the direction of the fragment to the light
	vec3 dir = normalize(light.position - pixelPos);
	
	//get the dot product of cosine angle between frag normal and light.
	//calculates the "strength" of the light on this fragment.
	float diff = max(dot(fragNorm, dir), 0.0);
	
	//calculate diffuse light
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse0, texCoord).rgb;

	//////////////////////////////////////////////
	//specular light
	//////////////////////////////////////////////

	//direction of fragment to camera
	vec3 viewDir = normalize(viewPos - pixelPos);

	//get the direction of the reflection
	vec3 reflectDir = reflect(-dir, fragNorm);

	//specular value: cos(angle between reflect and view dir)^32
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	//calculate specular lighting
	vec3 specular = light.specular * spec * texture(material.specular0, texCoord).rgb;

	//////////////////////////////////////////////
	//output color
	//////////////////////////////////////////////
	color = vec4(ambient + diffuse + specular, 1.0);
}
