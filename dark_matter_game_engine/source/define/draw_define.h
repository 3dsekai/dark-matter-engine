//*************************************************************************
// DarkMatter OpenGL 3D Engine Framework
// Class Name: -
// Source File: [draw_define.h]
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
#ifndef _DRAW_DEFINE_H_
#define _DRAW_DEFINE_H_

//*************************************************************************
// vertex attribute types
//*************************************************************************
enum AttributeType
{
	POS_COORD_ATTRIB = 0,	//position coordinates
	TEX_COORD_ATTRIB,		//texture coordinates
	ATTRIB_NUM
};

//*************************************************************************
// vertex buffer object types
//*************************************************************************
enum BuffObjType
{
	POS_COORDS_BUFF_OBJ = 0,	//position coordinates buffer object
	TEX_COORDS_BUFF_OBJ,		//texture coordinates buffer object
	INDEX_BUFF_OBJ,				//index array buffer object
	BUFF_OBJ_NUM
};
#endif
