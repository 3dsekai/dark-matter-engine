//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: Plane
// Source File: [plane.cpp]
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

//*************************************************************************
// Includes
//*************************************************************************
#include "plane.h"
#include "../math_lib/mat4.h"
#include "../resource/meshManager.h"
//*************************************************************************
// Macro Definitions
//*************************************************************************
#define PLANE_ATTRIBUTE_NUM (32)
#define PLANE_INDICES_NUM (6)

//*************************************************************************
// constants definitions
//*************************************************************************
namespace
{
	//cube vertices
	const float planeVerts[PLANE_ATTRIBUTE_NUM] =
	{
		/*pos coord           tex coord  normals*/
		//front
		-1.0, -1.0,  1.0,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f, //bottom left
		 1.0, -1.0,  1.0,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,//bottom right
		 1.0,  1.0,  1.0,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,//top right
		-1.0,  1.0,  1.0,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,//top left
	};

	//indices
	const uint32_t planeIdx[PLANE_INDICES_NUM] =
	{
		0, 1, 2,
		2, 3, 0
	};
}
//*************************************************************************
// Class: Plane
// Function Name: Plane
// Argument{s}: -
// Explanation: Plane constructor
//*************************************************************************
Plane::Plane(const char* shaderName, const Vec3& pos, const Quat& rot, const Vec3& scale) :
	Mesh(shaderName, pos, rot, scale)
{
	Init("plane", planeVerts, planeIdx, PLANE_ATTRIBUTE_NUM, PLANE_INDICES_NUM);
}

//*************************************************************************
// Class: Plane
// Function Name: ~Plane
// Argument{s}: -
// Explanation: Plane destructor
//*************************************************************************
Plane::~Plane()
{
	Delete();
}
