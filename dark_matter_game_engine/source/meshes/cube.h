//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: Cube
// Source File: [cube.h]
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
#ifndef _CUBE_H_
#define _CUBE_H_

//*************************************************************************
// Includes
//*************************************************************************
#include <GL/glew.h>
#include "mesh.h"
#include "../draw/renderMesh.h"

//*************************************************************************
// Cube Class
//*************************************************************************
class Cube : public Mesh
{
public:
	Cube(const char* shaderName,
		 const Vec3& pos = Vec3(0.0f, 0.0f, 0.0f),
		 const Quat& rot = Quat::Identity(),
		 const Vec3& scale = Vec3(1.0f, 1.0f, 1.0f));
	~Cube();

//	virtual void Init(const char* meshName, const std::vector<RenderMesh::Vertex>& vertices, const std::vector<uint32_t>& indices) override;
};

#endif
