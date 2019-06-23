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

//determinant
float Mat3::GetDeterminant()
{
	return 0.0f;
	//return MathUtil::GetDeterminant(elem, MAT3_SIZE);
}

//inverse of the matrix, using classical adjoint method
Mat3 Mat3::GetInverse()
{
	return Identity();
	//Mat3 inv;
	//bool res = MathUtil::GetInverse(this->elem, inv.elem, MAT3_SIZE);
	//if (!res)
	//{ //inverse calculation failed
	//	inv = Identity();
	//}
	//return inv;
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
