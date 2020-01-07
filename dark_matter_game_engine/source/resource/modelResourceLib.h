//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: ModelResourceLib
// Source File: [modelResourceLib.h]
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
#ifndef _MODEL_RESOURCE_LIB_H_
#define _MODEL_RESOURCE_LIB_H_

//*************************************************************************
// Include
//*************************************************************************
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../define/material_define.h"

class Mesh;
//*************************************************************************
// Declarations
//*************************************************************************
void lib_initModel(std::string path, std::vector<Mesh*>* model);
void lib_aiProcessNode(aiNode *aiNode, const aiScene *aiScene, std::vector<Mesh*>* model);
Mesh* lib_aiProcessMesh(aiMesh *aiMesh, const aiScene *aiScene);
void lib_loadMaterials(aiMaterial* aiMat, aiTextureType matType, std::vector<materialData>* maps);

#endif
