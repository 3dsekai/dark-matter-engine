//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Class Name: Vec3
// Source File: [vec3.cpp]
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
#include "vec3.h"
#include "mat3.h"

//*************************************************************************
// Functions
//*************************************************************************
//constructors
Vec3::Vec3() :
	x(0.0f),
	y(0.0f),
	z(0.0f)
{}

Vec3::Vec3(float X, float Y, float Z) :
	x(X),
	y(Y),
	z(Z)
{}

//overload: addition to vec operator (+)
Vec3 Vec3::operator +(const Vec3& vec) const
{
	return Vec3(this->x + vec.x,
				this->y + vec.y,
				this->z + vec.z);
}

//overload: subtraction from vec operator (-)
Vec3 Vec3::operator -(const Vec3& vec) const
{
	return Vec3(this->x - vec.x,
				this->y - vec.y,
				this->z - vec.z);
}

//overload: multiplication by vec operator (*)
Vec3 Vec3::operator *(const Vec3& vec) const
{
	return Vec3(this->x * vec.x,
				this->y * vec.y,
				this->z * vec.z);
}

//overload: division by vec operator (/)
Vec3 Vec3::operator /(const Vec3& vec) const
{
	return Vec3(this->x / vec.x,
				this->y / vec.y,
				this->z / vec.z);
}

//overload: addition by scalar operator (+)
Vec3 Vec3::operator +(float scalar) const
{
	return Vec3(this->x + scalar,
				this->y + scalar,
				this->z + scalar);
}

//overload: subtraction by scalar operator (-)
Vec3 Vec3::operator -(float scalar) const
{
	return Vec3(this->x - scalar,
				this->y - scalar,
				this->z - scalar);
}

//overload: multiplication by scalar operator (*)
Vec3 Vec3::operator *(float scalar) const
{
	return Vec3(this->x * scalar,
				this->y * scalar,
				this->z * scalar);
}

//overload: division by scalar operator (/)
Vec3 Vec3::operator /(float scalar) const
{
	return Vec3(this->x / scalar,
				this->y / scalar,
				this->z / scalar);
}

//overload: multiplication by 3x3 matrix operator (*)
//NOTE: using column vectors, column-major (res = MAT * 3DVEC)
Vec3 Vec3::operator *(const Mat3& mat) const
{
	return Vec3((x * mat.elem[0]) + (y * mat.elem[1]) + (z * mat.elem[2]),
				(x * mat.elem[3]) + (y * mat.elem[4]) + (z * mat.elem[5]),
				(x * mat.elem[6]) + (y * mat.elem[7]) + (z * mat.elem[8]));
}

//overload: modulus operator (%)
//overload: assignment operator (=)
Vec3& Vec3::operator =(const Vec3& vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
	return *this;
}

//overload: equality for vectors operator (==)
//NOTE: comparing floats is bad. Probably shouldn't use this.
bool Vec3::operator ==(const Vec3& vec) const
{
	return (this->x == vec.x && 
			this->y == vec.y &&
			this->z == vec.z);
}

//overload: inequality for vectors operator (!=)
//NOTE: comparing floats is bad. Probably shouldn't use this.
bool Vec3::operator !=(const Vec3& vec) const
{
	return (this->x != vec.x || 
			this->y != vec.y ||
			this->z != vec.z);
}

//overload: addition/assignment by vec operator (+=)
Vec3& Vec3::operator +=(const Vec3& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
	return *this;
}

//overload: subtraction/assignment by vec operator (-=)
Vec3& Vec3::operator -=(const Vec3& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	return *this;
}

//overload: multiplication/assignment by vec operator (*=)
Vec3& Vec3::operator *=(const Vec3& vec)
{
	x *= vec.x;
	y *= vec.y;
	z *= vec.z;
	return *this;
}

//overload: division/assignment by vec operator (/=)
Vec3& Vec3::operator /=(const Vec3& vec)
{
	x /= vec.x;
	y /= vec.y;
	z /= vec.z;
	return *this;
}

//overload: multiplication/assignment by 3x3 matrix operator (*=)
//NOTE: using column vectors, column-major (res = MAT * 3DVEC)
Vec3& Vec3::operator *=(const Mat3& mat)
{
	x = x * mat.elem[0] + y * mat.elem[1] + z * mat.elem[2];
	y = x * mat.elem[3] + y * mat.elem[4] + z * mat.elem[5];
	z = x * mat.elem[6] + y * mat.elem[7] + z * mat.elem[8];
	return *this;
}

//overload: vector negation (-vec)
Vec3 Vec3::operator -()
{
	return Vec3(-x, -y, -z);
}

//vector length
float Vec3::Length() const
{
	float len_sqr = this->x * this->x +
				    this->y * this->y +
				    this->z * this->z;
	return sqrtf(len_sqr);
}

//normalize vector
Vec3& Vec3::Normalize()
{
	float len = this->Length();
	x /= len;
	y /= len;
	z /= len;

	return *this;
}

//get normalized vector
Vec3 Vec3::GetNormalizedVec() const
{
	Vec3 norm_vec = *this;
	norm_vec.Normalize();
	return norm_vec;
}

//dot product
float Vec3::Dot(const Vec3& vec) const
{
	return this->x * vec.x +
		   this->y * vec.y +
		   this->z * vec.z;
}

//cross product
Vec3 Vec3::Cross(const Vec3& vec) const
{
	return Vec3(this->y * vec.z - this->z * vec.y,
				this->z * vec.x - this->x * vec.z,
				this->x * vec.y - this->y * vec.x);
}