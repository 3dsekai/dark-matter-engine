//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Class Name: Vec2
// Source File: [vec2.h]
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
#ifndef _VEC2_H_
#define _VEC2_H_
//*************************************************************************
// Includes
//*************************************************************************
#include <math.h>

//*************************************************************************
// Class
//*************************************************************************
class Vec2
{
public:

	//constructors
	Vec2() :
		x(0.0f),
		y(0.0f)
	{};

	Vec2(float X, float Y) :
		x(X),
		y(Y)
	{};

	//overload: addition to vec operator (+)
	Vec2 operator +(Vec2 vec) const
	{
		return Vec2(this->x + vec.x,
					this->y + vec.y);
	};
	//overload: subtraction from vec operator (-)
	Vec2 operator -(Vec2 vec) const
	{
		return Vec2(this->x - vec.x, 
					this->y - vec.y);
	};
	//overload: multiplication by vec operator (*)
	Vec2 operator *(Vec2 vec) const
	{
		return Vec2(this->x * vec.x,
					this->y * vec.y);
	};
	//overload: division by vec operator (/)
	Vec2 operator /(Vec2 vec) const
	{
		return Vec2(this->x / vec.x,
					this->y / vec.y);
	};
	//overload: multiplication by scalar operator (*)
	Vec2 operator *(float scalar) const
	{
		return Vec2(this->x * scalar,
					this->y * scalar);
	};
	//overload: division by scalar operator (/)
	Vec2 operator /(float scalar) const
	{
		return Vec2(this->x / scalar,
					this->y / scalar);
	};
	//overload: modulus operator (%)
	//overload: assignment operator (=)
	Vec2& operator =(Vec2 vec)
	{
		x = vec.x;
		y = vec.y;
		return *this;
	};
	//overload: equality for vectors operator (==)
	//NOTE: comparing floats is bad. Probably shouldn't use this.
	bool operator ==(Vec2 vec) const
	{
		return (this->x == vec.x &&
				this->y == vec.y);
	};
	//overload: inequality for vectors operator (!=)
	//NOTE: comparing floats is bad. Probably shouldn't use this.
	bool operator !=(Vec2 vec) const
	{
		return (this->x != vec.x ||
				this->y != vec.y);
	};
	//overload: addition/assignment by vec operator (+=)
	Vec2& operator +=(Vec2 vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	};
	//overload: subtraction/assignment by vec operator (-=)
	Vec2& operator -=(Vec2 vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	};
	//overload: multiplication/assignment by vec operator (*=)
	Vec2& operator *=(Vec2 vec)
	{
		x *= vec.x;
		y *= vec.y;
		return *this;
	};
	//overload: division/assignment by vec operator (/=)
	Vec2& operator /=(Vec2 vec)
	{
		x /= vec.x;
		y /= vec.y;
		return *this;
	};
	//overload: vector negation (-vec)
	Vec2 operator -()
	{
		return Vec2(-x, -y);
	};

	//vector length
	float Length() const
	{
		float len_sqr = this->x * this->x +
						this->y * this->y;
		return sqrtf(len_sqr);
	};

	//normalize vector
	Vec2& Normalize()
	{
		float len = this->Length();
		x /= len;
		y /= len;

		return *this;
	};

	//get normalized vector
	Vec2 GetNormalizedVec() const
	{
		Vec2 norm_vec = *this;
		norm_vec.Normalize();
		return norm_vec;
	};

	//dot product
	float Dot(Vec2 vec) const
	{
		return this->x * vec.x +
			   this->y * vec.y;
	};

public:
	float x;
	float y;
};
#endif
