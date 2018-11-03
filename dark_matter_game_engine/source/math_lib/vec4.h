//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Class Name: Vec4
// Source File: [vec4.h]
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
#ifndef _VEC4_H_
#define _VEC4_H_
//*************************************************************************
// Includes
//*************************************************************************
class Mat4;

//*************************************************************************
// Class
//*************************************************************************
class Vec4
{
public:

	//constructors
	Vec4();
	Vec4(float X, float Y, float Z, float W);

	//operator overloads
	Vec4 operator +(const Vec4& vec) const;
	Vec4 operator -(const Vec4& vec) const;
	Vec4 operator *(const Vec4& vec) const;
	Vec4 operator /(const Vec4& vec) const;
	Vec4 operator +(float scalar) const;
	Vec4 operator -(float scalar) const;
	Vec4 operator *(float scalar) const;
	Vec4 operator /(float scalar) const;
	Vec4 operator *(const Mat4& mat) const;
	Vec4& operator =(const Vec4& vec);
	bool operator ==(const Vec4& vec) const;
	bool operator !=(const Vec4& vec) const;
	Vec4& operator +=(const Vec4& vec);
	Vec4& operator -=(const Vec4& vec);
	Vec4& operator *=(const Vec4& vec);
	Vec4& operator /=(const Vec4& vec);
	Vec4& operator *=(const Mat4& mat);
	Vec4 operator -();

	//general purpose functions
	float Length() const;
	Vec4& Normalize();
	Vec4 GetNormalizedVec() const;
	float Dot(Vec4 vec) const;
	Vec4 Cross(Vec4 vec) const;

public:
	float x;
	float y;
	float z;
	float w;
};
#endif
