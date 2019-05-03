//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: Quat
// Source File: [quat.h]
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
#ifndef _QUAT_H_
#define _QUAT_H_
//*************************************************************************
// Includes
//*************************************************************************
class Mat3;
class Mat4;
class Vec3;

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
	static Quat Identity();
	//Calculate lerp
	static Quat CalcLerp(float t, const Quat& Q0, const Quat& Q1);
	//Calculate slerp
	static Quat CalcSlerp(float t, const Quat& Q0, const Quat& Q1);
	//rotation matrix to quaternion
	static Quat Mat2Quat(const Mat4& m);
	//quaternion to rotation matrix
	static Mat3 Quat2Mat(const Quat& q);
	//euler angle (radians) to quaternion
	static Quat Euler2Quat(const Vec3& v);
	//quaternion to euler angle
	static Vec3 Quat2Euler(const Quat& q);
	//rotate quaternion by a 3d vector
	static Quat Rotation(const float rad, const Vec3& uvec);
	//get quaternion rotated around X axis by {rad} degrees
	static Quat RotationXAxis(const float rad);
	//get quaternion rotated around Y axis by {rad} degrees
	static Quat RotationYAxis(const float rad);
	//get quaternion rotated around Z axis by {rad} degrees
	static Quat RotationZAxis(const float rad);

public:
	//quaternion geometry. (angle of displacement, axis-angle vector [w, (x,y,z)])
	float w; //angle of displacement: cos(theta/2)
	float x; // x-axis of rotation: sin(theta/2)nx
	float y; // y-axis of rotation: sin(theta/2)ny
	float z; // z-axis of rotation: sin(theta/2)nz
};
#endif
