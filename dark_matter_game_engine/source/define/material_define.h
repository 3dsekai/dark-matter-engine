//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: -
// Source File: [material_define.h]
//
// License:
// Copyright(C) <2019>  <Christopher Tall>
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
#ifndef _MATERIAL_DEFINE_H_
#define _MATERIAL_DEFINE_H_

//*************************************************************************
// include
//*************************************************************************
#include "../math_lib/vec3.h"
#include <GL/glew.h>
#include <assimp/scene.h>

//#define MAX_SAMPLERS (GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS) //the maximum number of sampler's per material
#define MATERIAL_SAMPLER_MAX_NUM (16) //the maximum number of sampler's per material type

//object material struct
struct materialDef
{
	GLint  diffuse[MATERIAL_SAMPLER_MAX_NUM]; //diffuse material sampler
	GLuint diffTexId[MATERIAL_SAMPLER_MAX_NUM]; //diffuse material texture id
	int diffMaterialNum;			//number of diffuse materials
	GLint  specular[MATERIAL_SAMPLER_MAX_NUM]; //specular material sampler
	GLuint specTexId[MATERIAL_SAMPLER_MAX_NUM]; //specular material texture id
	int specMaterialNum;				//number of specular materials
	float  shininess; //the shininess of the material (strength of specular reflection)
};

//material types
enum MATERIAL_TYPE
{
	MATERIAL_DIFFUSE = aiTextureType_DIFFUSE,
	MATERIAL_SPECULAR = aiTextureType_SPECULAR
};

//basic basic data
struct materialData
{
	const char* texName; //name of texture
	MATERIAL_TYPE type; //type of material
};
#endif
