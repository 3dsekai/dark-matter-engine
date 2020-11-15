
//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: BitmapText
// Source File: [bitmapText.h]
//
// License:
// Copyright(C) <2020> <Christopher Tall>
//
// This software is copyrighted.
// The copyright notice and license information in this document must be
// preserved in every copy of the document AS IS. Attribution to the
// original author of this software must be given in either the
// modified source OR in the product's documentation.
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
#ifndef _BITMAP_TEXT_H_
#define _BITMAP_TEXT_H_

//*************************************************************************
// Definitions
//*************************************************************************
#define TEXT_MAX_CHAR_NUM (256) //maximum length of the text string

//*************************************************************************
// Includes
//*************************************************************************
#include "mesh.h"
#include "../draw/renderMesh.h"

class Vec3;

//*************************************************************************
// Quad Class
//*************************************************************************
#define QUAD_ATTRIBUTE_NUM (20)
#define QUAD_INDICES_NUM (6)
#define QUAD_STRIDE_LENGTH (5)

namespace
{
	//quad vertices
	const float quadVerts[QUAD_ATTRIBUTE_NUM] =
	{
		/*pos coord      tex coord*/
		-1.0, -1.0, 0.0, 0.0f, 0.0f,//bottom left
		 1.0, -1.0, 0.0, 1.0f, 0.0f,//bottom right
		 1.0,  1.0, 0.0, 1.0f, 1.0f,//top right
		-1.0,  1.0, 0.0, 0.0f, 1.0f//top left
	};

	//indices
	const uint32_t quadIdx[QUAD_INDICES_NUM] =
	{
		0, 1, 2,
		2, 3, 0
	};
};

class Quad : public Mesh
{
public:
	Quad(const char* shaderName, const Vec3& pos, const Quat& rot, const Vec3& scale) :
		Mesh(shaderName, pos, rot, scale)
	{
		int vtx_num = QUAD_ATTRIBUTE_NUM/QUAD_STRIDE_LENGTH;
		//set mesh data
		_meshName = "quad";
		_mDrawParam->mesh.vertNum = vtx_num;
		_mDrawParam->mesh.idxNum = QUAD_INDICES_NUM;
	
		//fill in vertices
		_vertices.reserve(vtx_num);
		for(int i = 0; i < vtx_num; i++)
		{
			int offset = i*QUAD_STRIDE_LENGTH;
			RenderMesh::Vertex vtx;
			//position
			vtx.pos.x = quadVerts[offset];
			vtx.pos.y = quadVerts[offset+1];
			vtx.pos.z = quadVerts[offset+2];
			// texture coordinates
			vtx.tex_coord.x = quadVerts[offset+3];
			vtx.tex_coord.y = quadVerts[offset+4];
			_vertices.push_back(vtx);
		}
	
		//fill in indices
		_indices = std::vector<uint32_t>(quadIdx, quadIdx+sizeof(quadIdx)/sizeof(uint32_t));
	
		//prepare vertex attributes
		std::vector<RenderMesh::VAParams> va;
		{ //position coordinates
			RenderMesh::VAParams va1;
			va1.size = 3; //size of attribute
			va1.type = GL_FLOAT; //vertex attribute type
			va1.norm = GL_FALSE; //vertex attribute normalization bool
			va1.stride = sizeof(RenderMesh::Vertex); //size of vertex stride
			va1.offset = 0; //offset attribute
			va.push_back(va1);
		}
		{ //texture coordinates
			RenderMesh::VAParams va2;
			va2.size = 2;
			va2.type = GL_FLOAT;
			va2.norm = GL_FALSE;
			va2.stride = sizeof(RenderMesh::Vertex);
			va2.offset = offsetof(RenderMesh::Vertex, RenderMesh::Vertex::tex_coord);
			va.push_back(va2);
		}
		//initialize the mesh for rendering
		RenderMesh::InitMesh(_vertices, _indices, &_mDrawParam->mesh, va);
	};
	
	~Quad()
	{
		Delete();
	};
};
//*************************************************************************
// BitmapText Class
//*************************************************************************
class BitmapText
{
public:
	struct BitmapTextParameters
	{
		const char* _text = ""; //the text to display
	//	const char* _color; //text color
	};

public:
	BitmapText(const BitmapTextParameters& textParams, const Vec3& pos);
	~BitmapText();

	void Draw();
	void Delete();

	void SetText(const char* text);
	void ResetTextParameters(const BitmapTextParameters& textParams);

	inline void SetPosition(const Vec3& pos) { _pos = pos; };
	inline const Vec3 GetPosition() const { return _pos; };

	//void SetTexture(const char* texName, MATERIAL_TYPE type);

private:
	void SetupText();

private:
	BitmapTextParameters _textParams; //text parameters
	Vec3 _pos;	//position
};

#endif
