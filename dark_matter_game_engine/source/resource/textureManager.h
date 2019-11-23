//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: TextureManager
// Source File: [textureManager.h]
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
#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_

//*************************************************************************
// Includes
//*************************************************************************
#include <map>
#include <GL/glew.h>
#include "../define/texture_define.h"

//*************************************************************************
// Texture Manager Class
//*************************************************************************
class TextureManager
{
public:
	static TextureManager* GetInstance();
	static void DestroyInstance();

	void LoadAllTextures();
	void LoadTexture(const char* path);
	void DeleteTexture(const char* path);
	GLuint GetTextureId(const char* path);

private:
	static void ClearAllTextures();

private:
	TextureManager() {};
	~TextureManager() {};

	TextureManager(const TextureManager &obj) {};


private:
	static TextureManager* _instance;
	static std::map<const char*, GLuint> _textures;
};

#endif

