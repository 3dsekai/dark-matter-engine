//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: -
// Source File: [collisionUtils.h]
//
// License:
// Copyright(C) <2020>  <Christopher Tall>
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
#ifndef _COL_DET_UTILS_H_
#define _COL_DET_UTILS_H_

//*************************************************************************
// include
//*************************************************************************
#include "../math_lib/vec3.h"

//*************************************************************************
// Collision Detection Utility Functions
//*************************************************************************
namespace ColDetUtils
{
	//*************************************************************************
	// Definitions
	//*************************************************************************
	bool linePolygonHitCheck(const Vec3& p0, const Vec3& p1, const Vec3& p2, const Vec3& pos0, const Vec3& pos1);
}
#endif
