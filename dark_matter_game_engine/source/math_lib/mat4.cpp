//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: Mat4
// Source File: [mat4.cpp]
//
// License:
// Copyright(C) <2018>  <Christopher Tall>
//
// This is software is copyrighted.
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
#include "mat4.h"
#include "quat.h"

//*************************************************************************
// Functions
//*************************************************************************

//overload: equals operator
Mat4& Mat4::operator =(const Mat4& mat)
{
	memcpy(elem, mat.elem, MAT4_ELEM_NUM * sizeof(float));
	return *this;
}

//overload: multiplication by scalar operator (*)
Mat4 Mat4::operator *(float k) const
{
	Mat4 res;
	memcpy(res.elem, elem, MAT4_ELEM_NUM * sizeof(float));
	for (int col = 0; col < MAT4_SIZE; col++)
	{
		for (int row = 0; row < MAT4_SIZE; row++)
		{
			res.elem[MAT4_SIZE * row + col] *= k;
		}
	}
	return res;
}

//overload: multiplication/assignment by scalar operator (*=)
Mat4& Mat4::operator *=(float k)
{
	*this = *this * k;
	return *this;
}

//overload: multiplication by mat operator (*)
Mat4 Mat4::operator *(const Mat4& mat) const
{
	Mat4 res;
	for (int i = 0; i < MAT4_SIZE; i++)
	{
		for (int j = 0; j < MAT4_SIZE; j++)
		{
			float sum = 0;
			for (int k = 0; k < MAT4_SIZE; k++)
			{
				sum += elem[MAT4_SIZE * k + i] * mat.elem[MAT4_SIZE * j + k];
			}
			res.elem[MAT4_SIZE * j + i] = sum;
		}
	}
	return res;
}

//overload: multiplication/assignment by mat operator (*=)
Mat4& Mat4::operator *=(const Mat4& mat)
{
	*this = *this * mat;
	return *this;
}

//set identity matrix
Mat4& Mat4::SetIdentity()
{
	float identity[MAT4_ELEM_NUM] = 
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	memcpy(elem, identity, MAT4_ELEM_NUM * sizeof(float));
	return *this;
}

//transpose the matrix
Mat4& Mat4::Transpose()
{
	Mat4 transposed;
	for (int col = 0; col < MAT4_SIZE; col++)
	{
		for (int row = 0; row < MAT4_SIZE; row++)
		{
			transposed.elem[MAT4_SIZE * row + col] = elem[MAT4_SIZE * col + row];
		}
	}
	*this = transposed;
	return *this;
}

//determinant
float Mat4::GetDeterminant()
{
	return MathUtil::GetDeterminant(elem, MAT4_SIZE);
}

//inverse of the matrix, using classical adjoint method
Mat4 Mat4::GetInverse()
{
	float det = GetDeterminant();
	if ((unsigned int)det == 0)
	{ //the matrix is singular - can't be inverted
		return *this;
	}

	Mat4 inverse;
	int sign = 1;
	for (int col = 0; col < MAT4_SIZE; col++)
	{
		for (int row = 0; row < MAT4_SIZE; row++)
		{
			//get the submatrix of this object's matrix
			float submat[9];
			MathUtil::GetSubMatrix(this->elem, submat, row, col, MAT4_SIZE);

			//get the cofactor of the submatrix
			sign = ((row + col) % 2 == 0) ? 1 : -1;//change the sign to match the cofactor sign order
			inverse.elem[MAT4_SIZE * row + col] = sign * MathUtil::GetDeterminant(submat, MAT4_SIZE - 1);
		}
	}
	inverse.Transpose(); //get the transpose of the adjoint matrix
	return inverse * (1 / det); //inverse = adj M / det M
}

//generate translation matrix
Mat4 Mat4::Translate(const Vec3& vec)
{
	return (*this * TranslateMat(vec));
}

//generate scale matrix
Mat4 Mat4::Scale(const Vec3& vec)
{
	return (*this * ScaleMat(vec));
}

//generate rotation matrix from 3d vector
Mat4 Mat4::Rotate(const Vec3& vec)
{
	return (*this * RotXMat(vec.x) * RotYMat(vec.y) * RotZMat(vec.z));
}

//quaternion to rotation matrix
Mat4 Mat4::Rotate(const Quat& q)
{
	Mat3 q2m = Quat::Quat2Mat(q);
	Mat4 rMat = Identity();
	rMat.elem[0]  = q2m.elem[0];
	rMat.elem[1]  = q2m.elem[1];
	rMat.elem[2]  = q2m.elem[2];
	rMat.elem[4]  = q2m.elem[3];
	rMat.elem[5]  = q2m.elem[4];
	rMat.elem[6]  = q2m.elem[5];
	rMat.elem[8]  = q2m.elem[6];
	rMat.elem[9]  = q2m.elem[7];
	rMat.elem[10] = q2m.elem[8];

	return *this * rMat;
}

//rotate around X axis by {rad} degrees
Mat4 Mat4::RotateXAxis(const float rad)
{
	return (*this * RotXMat(rad));
}

//rotate around Y axis by {rad} degrees
Mat4 Mat4::RotateYAxis(const float rad)
{
	return (*this * RotYMat(rad));
}

//rotate around Z axis by {rad} degrees
Mat4 Mat4::RotateZAxis(const float rad)
{
	return (*this * RotZMat(rad));
}

//calculate a matrix for perspective projection. gluPerspective implementation.
Mat4 Mat4::Perspective(const float fovy, const float aspect, const float zNear, const float zFar)
{
	float zoom = 1/tanf(fovy/2);

	Mat4 proj_mat = 
	{
		zoom/aspect, 0,    0,                           0,
		0,           zoom, 0,                           0,
		0,           0,    (zFar+zNear)/(zNear-zFar),  -1,
		0,           0,    (2*zFar*zNear)/(zNear-zFar), 0
	};

	return (*this * proj_mat);
}

//calculate the lookAt matrix. gluLookAt implementation.
Mat4 Mat4::LookAt(const Vec3& eye, const Vec3& center, const Vec3& up)
{
	Vec3 dir;
	Vec3 right;
	Vec3 eye_up;
	Vec3 eye_vec = eye;

	//get the direction of the eye to the origin (scene center)
	dir = center - eye;
	dir.Normalize();

	//calculate the right (positive x axis) vector
	right = dir.Cross(up);
	right.Normalize();

	//calculate the camera's up (positive y axis) vector
	eye_up = right.Cross(dir);
	eye_up.Normalize();

	//define look at matrix
	Mat4 look_at = 
	{
		right.x, eye_up.x, -dir.x, 0,
		right.y, eye_up.y, -dir.y, 0,
		right.z, eye_up.z, -dir.z, 0,
		0,       0,         0,     1
		
	};

	//define the eye translation matrix
	//invert the position because we translate the world in the
	//opposite direction the eye is moving.
	Mat4 eye_pos = TranslateMat(-eye_vec);

	//get the look at matrix;
	return (*this * look_at * eye_pos);
}
