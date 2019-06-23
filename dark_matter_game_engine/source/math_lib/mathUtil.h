//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: -
// Source File: [mathUtil.h]
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
#ifndef _MATHUTIL_H_
#define _MATHUTIL_H_

class Mat4;
//*************************************************************************
// Macro Definitions
//*************************************************************************
#define PI (3.14159265359f) //the value of pi
#define MIN(X, Y) ((X < Y) ? (X) : (Y)) //get smaller value
#define MAX(X, Y) ((X > Y) ? (X) : (Y)) //get larger value

//*************************************************************************
// Math Utility Functions
//*************************************************************************
namespace MathUtil
{
	//*************************************************************************
	// Definitions
	//*************************************************************************
	float Clamp(float val, float upper, float lower);
	float Deg2Rad(float deg);
	float Rad2Deg(float rad);
	float Det2x2(float a, float b, float c, float d);
	void Adjoint(const Mat4& m, float* adj);
	bool Inverse(Mat4& m, float* inv);
//	float Det3x3(float a1, float a2, float a3, float b1, float b2, float b3, float c1, float c2, float c3);
//	float Det4x4(float* m);
}
#endif
