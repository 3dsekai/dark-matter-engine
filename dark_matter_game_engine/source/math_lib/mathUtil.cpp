//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: -
// Source File: [mathUtil.cpp]
//
// License:
// Copyright(C) <2018/2019>  <Christopher Tall>
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
#include <math.h>
#include <string.h>
#include "mathUtil.h"
//*************************************************************************
// Math Utility Functions
//*************************************************************************
namespace MathUtil
{
	//simple clamp for float values
	float Clamp(float val, float upper, float lower)
	{
		return MIN(upper, MAX(val, lower));
	}

	//convert degrees to radians
	float Deg2Rad(float deg)
	{
		return deg * (PI / 180.0f);
	}

	//convert radians to degrees
	float Rad2Deg(float rad)
	{
		return rad * (180.0f / PI);
	}

	//get determinant for 2x2 matrix
	float Det2x2(float a, float b, float c, float d)
	{
		return a * d - b * c;
	}
}
