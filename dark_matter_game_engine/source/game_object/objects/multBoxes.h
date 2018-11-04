//*************************************************************************
// DarkMatter OpenGL 3D Engine Framework
// Class Name: MultBoxes
// Source File: [multBoxes.h]
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

//*************************************************************************
// Includes
//*************************************************************************
#include <vector>
#include "../gameObjBase.h"

class Cube;
//*************************************************************************
// MultBoxes Class
//*************************************************************************
class MultBoxes : public GameObjBase
{
public:
	MultBoxes();
	~MultBoxes();

	void Init() override;
	void Update(float time, const Mouse& mouse, const Keyboard& keyboard) override;
	void Draw(Camera& cam) override;
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
	std::vector<Cube*> _cubes;
	Vec3 _pos;
	Vec3 _rot;
};
