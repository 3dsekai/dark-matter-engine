//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: Mat3
// Source File: [mat3.h]
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
#ifndef _MAT3_H_
#define _MAT3_H_

//*************************************************************************
// macros 
//*************************************************************************
#define MAT3_SIZE (3)
#define MAT3_ELEM_NUM (9)

//*************************************************************************
// Class
//*************************************************************************
class Mat3
{
public:

	//default constructors
	Mat3() = default;
	~Mat3() = default;

	//operator overloads
	Mat3& operator =(const Mat3& mat);
	Mat3 operator *(float k) const;
	Mat3& operator *=(float k);
	Mat3 operator *(const Mat3& mat) const;
	Mat3& operator *=(const Mat3& mat);

	//general purpose functions
	Mat3& SetIdentity();
	Mat3& Transpose();
	float GetDeterminant();
	Mat3 GetInverse();

	//identity matrix
	static Mat3 Identity()
	{
		return
		{
			1.0f, 0.0f, 0.0f, 
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 
		};
	};

public:
	float elem[MAT3_ELEM_NUM];
};
#endif
