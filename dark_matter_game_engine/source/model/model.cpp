//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: Model
// Source File: [model.cpp]
//
// License:
// Copyright(C) <2019> <Christopher Tall>
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

//*************************************************************************
// Includes
//*************************************************************************
#include <iostream>
#include "model.h"
#include "../meshes/mesh.h"
#include "../resource/modelManager.h"

Model::Model(const char* shaderName, const char* modelName, const Vec3& pos, const Quat& rot, const Vec3& scale) :
	  _shaderName(shaderName)
	, _modelName(modelName)
	, _pos(pos)
	, _rot(rot)
	, _scale(scale)
{
	LoadModel(modelName);
}

Model::~Model()
{
	Delete();
}

void Model::Draw()
{
	for(auto it = _meshArr.begin(); it != _meshArr.end(); it++)
	{
		(*it)->Draw();
	}
}

void Model::Delete()
{
	_meshArr.clear();
}

void Model::LoadModel(const char* modelName)
{
	ModelManager::GetInstance()->LoadModel(modelName);
	_meshArr = ModelManager::GetInstance()->GetModel(modelName);
	if(_meshArr.size() <= 0)
	{
		std::cout << "Model Load Failed" << std::endl;
	}
}
