//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: RenderMesh
// Source File: [renderMesh.h]
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
#ifndef _RENDERMESH_H_
#define _RENDERMESH_H_

//*************************************************************************
// Include
//*************************************************************************
#include <vector>
#include <GL/glew.h>
#include "../math_lib/vec4.h"
#include "../define/material_define.h"
class Vec4;
class Mat4;

//*************************************************************************
// Class
//*************************************************************************
class RenderMesh
{
public:
//vertex attribute parameters
struct VAParams
{
	int size; //size of attribute
	GLenum type; //vertex attribute type
	GLboolean norm; //vertex attribute normalization bool
	GLuint stride; //size of vertex stride
	int offset; //offset attribute
};

//mesh parameters
struct MeshParam
{
	GLuint VAO; //vertex aray object
	int vertNum; //number of vertices
	int idxNum; //number of indices
};

//mesh render parameters
struct MeshRenderParam
{
	//shader name
	const char* shaderName;

	//mesh material
	materialDef material;
	
	//mesh parameters
	MeshParam mesh;
};

public:
	RenderMesh() {};
	~RenderMesh() {};

	static void InitMesh(const float* vertices, const uint32_t* indices, MeshParam* mParam, const std::vector<VAParams>& va);
	static void DrawMesh(const Mat4& model, const MeshRenderParam& mDrawParam);
	static void DeleteMesh(MeshParam* mParam);
};

#endif
