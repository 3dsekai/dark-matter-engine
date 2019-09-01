//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: TextureManager
// Source File: [textureManager.cpp]
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
// Includes
//*************************************************************************
#include "textureManager.h"
#include "../resource/textureResourceManager.h"

//*************************************************************************
// static member definition
//*************************************************************************
TextureManager* TextureManager::_instance = nullptr;
std::map<const char*, GLuint> TextureManager::_textures;

//*************************************************************************
// Class: TextureManager
// Function Name: GetInstance
// Explanation: Get the instance to this static singleton class
// Argument{s}:
// Other: -
//*************************************************************************
TextureManager* TextureManager::GetInstance()
{
	if(_instance == nullptr)
	{
		_instance = new TextureManager;
	}
	return _instance;
}

//*************************************************************************
// Class: TextureManager
// Function Name: GetInstance
// Explanation: Destroy the instance to this static singleton class
// Argument{s}:
// Other: -
//*************************************************************************
void TextureManager::DestroyInstance()
{
	//release all texture resources
	ClearAllTextures();

	//release the singleton instance
	delete _instance;
	_instance = nullptr;
}

//*************************************************************************
// Class: TextureManager
// Function Name: LoadAllTextures
// Explanation: Load all textures
// Argument{s}:
// Other: -
//*************************************************************************
void TextureManager::LoadAllTextures()
{
	LoadTexture(BOX_TEXTURE);
	LoadTexture(BOX2_TEXTURE);
	LoadTexture(BOX2_SPEC_TEX);
	LoadTexture(BLACK_TEXTURE);
}

//*************************************************************************
// Class: TextureManager
// Function Name: LoadTexture
// Explanation: Load a texture
// // Argument{s}:
// const char* name: the name of the texture
// Other: -
//*************************************************************************
void TextureManager::LoadTexture(const char* name)
{
	if (_textures.find(name) == _textures.end())
	{
		GLuint texId;
		//load texture
		std::string dir = "resources/img/" + std::string(name);
		TextureResourceManager::stbImgData texData;
		TextureResourceManager::LoadTexture(dir.c_str(), &texData);

		if (texData.imgData != nullptr)
		{
			GLenum format;
			if (texData.n == 1) format = GL_RED;
			else if (texData.n == 2) format = GL_RG;
			else if (texData.n == 3) format = GL_RGB;
			else if (texData.n == 4) format = GL_RGBA;

			glGenTextures(1, &texId); //generate texture name
			glBindTexture(GL_TEXTURE_2D, texId); //bind the texture to the texture target

												 // set the texture wrapping parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			// set texture filtering parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			//generate texture image on currently bound texture object
			glTexImage2D(GL_TEXTURE_2D,
				0,
				format,
				texData.w,
				texData.h,
				0,
				format,
				GL_UNSIGNED_BYTE,
				texData.imgData);
			//generate mipmaps for currently bound texture object
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		//unload texture
		TextureResourceManager::UnloadTexture(&texData);

		//assign the texture id
		_textures[name] = texId;
	}
}

//*************************************************************************
// Class: TextureManager
// Function Name: DeleteTexture
// Explanation: delete specified texture
// Argument{s}:
// const char* name: name of the texture to delete
// Other: -
//*************************************************************************
void TextureManager::DeleteTexture(const char* name)
{
	if(_textures.find(name) != _textures.end())
	{
		_textures.erase(name);
	}
}

//*************************************************************************
// Class: TextureManager
// Function Name: GetTextureId
// Explanation: Get a specified texture id
// Argument{s}:
// const char* name: name of the texture to retrieve
// Other: -
//*************************************************************************
GLuint TextureManager::GetTextureId(const char* name)
{
	GLuint id = 0;
	if(_textures.find(name) != _textures.end())
	{
		id = _textures[name];
	}
	return id;
}

//*************************************************************************
// Class: TextureManager
// Function Name: ClearAllTextures
// Explanation: Clear all textures
// Argument{s}:
// Other: -
//*************************************************************************
void TextureManager::ClearAllTextures()
{
	//delete all textures
	_textures.clear();
}
