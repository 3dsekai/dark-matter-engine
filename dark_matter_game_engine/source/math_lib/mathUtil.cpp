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
#include <array>

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

	//get determinant for 3x3 matrix
	float Det3x3(float a1, float a2, float a3, float b1, float b2, float b3, float c1, float c2, float c3)
	{
		float det;

		det = a1 * Det2x2(b2, b3, c2, c3)
			- b1 * Det2x2(a2, a3, c2, c3)
			+ c1 * Det2x2(a2, a3, b2, b3);

		return det;
	}

	//get determinant for 4x4 matrix
	float Det4x4(float* m)
	{
		float det;
		float a1, a2, a3, a4, b1, b2, b3, b4, c1, c2, c3, c4, d1, d2, d3, d4;

		a1 = m[0]; b1 = m[1];
		c1 = m[2]; d1 = m[3];

		a2 = m[4]; b2 = m[5];
		c2 = m[6]; d2 = m[7];

		a3 = m[8];  b3 = m[9];
		c3 = m[10]; d3 = m[11];

		a4 = m[12]; b4 = m[13];
		c4 = m[14]; d4 = m[15];

		det = a1 * Det3x3(b2, b3, b4, c2, c3, c4, d2, d3, d4)
			- b1 * Det3x3(a2, a3, a4, c2, c3, c4, d2, d3, d4)
			+ c1 * Det3x3(a2, a3, a4, b2, b3, b4, d2, d3, d4)
			- d1 * Det3x3(a2, a3, a4, b2, b3, b4, c2, c3, c4);

		return det;
	}

	//get matrix classical adjoint
	void Adjoint(float* m, float* adj)
	{
		float a1, a2, a3, a4, b1, b2, b3, b4, c1, c2, c3, c4, d1, d2, d3, d4;

		a1 = m[0]; b1 = m[1];
		c1 = m[2]; d1 = m[3];

		a2 = m[4]; b2 = m[5];
		c2 = m[6]; d2 = m[7];

		a3 = m[8];  b3 = m[9];
		c3 = m[10]; d3 = m[11];

		a4 = m[12]; b4 = m[13];
		c4 = m[14]; d4 = m[15];

		adj[0] =    Det3x3(b2, b3, b4, c2, c3, c4, d2, d3, d4);
		adj[4] =  - Det3x3(a2, a3, a4, c2, c3, c4, d2, d3, d4);
		adj[8] =    Det3x3(a2, a3, a4, b2, b3, b4, d2, d3, d4);
		adj[12] = - Det3x3(a2, a3, a4, b2, b3, b4, c2, c3, d4);

		adj[1] =  - Det3x3(b1, b3, b4, c1, c3, c4, d1, d3, d4);
		adj[5] =    Det3x3(a1, a3, a4, c1, c3, c4, d1, d3, d4);
		adj[9] =  - Det3x3(a1, a3, a4, b1, b3, b4, d1, d3, d4);
		adj[13] =   Det3x3(a1, a3, a4, b1, b3, b4, c1, c3, c4);

		adj[2] =    Det3x3(b1, b2, b4, c1, c2, c4, d1, d2, d4);
		adj[6] =  - Det3x3(a1, a2, a4, c1, c2, c4, d1, d2, d4);
		adj[10] =   Det3x3(a1, a2, a4, b1, b2, b4, d1, d2, d4);
		adj[14] = - Det3x3(a1, a2, a4, b1, b2, b4, c1, c2, c4);

		adj[3] =  - Det3x3(b1, b2, b3, c1, c2, c3, d1, d2, d3);
		adj[7] =    Det3x3(a1, a2, a3, c1, c2, c3, d1, d2, d3);
		adj[11] = - Det3x3(a1, a2, a3, b1, b2, b3, d1, d2, d3);
		adj[15] =   Det3x3(a1, a2, a3, b1, b2, b3, c1, c2, c3);
	}

	//get matrix inverse
	bool Inverse(float* m, float* inv)
	{
		Adjoint(m, inv);

		float det = Det4x4(inv);

		if(det == 0.0f)
		{
			return false;
		}

		for(int r = 0; r < 4; r++)
		{
			for(int c = 0; c < 4; c++)
			{
				inv[4 * r + c] = inv[4 * r + c] * (1 / det);
			}
		}
		return true;
	}
}
