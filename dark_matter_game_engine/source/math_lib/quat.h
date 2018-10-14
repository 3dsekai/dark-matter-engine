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
		x(0.0f),
		y(0.0f),
		z(0.0f),
		w(1.0f)
	{};

	Quat(float X, float Y, float Z, float W) :
		x(X),
		y(Y),
		z(Z),
		w(W)
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
		this->w = q.w;
		this->x = q.x;
		this->y = q.y;
		this->z = q.z;

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
		return this->w * q.w +
			   this->x * q.x +
			   this->y * q.y +
			   this->z * q.z;
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
	//Calculate slerp
	Quat CalcSlerp(float t, const Quat& Q0, const Quat& Q1)
	{
		Quat q0 = Q0;
		Quat q1 = Q1;
		//dot product of the two quaternions
		//to get the cosine of the angle
		float cosW = q0.Dot(q1);

		//if the dot product is negative,
		//negate one quaternion to get the shortest arc
		if(cosW < 0.0f)
		{
			q1.x = -q1.x;
			q1.y = -q1.y;
			q1.z = -q1.z;
			q1.w = -q1.w;
			cosW = -cosW;
		}

		//check if quaternions are very close together to prevent
		//divide-by-zero
		float k0, k1;	//constants for interpolation
		if(cosW > 0.9999f)
		{ //very close
			//use linear interpolation
			k0 = 1.0f - t;
			k1 = t;
		}
		else
		{ //not close
			//compute sign of the angle
			//trig identity: sin^2(omega) + cos^2(omega) = 1
			float sinW = sqrtf(1.0f - (cosW * cosW));

			//compute angle from sin and cosine
			float w = atan2f(sinW, cosW);

			//inverse of denominator (only have to divide once)
			float sinWInv = 1.0f / sinW;

			//compute interpolation parameters
			k0 = sinf((1.0f - t) * w) * sinWInv;
			k1 = sinf(t*w) * sinWInv;
		}

		//return interpolated quaternion
		return
		{
			Quat(q0.x*k0 + q1.x*k1,
				 q0.y*k0 + q1.y*k1,
				 q0.z*k0 + q1.z*k1,
				 q0.w*k0 + q1.w*k1)
		};
	};
	//rotation matrix to quaternion
	static Quat Mat2Quat(const Mat3& m)
	{
	}
	//quaternion to rotation matrix
	static Mat3 Quat2Mat(const Quat& q)
	{
		//quaternion to rotation matrix as defined in
		//Dunn/Parberry's "3D Math Primer for Graphics and Game Development"
		//page. 284
		Mat3 q2m;
		q2m.elem[0] = 1-(2*q.y*q.y)-(2*q.z*q.z);
		q2m.elem[1] =   (2*q.x*q.y)+(2*q.w*q.z);
		q2m.elem[2] =   (2*q.x*q.z)-(2*q.w*q.y);
		q2m.elem[3] =   (2*q.x*q.y)-(2*q.w*q.z);
		q2m.elem[4] = 1-(2*q.x*q.x)-(2*q.z*q.z);
		q2m.elem[5] =   (2*q.y*q.z)+(2*q.w*q.x);
		q2m.elem[6] =   (2*q.x*q.z)+(2*q.w*q.y);
		q2m.elem[7] =   (2*q.y*q.z)-(2*q.w*q.x);
		q2m.elem[8] = 1-(2*q.x*q.x)-(2*q.y*q.y);

		return q2m;
	};
	//euler angle (degrees) to quaternion
	static Quat Euler2Quat(const Vec3& v)
	{
		float p = MathUtil::Deg2Rad(v.x/2);		//pitch
		float y = MathUtil::Deg2Rad(v.y/2);		//yaw
		float r = MathUtil::Deg2Rad(v.z/2);		//roll
		float cosP = cosf(p);					//cosine pitch/2
		float sinP = sinf(p);					//sine pitch/2
		float cosY = cosf(y);					//cosine yaw/2
		float sinY = sinf(y);					//sine yaw/2
		float cosR = cosf(r);					//cosine roll/2
		float sinR = sinf(r);					//sine roll/2

		//convert the euler angle to a quaternion
		Quat e2q;
		e2q.w = (cosP*cosY*cosR)+(sinP*sinY*sinR);
		e2q.x = (sinP*cosY*cosR)-(cosP*sinY*sinR);
		e2q.y = (cosP*sinY*cosR)+(sinP*cosY*sinR);
		e2q.z = (cosP*cosY*sinR)-(sinP*sinY*cosR);

		return e2q;
	};
	//quaternion to euler angle
	static Vec3 QuatToEuler(const Quat& q)
	{
	};
	//rotate quaternion by a 3d vector
	Quat Rotate(const Vec3& vec)
	{
	};
	//get quaternion rotated around X axis by {deg} degrees
	Quat RotationXAxis(const float deg)
	{
	};
	//get quaternion rotated around Y axis by {deg} degrees
	Quat RotationYAxis(const float deg)
	{
	};
	//get quaternion rotated around Z axis by {deg} degrees
	Quat RotationZAxis(const float deg)
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
