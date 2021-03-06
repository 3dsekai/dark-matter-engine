//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: ColoredCube
// Source File: [coloredCube.h]
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
#ifndef _COLOREDCUBE_H_
#define _COLOREDCUBE_H_

//*************************************************************************
// Includes
//*************************************************************************
#include <GL/glew.h>
#include "../../camera/camera.h"

class Mouse;
class Keyboard;
//*************************************************************************
// Macro Definitions
//*************************************************************************
#define VERTICES_NUM				(3)
#define VERTICES_ELEM_NUM			(24)

#define COL_VERTS_NUM				(3)
#define COL_VERTS_ELEM_NUM			(24)

#define POS_ATTRIB_ELEM_NUM			(3)
#define COLOR_ATTRIB_ELEM_NUM		(3)

#define VERTEX_STRIDE				(3)

#define INDICES_NUM					(36)

//*************************************************************************
// Shader Class
//*************************************************************************
class ColoredCube
{
private:
	enum BufferType
	{
		POS_VERT_BUFF_OBJ = 0,
		COLOR_VERT_BUFF_OBJ,
		INDEX_BUFF_OBJ,
		BUFF_OBJ_NUM
	};
public:
	ColoredCube();
	~ColoredCube();

	void Init();
	void Update(const Keyboard& keyboard, const Mouse& mouse);
	void Draw();
	void Delete();

private:
	GLuint _buff_obj[BUFF_OBJ_NUM];
	GLuint _VAO;
	Camera _cam;

	static const float _pos_verts[VERTICES_ELEM_NUM];
	static const float _col_verts[COL_VERTS_ELEM_NUM];
	static const unsigned int _indices[INDICES_NUM];
};

#endif
