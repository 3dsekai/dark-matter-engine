//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: ModelManager
// Source File: [modelManager.h]
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
#ifndef _MODEL_MANAGER_H_
#define _MODEL_MANAGER_H_

//*************************************************************************
// Includes
//*************************************************************************
#include <map>
#include <vector>
class Mesh;

//*************************************************************************
// Model Manager Class
//*************************************************************************
class ModelManager
{
private:
	ModelManager() {};
	ModelManager(const ModelManager &obj) {};
	~ModelManager() {};

public:
	static ModelManager* GetInstance();
	static void DestroyInstance();

	void LoadModel(const char* name);
	void UnloadModel(const char* name);
	std::vector<Mesh*> GetModel(const char* name);

private:
	static void UnloadAllModels();

private:
	static ModelManager* _instance;
	static std::map<const char*, std::vector<Mesh*>> _model;
};

#endif
