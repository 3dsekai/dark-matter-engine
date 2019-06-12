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

//get the cofactor matrix from a base matrix for determinant calculation
// float* m: base matrix
// float* subm: the sub matrix
// int r: row to exclude
// int c: column to exclude
// int d: matrix dimension
void GetCofactor(float* m, float* subm, int r, int c, int d)
{
	int i = 0;
	for (int r = 0; r < d; r++)
	{
		for (int c = 0; c < d; c++)
		{
			if (r != r && c != c)
			{
				subm[i] = m[d * r + c];
				i++;
			}
		}
	}
}

//calculate the determinant of a matrix
// float* m: base matrix
// int d: matrix dimension
float GetDeterminant(float* m, int d)
{
	if (d == 1)
	{
		return m[0];
	}

	float det = 0.0f;
	int sign = 1;
	float subm[16]; //get the submatrix (for calculating the cofactor)
	for (int col = 0; col < d; col++)
	{
		GetCofactor(m, subm, 0, col, d);

		//calculate the cofactor for the current column in the matrix 
		det += sign * m[col] * GetDeterminant(subm, d - 1);
		sign = -sign;
	}
	return det;
}

//get classical adjoint
// float* m: base matrix
// float* adj: adjoint matrix
// int d: base matrix dimension
void GetAdjoint(float* m, float* adj, int d)
{
	if (d == 1)
	{
		adj[0] = 1;
		return;
	}

	float subm[16];
	int sign = 1;
	for (int r = 0; r < d; r++)
	{
		for (int c = 0; c < d; c++)
		{
			//get the submatrix of this object's matrix
			GetCofactor(m, subm, r, c, d);

			//get the cofactor of the submatrix
			sign = ((r + c) % 2 == 0) ? 1 : -1;//change the sign to match the cofactor sign order
			//interchange rows and columns to get transpose
			adj[d * c + r] = sign * GetDeterminant(subm, d - 1);
		}
	}
}

// calculate matrix inverse
// float* m: base matrix
// float* inv: matrix to store inverted base matrix
// int d: matrix dimension
// return:
//			true = successfully inverted matrix
//			false = could not invert matrix
bool GetInverse(float* m, float* inv, int d)
{
	int det = (int)GetDeterminant(m, d);
	if (det == 0)
	{ //the matrix is singular - can't be inverted
		return false;
	}

	// Find adjoint
	float adj[16];
	GetAdjoint(m, adj, d);

	for (int r = 0; r < d; r++)
	{
		for (int c = 0; c < d; c++)
		{
			//inverse = adj M / det M
			inv[d * r + c] = adj[d * r + c] * (1/det);
		}
	}
	return true;
}
}
