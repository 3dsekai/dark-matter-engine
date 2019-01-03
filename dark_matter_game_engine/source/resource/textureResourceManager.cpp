//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: TextureResourceManager
// Source File: [textureResourceManager.cpp]
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

//*************************************************************************
// Include
//*************************************************************************
#include <iostream>
#include "textureResourceManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../third_party_lib/stb_image.h"

//*************************************************************************
// Class: TextureResourceManager
// Function Name: LoadTexture
// Argument{s}:
// const char* textureName: name of the texture to load
// stbImgData* textureData: the container for the texture data
// Explanation: load the specified texture
//*************************************************************************
void TextureResourceManager::LoadTexture(const char* textureName, stbImgData* textureData)
{
	//flip texture's y-axis
	stbi_set_flip_vertically_on_load(true);

	//load image data
	textureData->imgData = stbi_load(textureName, &textureData->w, &textureData->h, &textureData->n, 0);
	if(textureData->imgData == nullptr)
	{
		std::cout << "Texture load Failure" << std::endl;
	}
}

//*************************************************************************
// Class: TextureResourceManager
// Function Name: UnloadTexture
// Argument{s}:
// stbImgData* textureData: the container for the texture data
// Explanation: unload the specified texture
//*************************************************************************
void TextureResourceManager::UnloadTexture(stbImgData* textureData)
{
	stbi_image_free(textureData->imgData);
}
