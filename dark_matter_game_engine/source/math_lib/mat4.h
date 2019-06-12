//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: Mat4
// Source File: [mat4.h]
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
#ifndef _MAT4_H_
#define _MAT4_H_
//*************************************************************************
// Includes
//*************************************************************************
class Vec3;
class Quat;
class Mat3;

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
	Mat4 GetMatrixNormal();
	Mat4 Translate(const Vec3& vec);
	Mat4 Scale(const Vec3& vec);
	Mat4 Rotate(const Vec3& vec);
	Mat4 Rotate(const Quat& q);
	Mat4 RotateXAxis(const float rad);
	Mat4 RotateYAxis(const float rad);
	Mat4 RotateZAxis(const float rad);
	Mat4 Perspective(const float fovy, const float aspect, const float zNear, const float zFar);
	Mat4 LookAt(const Vec3& eye, const Vec3& center, const Vec3& up);
	Vec3 GetTranslation();

	static Mat4 Mat3ToMat4(const Mat3& m);

	//identity matrix
	static Mat4 Identity();
	//translation
	static Mat4 TranslateMat(const Vec3& vec);
	//scaling
	static Mat4 ScaleMat(const Vec3& vec);
	//rotation: X
	static Mat4 RotXMat(const float rad);
	//rotation: Y
	static Mat4 RotYMat(const float rad);
	//rotation: Z
	static Mat4 RotZMat(const float rad);

public:
	float elem[MAT4_ELEM_NUM];
};
#endif
