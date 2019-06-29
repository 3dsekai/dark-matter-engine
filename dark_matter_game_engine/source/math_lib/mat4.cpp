//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: Mat4
// Source File: [mat4.cpp]
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
#include "mat4.h"
#include "mat3.h"
#include "quat.h"
#include "vec3.h"
#include "mathUtil.h"
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

/*
Get the determinant of this 4x4 matrix

4x4 matrix form:

| a1  b1  c1  d1 |
| a2  b2  c2  d2 |
| a3  b3  c3  d3 |
| a4  b4  c4  d4 |

*/
float Mat4::GetDeterminant()
{
	float det;
	float a1, a2, a3, a4, b1, b2, b3, b4, c1, c2, c3, c4, d1, d2, d3, d4;

	a1 = elem[0];  b1 = elem[1];
	c1 = elem[2];  d1 = elem[3];

	a2 = elem[4];  b2 = elem[5];
	c2 = elem[6];  d2 = elem[7];

	a3 = elem[8];  b3 = elem[9];
	c3 = elem[10]; d3 = elem[11];

	a4 = elem[12]; b4 = elem[13];
	c4 = elem[14]; d4 = elem[15];

	Mat3 m0 = { b2, b3, b4, c2, c3, c4, d2, d3, d4 };
	Mat3 m1 = { a2, a3, a4, c2, c3, c4, d2, d3, d4 };
	Mat3 m2 = { a2, a3, a4, b2, b3, b4, d2, d3, d4 };
	Mat3 m3 = { a2, a3, a4, b2, b3, b4, c2, c3, c4 };

	det = a1 * m0.GetDeterminant()
		- b1 * m1.GetDeterminant()
		+ c1 * m2.GetDeterminant()
		- d1 * m3.GetDeterminant();

	return det;
}

//get 4x4 matrix classical adjoint
//for math reference:3D Math Primer for Graphics and Game Development pg. 168 - 171
//for algorithm reference: Graphics Gems pg. 767
Mat4 Mat4::GetAdjoint()
{
	float a1, a2, a3, a4, b1, b2, b3, b4, c1, c2, c3, c4, d1, d2, d3, d4;
	Mat3 m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15;
	Mat4 adj;

	//assign elements to individual values to aid in selecting correct values
	a1 = elem[0]; b1 = elem[1];
	c1 = elem[2]; d1 = elem[3];

	a2 = elem[4]; b2 = elem[5];
	c2 = elem[6]; d2 = elem[7];

	a3 = elem[8];  b3 = elem[9];
	c3 = elem[10]; d3 = elem[11];

	a4 = elem[12]; b4 = elem[13];
	c4 = elem[14]; d4 = elem[15];

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
	adj.elem[0] =    m0.GetDeterminant();
	adj.elem[4] =  - m1.GetDeterminant();
	adj.elem[8] =    m2.GetDeterminant();
	adj.elem[12] = - m3.GetDeterminant();

	adj.elem[1] =  - m4.GetDeterminant();
	adj.elem[5] =    m5.GetDeterminant();
	adj.elem[9] =  - m6.GetDeterminant();
	adj.elem[13] =   m7.GetDeterminant();

	adj.elem[2] =    m8.GetDeterminant();
	adj.elem[6] =  - m9.GetDeterminant();
	adj.elem[10] =   m10.GetDeterminant();
	adj.elem[14] = - m11.GetDeterminant();

	adj.elem[3] =  - m12.GetDeterminant();
	adj.elem[7] =    m13.GetDeterminant();
	adj.elem[11] = - m14.GetDeterminant();
	adj.elem[15] =   m15.GetDeterminant();

	return adj;
}


//get 4x4 matrix inverse
//for math reference:3D Math Primer for Graphics and Game Development pg. 168 - 171
//for algorithm reference: Graphics Gems pg. 766
Mat4 Mat4::GetInverse()
{
	float det = GetDeterminant();

	if ( fabs( det ) < SMALL_NUMBER)
	{ // matrix is singular - can't get inverse
		return Identity();
	}

	//construct the adjoint matrix
	Mat4 inv = GetAdjoint();

	//construct inverse matrix
	for(int r = 0; r < MAT4_SIZE; r++)
	{
		for(int c = 0; c < MAT4_SIZE; c++)
		{
			// inverseA = 1/adjA
			inv.elem[MAT4_SIZE * r + c] = inv.elem[MAT4_SIZE * r + c] * (1 / det);
		}
	}
	return inv;
}

//get the matrix normal
Mat4 Mat4::GetMatrixNormal()
{
	//matrix normal: the transpose of the inverse of a matrix
	return (*this).GetInverse().Transpose();
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

//get translation
Vec3 Mat4::GetTranslation()
{
	return Vec3(elem[12], elem[13], elem[14]);
}

//convert mat3 to mat4
Mat4 Mat4::Mat3ToMat4(const Mat3& m)
{
	return
	{
		m.elem[0], m.elem[1], m.elem[2],  1.0f,
		m.elem[4], m.elem[5], m.elem[6],  1.0f,
		m.elem[8], m.elem[9], m.elem[10], 1.0f,
		1.0f,      1.0f,      1.0f,       1.0f
	};
}

//identity matrix
Mat4 Mat4::Identity()
{
	return
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

//translation
Mat4 Mat4::TranslateMat(const Vec3& vec)
{
	return
	{
		1.0f,  0.0f,  0.0f,  0.0f,
		0.0f,  1.0f,  0.0f,  0.0f,
		0.0f,  0.0f,  1.0f,  0.0f,
		vec.x, vec.y, vec.z, 1.0f
	};
}

//scaling
Mat4 Mat4::ScaleMat(const Vec3& vec)
{
	return
	{
		vec.x, 0.0f,  0.0f,  0.0f,
		0.0f,  vec.y, 0.0f,  0.0f,
		0.0f,  0.0f,  vec.z, 0.0f,
		0.0f,  0.0f,  0.0f,  1.0f
	};
}

//rotation: X
Mat4 Mat4::RotXMat(const float rad)
{
	float cosAng = cosf(rad);
	float sinAng = sinf(rad);
	return
	{
		1.0f,  0.0f,   0.0f,   0.0f,
		0.0f,  cosAng, sinAng, 0.0f,
		0.0f, -sinAng, cosAng, 0.0f,
		0.0f,  0.0f,   0.0f,   1.0f
	};
}

//rotation: Y
Mat4 Mat4::RotYMat(const float rad)
{
	float cosAng = cosf(rad);
	float sinAng = sinf(rad);
	return
	{
		cosAng, 0.0f, -sinAng, 0.0f,
		0.0f,   1.0f,  0.0f,   0.0f,
		sinAng, 0.0f,  cosAng, 0.0f,
		0.0f,   0.0f,  0.0f,   1.0f
	};
}

//rotation: Z
Mat4 Mat4::RotZMat(const float rad)
{
	float cosAng = cosf(rad);
	float sinAng = sinf(rad);
	return
	{
		cosAng, sinAng, 0.0f, 0.0f,
		-sinAng, cosAng, 0.0f, 0.0f,
		0.0f,   0.0f,   1.0f, 0.0f,
		0.0f,   0.0f,   0.0f, 1.0f
	};
}
