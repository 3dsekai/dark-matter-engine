//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Class Name: Vec4
// Source File: [vec4.cpp]
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
#include <math.h>
#include "vec4.h"
#include "mat4.h"

//*************************************************************************
// Functions
//*************************************************************************
//constructors
Vec4::Vec4() :
	x(0.0f),
	y(0.0f),
	z(0.0f),
	w(0.0f)
{};

Vec4::Vec4(float X, float Y, float Z, float W) :
	x(X),
	y(Y),
	z(Z),
	w(W)
{};

//overload: addition to vec operator (+)
Vec4 Vec4::operator +(const Vec4& vec) const
{
	return Vec4(this->x + vec.x,
				this->y + vec.y,
				this->z + vec.z,
				this->w);
}

//overload: subtraction from vec operator (-)
Vec4 Vec4::operator -(const Vec4& vec) const
{
	return Vec4(this->x - vec.x,
				this->y - vec.y,
				this->z - vec.z,
				this->w);
}

//overload: multiplication by vec operator (*)
Vec4 Vec4:: operator *(const Vec4& vec) const
{
	return Vec4(this->x * vec.x,
				this->y * vec.y,
				this->z * vec.z,
				this->w);
}

//overload: division by vec operator (/)
Vec4 Vec4::operator /(const Vec4& vec) const
{
	return Vec4(this->x / vec.x,
				this->y / vec.y,
				this->z / vec.z,
				this->w);
}

//overload: addition by scalar operator (+)
Vec4 Vec4:: operator +(float scalar) const
{
	return Vec4(this->x + scalar,
				this->y + scalar,
				this->z + scalar,
				this->w);
}

//overload: subtraction by scalar operator (-)
Vec4 Vec4::operator -(float scalar) const
{
	return Vec4(this->x - scalar,
				this->y - scalar,
				this->z - scalar,
				this->w - scalar);
}

//overload: multiplication by scalar operator (*)
Vec4 Vec4:: operator *(float scalar) const
{
	return Vec4(this->x * scalar,
				this->y * scalar,
				this->z * scalar,
				this->w);
}

//overload: division by scalar operator (/)
Vec4 Vec4::operator /(float scalar) const
{
	return Vec4(this->x / scalar,
				this->y / scalar,
				this->z / scalar,
				this->w);
}

//overload: multiplication by 4x4 matrix operator (*)
//NOTE: using column vectors, column-major (res = MAT * POINT)
Vec4 Vec4::operator *(const Mat4& mat) const
{
	return Vec4((x * mat.elem[0])  + (y * mat.elem[1]) +  (z * mat.elem[2])  + (w * mat.elem[3]),
				(x * mat.elem[4])  + (y * mat.elem[5]) +  (z * mat.elem[6])  + (w * mat.elem[7]),
				(x * mat.elem[8])  + (y * mat.elem[9]) +  (z * mat.elem[10]) + (w * mat.elem[11]),
				(x * mat.elem[12]) + (y * mat.elem[13]) + (z * mat.elem[14]) + (w * mat.elem[15]));
}

//overload: modulus operator (%)
//overload: assignment operator (=)
Vec4& Vec4::operator =(const Vec4& vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
	w = vec.w;
	return *this;
}

//overload: equality for vectors operator (==)
//NOTE: comparing floats is bad. Probably shouldn't use this.
bool Vec4::operator ==(const Vec4& vec) const
{
	return (this->x == vec.x && 
			this->y == vec.y &&
			this->z == vec.z &&
			this->w == vec.w);
}

//overload: inequality for vectors operator (!=)
//NOTE: comparing floats is bad. Probably shouldn't use this.
bool Vec4::operator !=(const Vec4& vec) const
{
	return (this->x != vec.x || 
			this->y != vec.y ||
			this->z != vec.z ||
			this->w != vec.w);
}

//overload: addition/assignment by vec operator (+=)
Vec4& Vec4::operator +=(const Vec4& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
	return *this;
}

//overload: subtraction/assignment by vec operator (-=)
Vec4& Vec4::operator -=(const Vec4& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	return *this;
}

//overload: multiplication/assignment by vec operator (*=)
Vec4& Vec4::operator *=(const Vec4& vec)
{
	x *= vec.x;
	y *= vec.y;
	z *= vec.z;
	return *this;
}

//overload: division/assignment by vec operator (/=)
Vec4& Vec4::operator /=(const Vec4& vec)
{
	x /= vec.x;
	y /= vec.y;
	z /= vec.z;
	return *this;
}

//overload: multiplication/assignment by 4x4 matrix operator (*=)
//NOTE: using column vectors, column-major (res = MAT * POINT)
Vec4& Vec4::operator *=(const Mat4& mat)
{
	x = (x * mat.elem[0])  + (y * mat.elem[1]) +  (z * mat.elem[2])  + (w * mat.elem[3]);
	y = (x * mat.elem[4])  + (y * mat.elem[5]) +  (z * mat.elem[6])  + (w * mat.elem[7]);
	z = (x * mat.elem[8])  + (y * mat.elem[9]) +  (z * mat.elem[10]) + (w * mat.elem[11]);
	w = (x * mat.elem[12]) + (y * mat.elem[13]) + (z * mat.elem[14]) + (w * mat.elem[15]);
	return *this;
}

//overload: vector negation (-vec)
Vec4 Vec4::operator -()
{
	return Vec4(-x, -y, -z, w);
}

//vector length
float Vec4::Length() const
{
	float len_sqr = this->x * this->x +
				    this->y * this->y +
				    this->z * this->z;
	return sqrtf(len_sqr);
}

//normalize vector
Vec4& Vec4::Normalize()
{
	float len = this->Length();
	x /= len;
	y /= len;
	z /= len;

	return *this;
}

//get normalized vector
Vec4 Vec4::GetNormalizedVec() const
{
	Vec4 norm_vec = *this;
	norm_vec.Normalize();
	return norm_vec;
}

//dot product
float Vec4::Dot(Vec4 vec) const
{
	return this->x * vec.x +
		   this->y * vec.y +
		   this->z * vec.z;
}

//cross product
Vec4 Vec4::Cross(Vec4 vec) const
{
	return Vec4(this->y * vec.z - this->z * vec.y,
				this->z * vec.x - this->x * vec.z,
				this->x * vec.y - this->y * vec.x,
				this->w);
}
