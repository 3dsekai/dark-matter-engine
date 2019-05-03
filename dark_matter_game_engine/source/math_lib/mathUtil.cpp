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

	//get the minor matrix from a base matrix for determinant calculation
	void GetMinor(const float mat[], float submat[], int r, int c, int dim)
	{
		int i = -1;
		for (int col = 0; col < dim; col++)
		{
			for (int row = 0; row < dim; row++)
			{
				if (row != r && col != c)
				{
					submat[++i] = mat[dim * row + col];
				}
			}
		}
	}

	//calculate the determinant of a matrix
	float GetDeterminant(const float mat[], int dimension)
	{
		if (dimension <= 2)
		{
			return mat[0] * mat[3] - mat[1] * mat[2];
		}

		float det = 0.0f;
		int sign = 1;
//		const int size = (dimension - 1) * (dimension - 1);
		for (int col = 0; col < dimension; col++)
		{
			//get the submatrix (for calculating the cofactor)
			float submat[16];
			GetMinor(mat, submat, 0, col, dimension);

			//calculate the cofactor for the current column in the matrix 
			det += sign * mat[col] * GetDeterminant(submat, dimension - 1);
			sign = -sign;
		}
		return det;
	}
}