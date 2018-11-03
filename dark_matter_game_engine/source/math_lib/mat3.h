//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Class Name: Mat3
// Source File: [mat3.h]
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
#ifndef _MAT3_H_
#define _MAT3_H_

//*************************************************************************
// macros 
//*************************************************************************
#define MAT3_SIZE (3)
#define MAT3_ELEM_NUM (9)

//*************************************************************************
// Class
//*************************************************************************
class Mat3
{
public:

	//default constructors
	Mat3() = default;
	~Mat3() = default;

	//operator overloads
	Mat3& operator =(const Mat3& mat);
	Mat3 operator *(float k) const;
	Mat3& operator *=(float k);
	Mat3 operator *(const Mat3& mat) const;
	Mat3& operator *=(const Mat3& mat);

	//general purpose functions
	Mat3& SetIdentity();
	Mat3& Transpose();
	float GetDeterminant();
	Mat3 GetInverse();

	//identity matrix
	static Mat3 Identity()
	{
		return
		{
			1.0f, 0.0f, 0.0f, 
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 
		};
	};

public:
	float elem[MAT3_ELEM_NUM];
};
#endif
