//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: UBOManager
// Source File: [uboManager.h]
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
#ifndef _UBOMANAGER_H_
#define _UBOMANAGER_H_

#include "../math_lib/mat4.h"
#include "../math_lib/vec4.h"

//*************************************************************************
// macros
//*************************************************************************
/*

    size of the UBOParams struct

                          //base alignment    //aligned offset
    Mat4 projView;        16                  0    (column 0)
                          16                  16   (column 1)
                          16                  32   (column 2)
                          16                  48   (column 3)

    Vec4 ambientLight;    16                  64

              total size: 80


*/
//#define UBOPARAMS_SIZE (sizeof(Mat4)*sizeof(Vec4))
#define UBOPARAMS_SIZE (80)
//*************************************************************************
// Class
//*************************************************************************
class UBOManager
{
private:
//uniform buffer object parameters
struct UBOParams
{
	Mat4 projView;//world matrix store
	Vec4 ambientLight;//global ambient light color
};
//the size (base alignment) of various components
//according to the std140 layout specifications
enum BASE_ALIGNMENT
{
	BA_FLOAT = sizeof(float),
	BA_VEC3  = sizeof(float)*4,
	BA_VEC4  = sizeof(float)*4,
	BA_MAT3  = sizeof(float)*12,
	BA_MAT4  = sizeof(float)*16,
};
//the offset necessary to order components
//according to the std140 layout specifications
enum ALIGNED_OFFSET
{
	AO_NONE  = 0,
	AO_FLOAT = sizeof(float),
	AO_VEC3  = sizeof(float)*4,
	AO_VEC4  = sizeof(float)*4,
	AO_MAT3  = sizeof(float)*12,
	AO_MAT4  = sizeof(float)*16,
};

public:
	static void InitUniformBufferObject();
	static void UpdateUniformBufferObject();
	static void LinkShaderUBOBlockIndex(GLuint shaderId);

public:
	static UBOParams _uboParams;

private:
	static GLuint _uboBufferId;
};

#endif
