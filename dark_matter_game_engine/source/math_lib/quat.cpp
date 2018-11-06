//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Class Name: Quat
// Source File: [quat.cpp]
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
//
//*************************************************************************
// Includes
//*************************************************************************
#include "quat.h"

//*************************************************************************
// Functions
//*************************************************************************

//constructors
Quat::Quat() :
	x(0.0f),
	y(0.0f),
	z(0.0f),
	w(1.0f)
{}

Quat::Quat(float X, float Y, float Z, float W) :
	x(X),
	y(Y),
	z(Z),
	w(W)
{}

//overload: addition by quaternion operator (+)
Quat Quat::operator +(const Quat& q) const
{
	//(w1,v1) + (w2,v2) = (w1+w2,v1+v2)
	return Quat((this->x + q.x),
				(this->y + q.y),
				(this->z + q.z),
				(this->w + q.w));
}
//overload: subtraction by quaternion operator (-)
Quat Quat::operator -(const Quat& q) const
{
	//(w1,v1) - (w2,v2) = (w1-w2,v1-v2)
	return Quat((this->x - q.x),
				(this->y - q.y),
				(this->z - q.z),
				(this->w - q.w));
}
//overload: multiplication by scalar operator (*)
Quat Quat::operator *(float k) const
{
	//quaternion/scalar product: [kw kv]
	return Quat((k * this->x),
				(k * this->y),
				(k * this->z),
				(k * this->w));
}
//overload: multiplication by quaternion operator (*)
Quat Quat::operator *(const Quat& q) const
{
	//quaternion product: [w1 v1][w2 v2] = [w1w2 - v1 ? v2   w1v2 + w2v1 + v1 ? v2]
	return Quat((this->w * q.x) + (this->x * q.w) + (this->y * q.z) - (this->z * q.y),
				(this->w * q.y) + (this->y * q.w) + (this->z * q.x) - (this->x * q.z),
				(this->w * q.z) + (this->z * q.w) + (this->x * q.y) - (this->y * q.x),
				(this->w * q.w) - (this->x * q.x) - (this->y * q.y) - (this->z * q.z));
}
//overload: quaternion negation operator (-)
Quat Quat::operator -() const
{
	return Quat(-this->x, -this->y, -this->z, -this->w);
}
//overload: equals operator
Quat& Quat::operator =(const Quat& q)
{
	this->w = q.w;
	this->x = q.x;
	this->y = q.y;
	this->z = q.z;

	return *this;
}
//overload: addition/assignment by quaternion operator (+=)
Quat& Quat::operator +=(const Quat& q)
{
	*this = *this + q;
	return *this;
}
//overload: subtraction/assignment by quaternion operator (-=)
Quat& Quat::operator -=(const Quat& q)
{
	*this = *this - q;
	return *this;
}
//overload: multiplication/assignment by scalar operator (*=)
Quat& Quat::operator *=(float k)
{
	*this = *this * k;
	return *this;
}
//overload: multiplication/assignment by quaternion operator (*=)
Quat& Quat::operator *=(const Quat& q)
{
	*this = *this * q;
	return *this;
}
//get the normalized quaternion
Quat Quat::GetNormalizedQuat() const
{
	Quat norm = *this;
	norm.Normalize();
	return norm;
}
//normalize quaternion
Quat& Quat::Normalize()
{
	float n = sqrtf((x * x) + (y * y) + (z * z) + (w * w));
	float invN = 1.0f / n;
	x *= invN;
	y *= invN;
	z *= invN;
	w *= invN;

	return *this;
}
//dot product
float Quat::Dot(const Quat& q) const
{
	return this->w * q.w +
		   this->x * q.x +
		   this->y * q.y +
		   this->z * q.z;
}
//set identity quaternion
Quat& Quat::SetIdentity()
{
	*this = Identity();
	return *this;
}
//magnitude of the quaternion
float Quat::GetMagnitude()
{
	//quaternion magnitude: sqrt(w^2 + x^2 + y^2 + z^2)
	//note: rotation quaternions have unit magnitude (1)
	return sqrtf((x * x) + (y * y) + (z * z) + (w * w));
}
//inverse of the quaternion
Quat Quat::GetInverse()
{
	//quaternion inverse: conjugate of q / magnitude of q
	//note: for rotation quaternions (which are unit quaternions),
	//inverse is equivalent to the conjugate.
	Quat inverse = Quat(0.0f, 0.0f, 0.0f, 0.0f);
	float mag = this->GetMagnitude();
	if (mag > 0.0f)
	{
		float div = 1.0f / mag;
		inverse = Quat(-(this->x*div), -(this->y*div), -(this->z*div), this->w*div);

	}
	return inverse;
}
//get the conjugate of the quaternion
Quat Quat::GetConjugate()
{
	return Quat(-(this->x), -(this->y), -(this->z), this->w);
}
