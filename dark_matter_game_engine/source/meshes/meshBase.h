//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: MeshBase
// Source File: [meshBase.h]
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
#ifndef _MESH_BASE_H_
#define _MESH_BASE_H_

//*************************************************************************
// Includes
//*************************************************************************
#include <GL/glew.h>
#include <iostream>
#include "../define/material_define.h"
#include "../draw/shaderManager.h"
#include "../draw/shader.h"
#include "../draw/renderMesh.h"
#include "../math_lib/vec3.h"
#include "../math_lib/quat.h"

class Vec4;
//*************************************************************************
// MeshBase Class
//*************************************************************************
class MeshBase
{
public:
	MeshBase() = default;
	~MeshBase() = default;

protected:
	MeshBase(const char* shaderName, const Vec3& pos, const Vec3& scale, const Quat& rot, const Vec4& color, GLuint vao) :
		_pos(pos),
		_scale(scale),
		_rot(rot)
	{
		{ //set renderer
			_renderer = new RenderMesh();
			_renderer->_mParams.shaderName = shaderName;
			_renderer->_mParams.VAO = vao;
			_renderer->_mParams.color = color;
		}
		{ //set material
			_renderer->_mParams.material.diffuse   = 0;
			_renderer->_mParams.material.specular  = 1;
			_renderer->_mParams.material.diffTexId = 0;
			_renderer->_mParams.material.specTexId = 0;
			_renderer->_mParams.material.shininess = 64;
		}
	};

protected:
	virtual void Init() = 0;

public:
	virtual void Draw() = 0;
	virtual void Delete() = 0;

public:
	inline void SetPosition(const Vec3& pos) { _pos = pos; };
	inline void SetRotation(const Quat& rot) { _rot = rot; };
	inline void SetScale(const Vec3& scale) { _scale = scale; };
	inline void SetColor(const Vec4& color) { _renderer->_mParams.color = color; };

	inline const Vec3 GetPosition() const { return _pos; };
	inline const Quat GetRotation() const { return _rot; };
	inline const Vec3 GetScale() const { return _scale; };
	inline const Vec4 GetColor() const { return _renderer->_mParams.color; };

	void SetTexture(const char* texName, MATERIAL_TYPE type)
	{
		if(_renderer != nullptr)
		{
			GLuint texId = _renderer->LoadTexture(texName);
	
			//set the cube color and texture to the shader
			Shader* shader = ShaderManager::GetInstance()->GetShader(_renderer->_mParams.shaderName);
			if (shader != nullptr)
			{
				shader->UseProgram();
				switch(type)
				{
				case MATERIAL_DIFFUSE:
					shader->SetUniformInt(_renderer->_mParams.material.diffuse, "material.diffuse");
					_renderer->_mParams.material.diffTexId = texId;
					break;
				case MATERIAL_SPECULAR:
					shader->SetUniformInt(_renderer->_mParams.material.specular, "material.specular");
					_renderer->_mParams.material.specTexId = texId;
					break;
				}
			}
			else
			{
				std::cout << "Couldn't load shader: " << _renderer->_mParams.shaderName << std::endl;
			}
		}
	};

protected:
	RenderMesh* _renderer;		//mesh renderer

	Vec3 _pos;					//position
	Vec3 _scale;				//scale
	Quat _rot;					//rotation
};

#endif
