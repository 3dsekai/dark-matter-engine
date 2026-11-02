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
std::map<std::string, GLuint> TextureManager::_textures;

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
void TextureManager::LoadTexture(const char* path)
{
	if (_textures.find(path) == _textures.end())
	{
		GLuint texId;
		//load texture
		TextureResourceManager::stbImgData texData;
		TextureResourceManager::LoadTexture(path, &texData);

		//initialize texture
		TextureResourceManager::InitTexture(texData, texId);

		//unload texture
		TextureResourceManager::UnloadTexture(&texData);

		//assign the texture id
		_textures[path] = texId;
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
void TextureManager::DeleteTexture(const char* path)
{
	if(_textures.find(path) != _textures.end())
	{
		_textures.erase(path);
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
GLuint TextureManager::GetTextureId(const char* path)
{
	GLuint id = 0;
	if(_textures.find(path) != _textures.end())
	{
		id = _textures[path];
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
