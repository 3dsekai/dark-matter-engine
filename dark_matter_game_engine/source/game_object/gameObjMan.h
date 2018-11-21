//*************************************************************************
// DarkMatter OpenGL 3D Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: GameObjManager
// Source File: [gameObjMan.h]
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
#ifndef _GAME_OBJ_MAN_H_
#define _GAME_OBJ_MAN_H_

//*************************************************************************
// Includes
//*************************************************************************
#include <vector>

class GameObjBase;
class Mouse;
class Keyboard;
class Camera;

//*************************************************************************
// Class
//*************************************************************************
class GameObjManager
{
public:
	GameObjManager();
	~GameObjManager();

private:

	void DestroyAllObjects();
public:
	void Init();
	void Update(float time, const Mouse& mouse, const Keyboard& keyboard);
	void Draw(Camera& cam);
	void AddNewGameObject(GameObjBase* obj);

private:
	std::vector<GameObjBase*> _obj_list;
};


#endif
