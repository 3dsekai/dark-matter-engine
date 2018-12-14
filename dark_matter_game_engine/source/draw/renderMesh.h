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

class Camera;

//*************************************************************************
// Structs
//*************************************************************************
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
struct MeshParams
{
	//shader name
	const char* shaderName;

	//vertex aray object
	GLuint VAO;

	//texture id
	GLuint texId;

	//mesh color
	Vec4 color;

	//vertex attributes
	std::vector<VAParams> vertAttr;

	int vertNum; //number of vertices
	int idxNum; //number of indices
};

//*************************************************************************
// Class
//*************************************************************************
class RenderMesh
{
public:
	RenderMesh() {};
	~RenderMesh() {};

	void InitMesh(const float* vertices, const int* indices);
	void DrawMesh(const Camera& cam, Mat4 model);
	void SetTextureMesh(const char* texName);
	void DeleteMesh();

public:
	MeshParams _mParams;
};

#endif