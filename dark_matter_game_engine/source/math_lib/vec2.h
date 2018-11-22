//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: Vec2
// Source File: [vec2.h]
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
#ifndef _VEC2_H_
#define _VEC2_H_

//*************************************************************************
// Class
//*************************************************************************
class Vec2
{
public:

	//constructors
	Vec2();
	Vec2(float X, float Y);

	//operator overloads
	Vec2 operator +(Vec2 vec) const;
	Vec2 operator -(Vec2 vec) const;
	Vec2 operator *(Vec2 vec) const;
	Vec2 operator /(Vec2 vec) const;
	Vec2 operator *(float scalar) const;
	Vec2 operator /(float scalar) const;
	Vec2& operator =(Vec2 vec);
	bool operator ==(Vec2 vec) const;
	bool operator !=(Vec2 vec) const;
	Vec2& operator +=(Vec2 vec);
	Vec2& operator -=(Vec2 vec);
	Vec2& operator *=(Vec2 vec);
	Vec2& operator /=(Vec2 vec);
	Vec2 operator -();

	//general purpose functions
	float Length() const;
	Vec2& Normalize();
	Vec2 GetNormalizedVec() const;
	float Dot(Vec2 vec) const;

public:
	float x;
	float y;
};
#endif
