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
//*************************************************************************
class Quat
{
public:
	Quat() = default;
	~Quat() = default;

	//overload: addition by scalar operator (+)
	Quat operator +(float k) const
	{
	};
	//overload: addition by quaternion operator (+)
	Quat operator +(Quat q) const
	{
	};
	//overload: subtraction by scalar operator (-)
	Quat operator -(float k) const
	{
	};
	//overload: subtraction by quaternion operator (-)
	Quat operator -(Quat q) const
	{
	};
	//overload: multiplication by scalar operator (*)
	Quat operator *(float k) const
	{
	};
	//overload: multiplication by quaternion operator (*)
	Quat operator *(Quat q) const
	{
	}
	//overload: equals operator
	Quat& operator =(Quat q)
	{
	};
	//overload: addition/assignment by scalar operator (+=)
	Quat& operator +=(float k)
	{
	};
	//overload: addition/assignment by quaternion operator (+=)
	Quat& operator +=(Quat q)
	{
	};
	//overload: subtraction/assignment by scalar operator (-=)
	Quat& operator -=(float k)
	{
	};
	//overload: subtraction/assignment by quaternion operator (-=)
	Quat& operator -=(Quat q)
	{
	};
	//overload: multiplication/assignment by scalar operator (*=)
	Quat& operator *=(float k)
	{
	};
	//overload: multiplication/assignment by quaternion operator (*=)
	Quat& operator *=(Quat q)
	{
	};
	//get the normalizeed quaternion
	Quat GetNormalizedQuat() const
	{
	};
	//normalize quaternion
	Quat& Normalize()
	{
	};
	//identity quaternion
	static Quat Identity()
	{
	};
	//set identity quaternion
	Quat& SetIdentity()
	{
	};
	//inverse of the quaternion, using classical adjoint method
	Quat GetInverse()
	{
	};
	//get the conjugate of the quaternion
	Quat GetConjugate()
	{
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
	Vec4 _q;
};
#endif
