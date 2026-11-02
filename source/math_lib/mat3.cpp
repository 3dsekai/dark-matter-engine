//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: Mat3
// Source File: [mat3.cpp]
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
#include <math.h>
#include <string.h>
#include "mat3.h"
#include "mat4.h"
#include "mathUtil.h"

//*************************************************************************
// Functions
//*************************************************************************

//overload: equals operator
Mat3& Mat3::operator =(const Mat3& mat)
{
	memcpy(elem, mat.elem, MAT3_ELEM_NUM * sizeof(float));
	return *this;
}

//overload: multiplication by scalar operator (*)
Mat3 Mat3::operator *(float k) const
{
	Mat3 res;
	memcpy(res.elem, elem, MAT3_ELEM_NUM * sizeof(float));
	for (int col = 0; col < MAT3_SIZE; col++)
	{
		for (int row = 0; row < MAT3_SIZE; row++)
		{
			res.elem[MAT3_SIZE * row + col] *= k;
		}
	}
	return res;
}

//overload: multiplication/assignment by scalar operator (*=)
Mat3& Mat3::operator *=(float k)
{
	*this = *this * k;
	return *this;
}

//overload: multiplication by mat operator (*)
Mat3 Mat3::operator *(const Mat3& mat) const
{
	Mat3 res;
	for (int i = 0; i < MAT3_SIZE; i++)
	{
		for (int j = 0; j < MAT3_SIZE; j++)
		{
			float sum = 0;
			for (int k = 0; k < MAT3_SIZE; k++)
			{
				sum += elem[MAT3_SIZE * k + i] * mat.elem[MAT3_SIZE * j + k];
			}
			res.elem[MAT3_SIZE * j + i] = sum;
		}
	}
	return res;
}

//overload: multiplication/assignment by mat operator (*=)
Mat3& Mat3::operator *=(const Mat3& mat)
{
	*this = *this * mat;
	return *this;
}

//set identity matrix
Mat3& Mat3::SetIdentity()
{
	float identity[MAT3_ELEM_NUM] = 
	{
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
	};
	memcpy(elem, identity, MAT3_ELEM_NUM * sizeof(float));
	return *this;
}

//transpose the matrix
Mat3& Mat3::Transpose()
{
	Mat3 transposed;
	for (int col = 0; col < MAT3_SIZE; col++)
	{
		for (int row = 0; row < MAT3_SIZE; row++)
		{
			transposed.elem[MAT3_SIZE * row + col] = elem[MAT3_SIZE * col + row];
		}
	}
	*this = transposed;
	return *this;
}

/*
Get the determinant of this 3x3 matrix

3x3 matrix form:

| a1  b1  c1 |
| a2  b2  c2 |
| a3  b3  c3 |

*/
float Mat3::GetDeterminant()
{
	float det;
	float a1, a2, a3, b1, b2, b3, c1, c2, c3;
	a1 = elem[0]; b1 = elem[1]; c1 = elem[2];
	a2 = elem[3]; b2 = elem[4]; c2 = elem[5];
	a3 = elem[6]; b3 = elem[7]; c3 = elem[8];

	det = a1 * MathUtil::Det2x2(b2, b3, c2, c3)
		- b1 * MathUtil::Det2x2(a2, a3, c2, c3)
		+ c1 * MathUtil::Det2x2(a2, a3, b2, b3);

	return det;
}

//get 3x3 matrix classical adjoint
//for math reference:3D Math Primer for Graphics and Game Development pg. 168 - 171
//for algorithm reference: Graphics Gems pg. 767
Mat3 Mat3::GetAdjoint()
{
	float a1, a2, a3, b1, b2, b3, c1, c2, c3;

	//assign elements to individual values to aid in selecting correct values
	a1 = elem[0]; b1 = elem[1]; c1 = elem[2];
	a2 = elem[3]; b2 = elem[4]; c2 = elem[5];
	a3 = elem[6]; b3 = elem[7]; c3 = elem[8];

	//calculate cofactors and construct the classical adjoint
	// the rows/columns is transposed for the adjoint
	Mat3 adj;
	adj.elem[0] = MathUtil::Det2x2(b2, b3, c2, c3);
	adj.elem[3] = -MathUtil::Det2x2(a2, a3, c2, c3);
	adj.elem[6] = MathUtil::Det2x2(a2, a3, b2, b3);

	adj.elem[1] = -MathUtil::Det2x2(b1, b3, c1, c3);
	adj.elem[4] = MathUtil::Det2x2(a1, a3, c1, c3);
	adj.elem[7] = -MathUtil::Det2x2(a1, a3, b1, b3);

	adj.elem[2] = MathUtil::Det2x2(b1, b2, c1, c2);
	adj.elem[5] = -MathUtil::Det2x2(a1, a2, c1, c2);
	adj.elem[8] = MathUtil::Det2x2(a1, a2, b1, b2);
	return adj;
}

//get 3x3 matrix inverse
//for math reference:3D Math Primer for Graphics and Game Development pg. 168 - 171
//for algorithm reference: Graphics Gems pg. 766
Mat3 Mat3::GetInverse()
{
	float det = GetDeterminant();

	if (fabs(det) < SMALL_NUMBER)
	{ // matrix is singular - can't get inverse
		return Identity();
	}

	//construct the adjoint matrix
	Mat3 inv = GetAdjoint();

	//construct inverse matrix
	for (int r = 0; r < MAT3_SIZE; r++)
	{
		for (int c = 0; c < MAT3_SIZE; c++)
		{
			// inverseA = 1/adjA
			inv.elem[MAT3_SIZE * r + c] = inv.elem[MAT3_SIZE * r + c] * (1 / det);
		}
	}
	return inv;
}

//get the matrix normal
Mat3 Mat3::GetMatrixNormal()
{
	//matrix normal: the transpose of the inverse of a matrix
	return (*this).GetInverse().Transpose();
}

//convert mat4 to mat3
Mat3 Mat3::Mat4ToMat3(const Mat4& m)
{
	return
	{
		m.elem[0], m.elem[1], m.elem[2],
		m.elem[4], m.elem[5], m.elem[6],
		m.elem[8], m.elem[9], m.elem[10]
	};
}

//identity matrix
Mat3 Mat3::Identity()
{
	return
	{
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
	};
}
