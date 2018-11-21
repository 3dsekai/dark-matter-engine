//*************************************************************************
// DarkMatter OpenGL 3D Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: GameObjectBase
// Source File: [gameObjBase.h]
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
#ifndef _GAME_OBJ_BASE_H_
#define _GAME_OBJ_BASE_H_

//*************************************************************************
// Includes
//*************************************************************************
#include "../input/mouse.h"
#include "../input/keyboard.h"
#include "../camera/camera.h"

//*************************************************************************
// Class
//*************************************************************************
class GameObjBase
{
public:
	//constructor
	GameObjBase() { _is_kill = false; };
	//destructor
	virtual ~GameObjBase() {_is_kill = true; };

	//initialize game object
	virtual void Init() = 0;
	//update game object
	virtual void Update(float time, const Mouse& mouse, const Keyboard& keyboard) = 0;
	//draw game object
	virtual void Draw(Camera& cam) = 0;
	//delete game object
	virtual void Release() = 0;

	//is the object ready for deletion?
	bool IsKill() const { return _is_kill; };

protected:
	bool _is_kill; //object is ready for deletion check
};

#endif
