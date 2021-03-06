//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: Floor
// Source File: [floor.h]
//
// License:
// Copyright(C) <2019>  <Christopher Tall>
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
#ifndef _FLOOR_H_
#define _FLOOR_H_

//*************************************************************************
// Includes
//*************************************************************************
#include <vector>
#include "../gameObjBase.h"
#include "../../math_lib/vec3.h"
class Plane;
//*************************************************************************
// Floor Class
//*************************************************************************
class Floor : public GameObjBase
{
public:
	Floor();
	~Floor();

	void Init() override;
	void Update(const Mouse& mouse, const Keyboard& keyboard, Camera* cam) override;
	void Draw() override;
	void Release() override;
	//set position
	void SetPosition(const Vec3& pos) 
	{
		_pos = pos;
	};
	//set rotation
	void SetRotation(const Vec3& rot)
	{
		_rot = rot;
	};

private:
	Plane* _plane;
	Vec3 _pos;
	Vec3 _rot;
};

#endif
