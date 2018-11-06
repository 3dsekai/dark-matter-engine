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
#include "mat3.h"
#include "mat4.h"

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
	Quat();
	Quat(float X, float Y, float Z, float W);

	//operator overloads
	Quat operator +(const Quat& q) const;
	Quat operator -(const Quat& q) const;
	Quat operator *(float k) const;
	Quat operator *(const Quat& q) const;
	Quat operator -() const;
	Quat& operator =(const Quat& q);
	Quat& operator +=(const Quat& q);
	Quat& operator -=(const Quat& q);
	Quat& operator *=(float k);
	Quat& operator *=(const Quat& q);

	//general purpose functions
	Quat GetNormalizedQuat() const;
	Quat& Normalize();
	float Dot(const Quat& q) const;
	Quat& SetIdentity();
	float GetMagnitude();
	Quat GetInverse();
	Quat GetConjugate();

	//identity quaternion
	static Quat Identity()
	{
		//the identity quaternion: [1, 0]
		return Quat(0.0f, 0.0f, 0.0f, 1.0f);
	};
	//Calculate lerp
	static Quat CalcLerp(float t, const Quat& Q0, const Quat& Q1)
	{
		Quat delta = Q1 - Q0;
		return (Q0 + delta*t);
	}
	//Calculate slerp
	static Quat CalcSlerp(float t, const Quat& Q0, const Quat& Q1)
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
	static Quat Mat2Quat(const Mat4& m)
	{
		// matrix to quaternion conversion as defined in
		//Dunn/Parberry's "3D Math Primer for Graphics and Game Development"
		//p. 284 - 287

		Quat m2q;
		float absVal[4];
		float m11 = m.elem[0];
		float m12 = m.elem[1];
		float m13 = m.elem[2];
		float m21 = m.elem[4];
		float m22 = m.elem[5];
		float m23 = m.elem[6];
		float m31 = m.elem[8];
		float m32 = m.elem[9];
		float m33 = m.elem[10];

		//determine which component has the largest absolute value
		absVal[0] = m11 + m22 + m33; //W component
		absVal[1] = m11 - m22 - m33;
		absVal[2] = m22 - m11 - m33;
		absVal[3] = m33 - m11 - m22;

		int idx = 0; //index of component with the largest value
		float bigVal = absVal[0]; //holds the largest value
		for(int i = 1; i < 4; i++)
		{
			if(absVal[i] > bigVal)
			{
				bigVal = absVal[i];
				idx = i;
			}
		}

		//perform square root and division to extract the
		//quaternion value from the matrix
		bigVal = sqrtf(bigVal + 1.0f) * 0.5f;
		float div = 0.25f / bigVal;

		//apply the table to calculate the quaternion
		switch(idx)
		{
		case 0:		//W component is largest
			m2q.w = bigVal;
			m2q.x = (m23 - m32) * div;
			m2q.y = (m31 - m13) * div;
			m2q.z = (m12 - m21) * div;
			break;
		case 1:		//X component is largest
			m2q.w = (m23 - m32) * div;
			m2q.x = bigVal;
			m2q.y = (m12 + m21) * div;
			m2q.z = (m31 + m13) * div;
			break;
		case 2:		//Y component is largest
			m2q.w = (m31 - m13) * div;
			m2q.x = (m12 + m21) * div;
			m2q.y = bigVal;
			m2q.z = (m23 + m32) * div;
			break;
		case 3:		//Z component is largest
			m2q.w = (m12 - m21) * div;
			m2q.x = (m31 + m13) * div;
			m2q.y = (m23 + m32) * div;
			m2q.z = bigVal;
			break;
		}
		return m2q;
	};
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
	//euler angle (radians) to quaternion
	static Quat Euler2Quat(const Vec3& v)
	{
		//euler angle to quaternion as defined in
		//Dunn/Parberry's "3D Math Primer for Graphics and Game Development"
		//p. 287 - 288

		float p = v.x/2;		//pitch
		float y = v.y/2;		//yaw
		float r = v.z/2;		//roll
		float cosP = cosf(p);	//cosine pitch/2
		float sinP = sinf(p);	//sine pitch/2
		float cosY = cosf(y);	//cosine yaw/2
		float sinY = sinf(y);	//sine yaw/2
		float cosR = cosf(r);	//cosine roll/2
		float sinR = sinf(r);	//sine roll/2

		//convert the euler angle to a quaternion
		Quat e2q;
		e2q.w = (cosP*cosY*cosR)+(sinP*sinY*sinR);
		e2q.x = (sinP*cosY*cosR)-(cosP*sinY*sinR);
		e2q.y = (cosP*sinY*cosR)+(sinP*cosY*sinR);
		e2q.z = (cosP*cosY*sinR)-(sinP*sinY*cosR);

		return e2q;
	};
	//quaternion to euler angle
	static Vec3 Quat2Euler(const Quat& q)
	{
		//euler angle to quaternion as defined in
		//Dunn/Parberry's "3D Math Primer for Graphics and Game Development"
		//p. 288 - 290

		float x = q.x;
		float y = q.y;
		float z = q.z;
		float w = q.w;

		Vec3 q2e;

		//get sin(pitch)
		float sinP = -2.0f * ((y*z) - (w*x));

		//check for gimbal lock
		if(fabs(sinP) > 0.9999f)
		{
			//looking straight up or down (x-axis)
			//pi/2 * sin(pitch)
			q2e.x = (PI*0.5f) * sinP;

			//calculate yaw (y-axis)
			q2e.y = atan2f((-x*z) + (w*y), 0.5f - (y*y) - (z*z));

			//set roll (z-axis) to 0
			q2e.z = 0.0f;
		}
		else
		{
			//calculate angles
			q2e.x = asinf(sinP);
			q2e.y = atan2f((x*z) + (w*y), 0.5f - (x*x) - (y*y));
			q2e.z = atan2f((x*y) + (w*z), 0.5f - (x*x) - (z*z));
		}

		return q2e;
	};
	//rotate quaternion by a 3d vector
	static Quat Rotation(const float rad, const Vec3& uvec)
	{
		float ang = rad * 0.5f;
		float sin = sinf(ang);
		float cos = cosf(ang);
		Vec3 v = uvec * sin;

		return (Quat(v.x, v.y, v.z, cos));
	}
	//get quaternion rotated around X axis by {rad} degrees
	static Quat RotationXAxis(const float rad)
	{
		float ang = rad * 0.5f;
		float sin = sinf(ang);
		float cos = cosf(ang);

		return (Quat(sin, 0.0f, 0.0f, cos));
	};
	//get quaternion rotated around Y axis by {rad} degrees
	static Quat RotationYAxis(const float rad)
	{
		float ang = rad * 0.5f;
		float sin = sinf(ang);
		float cos = cosf(ang);

		return (Quat(0.0f, sin, 0.0f, cos));
	};
	//get quaternion rotated around Z axis by {rad} degrees
	static Quat RotationZAxis(const float rad)
	{
		float ang = rad * 0.5f;
		float sin = sinf(ang);
		float cos = cosf(ang);

		return (Quat(0.0f, 0.0f, sin, cos));
	};

public:
	//quaternion geometry. (angle of displacement, axis-angle vector [w, (x,y,z)])
	float w; //angle of displacement: cos(theta/2)
	float x; // x-axis of rotation: sin(theta/2)nx
	float y; // y-axis of rotation: sin(theta/2)ny
	float z; // z-axis of rotation: sin(theta/2)nz
};
#endif
