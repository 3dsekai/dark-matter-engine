//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Class Name: Mat3
// Source File: [mat3.cpp]
//
// License:
// Copyright(C) <2018>  <https://github.com/3dsekai/>
//
// This program is free software : you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
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
	return MathUtil::GetDeterminant(elem, MAT3_SIZE);
}

//inverse of the matrix, using classical adjoint method
Mat3 Mat3::GetInverse()
{
	float det = GetDeterminant();
	if ((unsigned int)det == 0)
	{ //the matrix is singular - can't be inverted
		return *this;
	}

	Mat3 inverse;
	int sign = 1;
	for (int col = 0; col < MAT3_SIZE; col++)
	{
		for (int row = 0; row < MAT3_SIZE; row++)
		{
			//get the submatrix of this object's matrix
			float submat[4];
			MathUtil::GetSubMatrix(this->elem, submat, row, col, MAT3_SIZE);

			//get the cofactor of the submatrix
			sign = ((row + col) % 2 == 0) ? 1 : -1;//change the sign to match the cofactor sign order
			inverse.elem[MAT3_SIZE * row + col] = sign * MathUtil::GetDeterminant(submat, MAT3_SIZE - 1);
		}
	}
	inverse.Transpose(); //get the transpose of the adjoint matrix
	return inverse * (1 / det); //inverse = adj M / det M
}