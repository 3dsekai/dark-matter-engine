//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Class Name: Quat
// Source File: [quat.h]
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
#ifndef _QUAT_H_
#define _QUAT_H_
//*************************************************************************
// Includes
//*************************************************************************
#include "vec3.h"
#include "vec4.h"

//*************************************************************************
// macros
//*************************************************************************

//*************************************************************************
// Class
//On quaternion arithmetic:
//http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/notations/scalarAndVector/index.htm
//*************************************************************************
class Quat
{
public:
	//constructors
	Quat() :
		w(1.0f),
		x(0.0f),
		y(0.0f),
		z(0.0f)
	{};

	Quat(float X, float Y, float Z, float W) :
		w(W),
		x(X),
		y(Y),
		z(Z)
	{};

	//overload: addition by quaternion operator (+)
	Quat operator +(Quat q) const
	{
		//(w1,v1) + (w2,v2) = (w1+w2,v1+v2)
		return Quat((this->w + q.w),
					(this->x + q.x),
					(this->y + q.y),
					(this->z + q.z));
	};
	//overload: subtraction by quaternion operator (-)
	Quat operator -(Quat q) const
	{
		//(w1,v1) - (w2,v2) = (w1-w2,v1-v2)
		return Quat((this->w - q.w),
					(this->x - q.x),
					(this->y - q.y),
					(this->z - q.z));
	};
	//overload: multiplication by scalar operator (*)
	Quat operator *(float k) const
	{
		//quaternion/scalar product: [kw kv]
		return Quat((k * this->w),
					(k * this->x),
					(k * this->y),
					(k * this->z));
	};
	//overload: multiplication by quaternion operator (*)
	Quat operator *(Quat q) const
	{
		//quaternion product: [w1 v1][w2 v2] = [w1w2 - v1 ? v2   w1v2 + w2v1 + v1 ? v2]
		return Quat((this->w * q.w) - (this->x * q.x) - (this->y * q.y) - (this->z * q.z),
					(this->w * q.x) + (this->x * q.w) + (this->y * q.z) - (this->z * q.y),
					(this->w * q.y) + (this->y * q.w) + (this->z * q.x) - (this->x * q.z),
					(this->w * q.z) + (this->z * q.w) + (this->x * q.y) - (this->y * q.x));
	}
	//overload: equals operator
	Quat& operator =(Quat q)
	{
		*this = q;
		return *this;
	};
	//overload: addition/assignment by quaternion operator (+=)
	Quat& operator +=(Quat q)
	{
		*this = *this + q;
		return *this;
	};
	//overload: subtraction/assignment by quaternion operator (-=)
	Quat& operator -=(Quat q)
	{
		*this = *this - q;
		return *this;
	};
	//overload: multiplication/assignment by scalar operator (*=)
	Quat& operator *=(float k)
	{
		*this = *this * k;
		return *this;
	};
	//overload: multiplication/assignment by quaternion operator (*=)
	Quat& operator *=(Quat q)
	{
		*this = *this * q;
		return *this;
	};
	//get the normalized quaternion
	Quat GetNormalizedQuat() const
	{
		Quat norm = *this;
		norm.Normalize();
		return norm;
	};
	//normalize quaternion
	Quat& Normalize()
	{
		float n = sqrtf((x * x) + (y * y) + (z * z) + (w * w));
		x /= n;
		y /= n;
		z /= n;
		w /= n;

		return *this;
	};
	//dot product
	float Dot(Quat q) const
	{
		(this->w * q.w) +
		(this->x * q.x) +
		(this->y * q.y) +
		(this->z * q.z);
	};
	//identity quaternion
	static Quat Identity()
	{
		//the identity quaternion: [1, 0]
		return Quat(1.0f, 0.0f, 0.0f, 0.0f);
	};
	//set identity quaternion
	Quat& SetIdentity()
	{
		*this = Identity();
		return *this;
	};
	//magnitude of the quaternion
	float GetMagnitude()
	{
		//quaternion magnitude: sqrt(w^2 + x^2 + y^2 + z^2)
		//note: rotation quaternions have unit magnitude (1)
		return sqrtf((x * x) + (y * y) + (z * z) + (w * w));
	};
	//inverse of the quaternion
	Quat GetInverse()
	{
		//quaternion inverse: conjugate of q / magnitude of q
		//note: for rotation quaternions (which are unit quaternions),
		//inverse is equivalent to the conjugate.
		Quat inverse = Quat(0.0f, 0.0f, 0.0f, 0.0f);
		float mag = this->GetMagnitude();
		if (mag > 0.0f)
		{
			float div = 1.0f / mag;
			inverse = Quat(this->w*div, -(this->x*div), -(this->y*div), -(this->z*div));

		}
		return inverse;
	};
	//get the conjugate of the quaternion
	Quat GetConjugate()
	{
		return Quat(this->w, -(this->x), -(this->y), -(this->z));
	};
	//calculate exponentiation of a quaternion
	Quat CalcExp(float exp)
	{
	};
	//Calculate slerp
	Quat CalcSlerp()
	{
	};
	//generate rotation quaternion
	Quat Rotate(const Vec3 vec)
	{
	};
	//rotate around X axis by {deg} degrees
	Quat RotateXAxis(const float deg)
	{
	};
	//rotate around Y axis by {deg} degrees
	Quat RotateYAxis(const float deg)
	{
	};
	//rotate around Z axis by {deg} degrees
	Quat RotateZAxis(const float deg)
	{
	};

public:
	//quaternion geometry. (angle of displacement, axis-angle vector [w, (x,y,z)])
	float w; //angle of displacement: cos(theta/2)
	float x; // x-axis of rotation: sin(theta/2)nx
	float y; // y-axis of rotation: sin(theta/2)ny
	float z; // z-axis of rotation: sin(theta/2)nz
};
#endif
