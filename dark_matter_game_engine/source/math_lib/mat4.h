//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Class Name: Mat4
// Source File: [mat4.h]
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
#ifndef _MAT4_H_
#define _MAT4_H_
//*************************************************************************
// Includes
//*************************************************************************
#include "vec3.h"

class Quat;

//*************************************************************************
// macros 
//*************************************************************************
#define MAT4_SIZE (4)
#define MAT4_ELEM_NUM (16)

//*************************************************************************
// Class
// on opengl transformations:
//https://www.opengl.org/archives/resources/faq/technical/transformations.htm
//matrices are column-major
//https://stackoverflow.com/questions/22145037/matrix-multiplication-as-column-major
//https://stackoverflow.com/questions/13293469/why-does-my-translation-matrix-needs-to-be-transposed#13294326
//*************************************************************************
class Mat4
{
public:
	Mat4() = default;
	~Mat4() = default;

	//operator overloads
	Mat4& operator =(const Mat4& mat);
	Mat4 operator *(float k) const;
	Mat4& operator *=(float k);
	Mat4 operator *(const Mat4& mat) const;
	Mat4& operator *=(const Mat4& mat);

	//general purpose functions
	Mat4& SetIdentity();
	Mat4& Transpose();
	float GetDeterminant();
	Mat4 GetInverse();
	Mat4 Translate(const Vec3& vec);
	Mat4 Scale(const Vec3& vec);
	Mat4 Rotate(const Vec3& vec);
	Mat4 Rotate(const Quat& q);
	Mat4 RotateXAxis(const float rad);
	Mat4 RotateYAxis(const float rad);
	Mat4 RotateZAxis(const float rad);
	Mat4 Perspective(const float fovy, const float aspect, const float zNear, const float zFar);
	Mat4 LookAt(const Vec3& eye, const Vec3& center, const Vec3& up);

	//identity matrix
	static Mat4 Identity()
	{
		return
		{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	};

	//translation
	static Mat4 TranslateMat(const Vec3& vec)
	{
		return
		{
			1.0f,  0.0f,  0.0f,  0.0f,
			0.0f,  1.0f,  0.0f,  0.0f,
			0.0f,  0.0f,  1.0f,  0.0f,
			vec.x, vec.y, vec.z, 1.0f
		};
	};
	//scaling
	static Mat4 ScaleMat(const Vec3& vec)
	{
		return
		{
			vec.x, 0.0f,  0.0f,  0.0f,
			0.0f,  vec.y, 0.0f,  0.0f,
			0.0f,  0.0f,  vec.z, 0.0f,
			0.0f,  0.0f,  0.0f,  1.0f
		};
	};
	//rotation: X
	static Mat4 RotXMat(const float rad)
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
	};
	//rotation: Y
	static Mat4 RotYMat(const float rad)
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
	};
	//rotation: Z
	static Mat4 RotZMat(const float rad)
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
	};

public:
	float elem[MAT4_ELEM_NUM];
};
#endif
