//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: MeshManager
// Source File: [meshManager.h]
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
#ifndef _MESH_MANAGER_H_
#define _MESH_MANAGER_H_
//*************************************************************************
// Includes
//*************************************************************************
#include <map>
#include <GL/glew.h>
#include "../draw/renderMesh.h"

//*************************************************************************
// Mesh Manager Class
//*************************************************************************
class MeshManager
{

public:
	static MeshManager* GetInstance();
	static void DestroyInstance();

	void InitAllMeshes();
	void InitMesh(std::string name, const float* vertices, const uint32_t* indices, int vertNum, int idxNum, const std::vector<RenderMesh::VAParams>& va);
	void DeleteMesh(std::string name);
	bool GetMesh(std::string name, RenderMesh::MeshParam* mesh);

private:
	static void ClearAllMeshes();

private:
	MeshManager() {};
	~MeshManager() {};

	MeshManager(const MeshManager &obj) {};


private:
	static MeshManager* _instance;
	static std::map<std::string, RenderMesh::MeshParam*> _meshes;
};

#endif
