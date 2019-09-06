//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: TextureResourceManager
// Source File: [textureResourceManager.h]
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
#ifndef _TEXTURE_RESOURCE_MANAGER_H_
#define _TEXTURE_RESOURCE_MANAGER_H_

//*************************************************************************
// Class
//*************************************************************************
class TextureResourceManager
{
public:
	//stb_image library, texture load data
	//https://github.com/nothings/stb/blob/master/stb_image.h
	struct stbImgData
	{
		int w; //outputs image width in pixels
		int h; //outputs image height in pixels
		int n; //outputs # of image components in image file
		unsigned char* imgData; //output image data
	};

public:
	static void LoadTexture(const char* textureName, stbImgData* textureData);
	static void InitTexture(const stbImgData& textureData, GLuint& texId);
	static void UnloadTexture(stbImgData* textureData);
};

#endif
