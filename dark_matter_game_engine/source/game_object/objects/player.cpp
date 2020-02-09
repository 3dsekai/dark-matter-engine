//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: Player
// Source File: [player.cpp]
//
// License:
// Copyright(C) <2020>  <Christopher Tall>
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
#include "player.h"
#include "../../define/shader_define.h"
#include "../../define/light_define.h"
#include "../../meshes/cube.h"
#include "../../lighting/light.h"
#include "../../input/inputCodes.h"
//#include "../../define/texture_define.h"
//#include "../../math_lib/mat4.h"
//#include "../../math_lib/mathUtil.h"

//*************************************************************************
//macro defintions
//*************************************************************************
#define SPEED (0.05f) //camera speed

//*************************************************************************
//constructor
//*************************************************************************
Player::Player() :
	_target(0.0f, 0.0f, -1.0f)
{
}

//*************************************************************************
//destructor
//*************************************************************************
Player::~Player()
{
	delete _player;
	_player = nullptr;
}

//*************************************************************************
//initialize
//*************************************************************************
void Player::Init()
{
	//player init
	_player = new Cube(TEXTURE_MESH_SHADER_NAME);
	//light
	Vec4 col = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
	lightDef light;
	light.position = _pos;
	light.ambient = Vec3(col.x, col.y, col.z) * 0.1f;
	light.diffuse = Vec3(col.x, col.y, col.z) * 0.5f;
	light.specular = Vec3(1.0f, 1.0f, 1.0f);
	_light = new Light(TEXTURE_MESH_SHADER_NAME, light);
}

//*************************************************************************
//update
//*************************************************************************
void Player::Update(const Mouse& mouse, const Keyboard& keyboard, Camera* cam)
{
	if(keyboard.IsKeyPressed(KEY_W))
	{ //move forward
		_pos += _target * SPEED;
	}
	if(keyboard.IsKeyPressed(KEY_S))
	{ //move back
		_pos -= _target * SPEED;
	}
	if (keyboard.IsKeyPressed(KEY_A))
	{ //move left
		Vec3 leftVec = _target;
		leftVec = leftVec.Cross(Vec3(0.0f, 1.0f, 0.0f));
		leftVec.Normalize();
		_pos -= leftVec * SPEED;
	}
	if(keyboard.IsKeyPressed(KEY_D))
	{ //move right
		Vec3 rightVec = _target;
		rightVec = rightVec.Cross(Vec3(0.0f, 1.0f, 0.0f));
		rightVec.Normalize();
		_pos += rightVec * SPEED;
	}
	_player->SetPosition(_pos);
	_light->SetPosition(_pos);
	//move cam
	if (cam != nullptr)
	{
		Vec3 camPos = Vec3(_pos.x, _pos.y + 3.0f, _pos.z + 10.0f);
		cam->SetPosition(camPos);
		Vec3 tar = (_pos - camPos).GetNormalizedVec();
		cam->SetTarget(tar);
	}
}

//*************************************************************************
//draw
//*************************************************************************
void Player::Draw()
{
	if (_player != nullptr)
	{
		_player->Draw();
	}
	if (_light != nullptr)
	{
		_light->Draw();
	}
}

//*************************************************************************
//delete
//*************************************************************************
void Player::Release()
{
	_is_kill = true;
}
