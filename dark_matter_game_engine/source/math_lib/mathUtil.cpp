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
#include "mat4.h"
#include "mat3.h"
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

	////get determinant for 3x3 matrix
	//float Det3x3(float a1, float a2, float a3, float b1, float b2, float b3, float c1, float c2, float c3)
	//{
	//	float det;

	//	det = a1 * Det2x2(b2, b3, c2, c3)
	//		- b1 * Det2x2(a2, a3, c2, c3)
	//		+ c1 * Det2x2(a2, a3, b2, b3);

	//	return det;
	//}

	////get determinant for 4x4 matrix
	//float Det4x4(float* m)
	//{
	//	float det;
	//	float a1, a2, a3, a4, b1, b2, b3, b4, c1, c2, c3, c4, d1, d2, d3, d4;

	//	a1 = m[0]; b1 = m[1];
	//	c1 = m[2]; d1 = m[3];

	//	a2 = m[4]; b2 = m[5];
	//	c2 = m[6]; d2 = m[7];

	//	a3 = m[8];  b3 = m[9];
	//	c3 = m[10]; d3 = m[11];

	//	a4 = m[12]; b4 = m[13];
	//	c4 = m[14]; d4 = m[15];

	//	det = a1 * Det3x3(b2, b3, b4, c2, c3, c4, d2, d3, d4)
	//		- b1 * Det3x3(a2, a3, a4, c2, c3, c4, d2, d3, d4)
	//		+ c1 * Det3x3(a2, a3, a4, b2, b3, b4, d2, d3, d4)
	//		- d1 * Det3x3(a2, a3, a4, b2, b3, b4, c2, c3, c4);

	//	return det;
	//}

	//get matrix classical adjoint
	void Adjoint(const Mat4& m, float* adj)
	{
		float a1, a2, a3, a4, b1, b2, b3, b4, c1, c2, c3, c4, d1, d2, d3, d4;
		Mat3 m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15;

		//a1 = m[0]; b1 = m[1];
		//c1 = m[2]; d1 = m[3];

		//a2 = m[4]; b2 = m[5];
		//c2 = m[6]; d2 = m[7];

		//a3 = m[8];  b3 = m[9];
		//c3 = m[10]; d3 = m[11];

		//a4 = m[12]; b4 = m[13];
		//c4 = m[14]; d4 = m[15];

		//assign elements to individual values to aid in selecting correct values
		a1 = m.elem[0]; b1 = m.elem[1];
		c1 = m.elem[2]; d1 = m.elem[3];

		a2 = m.elem[4]; b2 = m.elem[5];
		c2 = m.elem[6]; d2 = m.elem[7];

		a3 = m.elem[8];  b3 = m.elem[9];
		c3 = m.elem[10]; d3 = m.elem[11];

		a4 = m.elem[12]; b4 = m.elem[13];
		c4 = m.elem[14]; d4 = m.elem[15];

		//construct the 3x3 matrices necessary to calculate cofactors for adjoint
		m0 =  {b2, b3, b4, c2, c3, c4, d2, d3, d4};
		m1 =  {a2, a3, a4, c2, c3, c4, d2, d3, d4};
		m2 =  {a2, a3, a4, b2, b3, b4, d2, d3, d4};
		m3 =  {a2, a3, a4, b2, b3, b4, c2, c3, c4};

		m4 =  {b1, b3, b4, c1, c3, c4, d1, d3, d4};
		m5 =  {a1, a3, a4, c1, c3, c4, d1, d3, d4};
		m6 =  {a1, a3, a4, b1, b3, b4, d1, d3, d4};
		m7 =  {a1, a3, a4, b1, b3, b4, c1, c3, c4};

		m8  = {b1, b2, b4, c1, c2, c4, d1, d2, d4};
		m9  = {a1, a2, a4, c1, c2, c4, d1, d2, d4};
		m10 = {a1, a2, a4, b1, b2, b4, d1, d2, d4};
		m11 = {a1, a2, a4, b1, b2, b4, c1, c2, c4};

		m12 = {b1, b2, b3, c1, c2, c3, d1, d2, d3};
		m13 = {a1, a2, a3, c1, c2, c3, d1, d2, d3};
		m14 = {a1, a2, a3, b1, b2, b3, d1, d2, d3};
		m15 = {a1, a2, a3, b1, b2, b3, c1, c2, c3};

		//calculate cofactors and construct the classical adjoint
		// the rows/columns is transposed for the adjoint
		adj[0] =    m0.GetDeterminant();
		adj[4] =  - m1.GetDeterminant();
		adj[8] =    m2.GetDeterminant();
		adj[12] = - m3.GetDeterminant();

		adj[1] =  - m4.GetDeterminant();
		adj[5] =    m5.GetDeterminant();
		adj[9] =  - m6.GetDeterminant();
		adj[13] =   m7.GetDeterminant();

		adj[2] =    m8.GetDeterminant();
		adj[6] =  - m9.GetDeterminant();
		adj[10] =   m10.GetDeterminant();
		adj[14] = - m11.GetDeterminant();

		adj[3] =  - m12.GetDeterminant();
		adj[7] =    m13.GetDeterminant();
		adj[11] = - m14.GetDeterminant();
		adj[15] =   m15.GetDeterminant();
	}

	//get matrix inverse
	bool Inverse(Mat4& m, float* inv)
	{
		float det = m.GetDeterminant();

		if (det == 0.0f)
		{ // matrix is singular - can't get inverse
			return false;
		}

		//construct the adjoint matrix
		Adjoint(m, inv);

		//construct inverse matrix
		for(int r = 0; r < 4; r++)
		{
			for(int c = 0; c < 4; c++)
			{
				// inverseA = 1/adjA
				inv[4 * r + c] = inv[4 * r + c] * (1 / det);
			}
		}
		return true;
	}
}
