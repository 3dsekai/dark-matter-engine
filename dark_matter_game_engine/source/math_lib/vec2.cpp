//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: Vec2
// Source File: [vec2.cpp]
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
#include "math.h"
#include "vec2.h"

//*************************************************************************
// Functions
//*************************************************************************

//constructors
Vec2::Vec2() :
	x(0.0f),
	y(0.0f)
{}

Vec2::Vec2(float X, float Y) :
	x(X),
	y(Y)
{}

//overload: addition to vec operator (+)
Vec2 Vec2::operator +(Vec2 vec) const
{
	return Vec2(this->x + vec.x,
				this->y + vec.y);
}

//overload: subtraction from vec operator (-)
Vec2 Vec2::operator -(Vec2 vec) const
{
	return Vec2(this->x - vec.x, 
				this->y - vec.y);
}

//overload: multiplication by vec operator (*)
Vec2 Vec2::operator *(Vec2 vec) const
{
	return Vec2(this->x * vec.x,
				this->y * vec.y);
}

//overload: division by vec operator (/)
Vec2 Vec2::operator /(Vec2 vec) const
{
	return Vec2(this->x / vec.x,
				this->y / vec.y);
}

//overload: multiplication by scalar operator (*)
Vec2 Vec2::operator *(float scalar) const
{
	return Vec2(this->x * scalar,
				this->y * scalar);
}

//overload: division by scalar operator (/)
Vec2 Vec2::operator /(float scalar) const
{
	return Vec2(this->x / scalar,
				this->y / scalar);
}

//overload: modulus operator (%)
//overload: assignment operator (=)
Vec2& Vec2::operator =(Vec2 vec)
{
	x = vec.x;
	y = vec.y;
	return *this;
}

//overload: equality for vectors operator (==)
//NOTE: comparing floats is bad. Probably shouldn't use this.
bool Vec2::operator ==(Vec2 vec) const
{
	return (this->x == vec.x &&
			this->y == vec.y);
}

//overload: inequality for vectors operator (!=)
//NOTE: comparing floats is bad. Probably shouldn't use this.
bool Vec2::operator !=(Vec2 vec) const
{
	return (this->x != vec.x ||
			this->y != vec.y);
}

//overload: addition/assignment by vec operator (+=)
Vec2& Vec2::operator +=(Vec2 vec)
{
	x += vec.x;
	y += vec.y;
	return *this;
}

//overload: subtraction/assignment by vec operator (-=)
Vec2& Vec2::operator -=(Vec2 vec)
{
	x -= vec.x;
	y -= vec.y;
	return *this;
}

//overload: multiplication/assignment by vec operator (*=)
Vec2& Vec2::operator *=(Vec2 vec)
{
	x *= vec.x;
	y *= vec.y;
	return *this;
}

//overload: division/assignment by vec operator (/=)
Vec2& Vec2::operator /=(Vec2 vec)
{
	x /= vec.x;
	y /= vec.y;
	return *this;
}

//overload: vector negation (-vec)
Vec2 Vec2::operator -()
{
	return Vec2(-x, -y);
}

//vector length
float Vec2::Length() const
{
	float len_sqr = this->x * this->x +
					this->y * this->y;
	return sqrtf(len_sqr);
}

//normalize vector
Vec2& Vec2::Normalize()
{
	float len = this->Length();
	float inv = 1.0f / len;
	x *= inv;
	y *= inv;

	return *this;
}

//get normalized vector
Vec2 Vec2::GetNormalizedVec() const
{
	Vec2 norm_vec = *this;
	norm_vec.Normalize();
	return norm_vec;
}

//dot product
float Vec2::Dot(Vec2 vec) const
{
	return this->x * vec.x +
		   this->y * vec.y;
}
