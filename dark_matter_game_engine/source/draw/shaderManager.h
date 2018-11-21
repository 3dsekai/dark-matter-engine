//*************************************************************************
// DarkMatter OpenGL 3D Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: ShaderManager
// Source File: [shaderManager.h]
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
#ifndef _SHADER_MANAGER_H_
#define _SHADER_MANAGER_H_

//*************************************************************************
// Includes
//*************************************************************************
#include <map>
#include <GL/glew.h>

class Shader;

//*************************************************************************
// Shader Manager Class
//*************************************************************************
class ShaderManager
{
public:
	static ShaderManager* GetInstance();
	static void DestroyInstance();

	void LoadShader(const char* name, const GLchar* vert_file, const GLchar* frag_file, const GLchar* geom_file = nullptr);
	void UseShader(const char* name);
	void DeleteShader(const char* name);
	Shader* GetShader(const char* name);

private:
//	Shader loadShaderFromFile(const GLchar* vert_file, const GLchar* frag_file, const GLchar* geom_file = nullptr);
	static void ClearAllShaders();

private:
	ShaderManager();
	~ShaderManager();

	ShaderManager(const ShaderManager &obj);


private:
	static ShaderManager* _instance;
	static std::map<const char*, Shader*> _shaders;
};

#endif

