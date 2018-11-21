//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: Vec3
// Source File: [vec3.h]
//
// License:
// Copyright(C) <2018>  <Christopher Tall>
//
// This is software is copyrighted.
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
#ifndef _VEC3_H_
#define _VEC3_H_
//*************************************************************************
// Includes
//*************************************************************************
#include "mathUtil.h"

class Mat3;

//*************************************************************************
// Class
//*************************************************************************
class Vec3
{
public:

	//constructors
	Vec3();
	Vec3(float X, float Y, float Z);

	//operator overloads
	Vec3 operator +(const Vec3& vec) const;
	Vec3 operator -(const Vec3& vec) const;
	Vec3 operator *(const Vec3& vec) const;
	Vec3 operator /(const Vec3& vec) const;
	Vec3 operator +(float scalar) const;
	Vec3 operator -(float scalar) const;
	Vec3 operator *(float scalar) const;
	Vec3 operator /(float scalar) const;
	Vec3 operator *(const Mat3& mat) const;
	Vec3& operator =(const Vec3& vec);
	bool operator ==(const Vec3& vec) const;
	bool operator !=(const Vec3& vec) const;
	Vec3& operator +=(const Vec3& vec);
	Vec3& operator -=(const Vec3& vec);
	Vec3& operator *=(const Vec3& vec);
	Vec3& operator /=(const Vec3& vec);
	Vec3& operator *=(const Mat3& mat);
	Vec3 operator -();

	//general purpose functions
	float Length() const;
	Vec3& Normalize();
	Vec3 GetNormalizedVec() const;
	float Dot(const Vec3& vec) const;
	Vec3 Cross(const Vec3& vec) const;

	//convert degrees to radians (for Vec3)
	static Vec3 Deg2RadVec3(const Vec3& v)
	{
		return Vec3(v.x * (PI / 180.0f),
					v.y * (PI / 180.0f),
					v.z * (PI / 180.0f));
	};
	//convert radians to degrees (for Vec3)
	static Vec3 Rad2DegVec3(const Vec3& v)
	{
		return (Vec3(v.x * (180.0f / PI),
					 v.y * (180.0f / PI),
					 v.z * (180.0f / PI)));
	};

public:
	float x;
	float y;
	float z;
};

#endif
