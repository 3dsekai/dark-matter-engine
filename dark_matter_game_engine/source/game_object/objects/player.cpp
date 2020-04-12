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
#include "../../math_lib/mat4.h"
#include "../../math_lib/mathUtil.h"
//#include "../../define/texture_define.h"

//*************************************************************************
//macro defintions
//*************************************************************************
#define PLAYER_SPEED (0.1f) //player movement speed
#define CAM_SPEED (2.0f) //camera movement speed
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
	Vec3 camRot = Vec3(0.0f, 0.0f, 0.0f);
	if(keyboard.IsKeyPressed(KEY_W))
	{ //move forward
		_pos += _target * PLAYER_SPEED;
	}
	if(keyboard.IsKeyPressed(KEY_S))
	{ //move back
		_pos -= _target * PLAYER_SPEED;
	}
	if (keyboard.IsKeyPressed(KEY_A))
	{ //move left
		Vec3 leftVec = _target;
		leftVec = leftVec.Cross(Vec3(0.0f, 1.0f, 0.0f));
		leftVec.Normalize();
		_pos -= leftVec * PLAYER_SPEED;
	}
	if(keyboard.IsKeyPressed(KEY_D))
	{ //move right
		Vec3 rightVec = _target;
		rightVec = rightVec.Cross(Vec3(0.0f, 1.0f, 0.0f));
		rightVec.Normalize();
		_pos += rightVec * PLAYER_SPEED;
	}
	if(keyboard.IsKeyPressed(KEY_I))
	{
		camRot.x -= CAM_SPEED;
	}
	if(keyboard.IsKeyPressed(KEY_K))
	{
		camRot.x += CAM_SPEED;
	}
	if(keyboard.IsKeyPressed(KEY_J))
	{
		camRot.y += CAM_SPEED;
	}
	if(keyboard.IsKeyPressed(KEY_L))
	{
		camRot.y -= CAM_SPEED;
	}
	//clamp pitch values so camera doesn't jump
	_rot.x = MathUtil::Clamp(_rot.x, 45.0f, -45.0f);
	_rot.z = MathUtil::Clamp(_rot.z, 45.0f, -45.0f);
	//set player position
	_player->SetPosition(_pos);
	_light->SetPosition(_pos);
	//move cam
	if (cam != nullptr)
	{
		//get camera position
		cam->AddYawPitch(camRot.y, camRot.x);
		Vec3 camPos = cam->GetSphericalCoords();
		camPos = (camPos * 10.0f) + _pos;
		//get camera target
		_target = (_pos - camPos).GetNormalizedVec();
		//set camera
		cam->SetPosition(camPos);
		cam->SetTarget(_target);
		_target.y = 0.0f;//set y to 0 so player doesn't move up or down
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
