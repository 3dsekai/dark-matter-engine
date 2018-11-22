//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: Camera
// Source File: [camera.cpp]
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
// Include
//*************************************************************************
#include "camera.h"
#include "../main.h"
#include "../input/mouse.h"
#include "../math_lib/mat4.h"
#include "../math_lib/mathUtil.h"
//*************************************************************************
// Macro Definitions
//*************************************************************************
#define SENSITIVITY (0.4f) //mouse motion sensitivity
#define SPEED (0.05f) //camera speed
#define DEFAULT_FOV (45.0f)
#define DEFAULT_YAW (-90.0f)
#define DEF_PITCH (0.0f)
#define OFFSET_CLAMP (1)
#define PITCH_CLAMP (89)

//*************************************************************************
// Class: Camera
// Function Name: Camera
// Argument{s}: -
// Explanation: Camera constructor
//*************************************************************************
Camera::Camera() :
		_pos(0.0f, 0.0f, 4.0f),
		_target(0.0f, 0.0f, -1.0f),
		_fov(DEFAULT_FOV),
		_yaw(DEFAULT_YAW),
		_pitch(DEF_PITCH),
		_last_x(SCREEN_WIDTH / 2),
		_last_y(SCREEN_HEIGHT / 2)
{
};

Camera::Camera(const Vec3& pos, const Vec3& target, float fov, float yaw, float pitch) :
		_pos(pos),
		_target(target),
		_yaw(yaw),
		_fov(fov),
		_pitch(pitch),
		_last_x(SCREEN_WIDTH / 2),
		_last_y(SCREEN_HEIGHT / 2)
{
};

//*************************************************************************
// Class: Camera
// Function Name: GetLookAtMat
// Argument{s}: - 
// Explanation: calculate and return the lookAt matrix for this camera
//*************************************************************************
Mat4 Camera::GetViewMatrix() const
{
	return Mat4::Identity().LookAt(_pos, _pos + _target, Vec3(0.0f, 1.0f, 0.0f));
}

//*************************************************************************
// Class: Camera
// Function Name: GetFieldOfView
// Argument{s}: - 
// Explanation: Get the field of view for the camera
//*************************************************************************
float Camera::GetFieldOfView() const
{
	return _fov;
}

//*************************************************************************
// Class: Camera
// Function Name: ProcessMouseInput
// Argument{s}:
// const Mouse& mouse: the global mouse instance
// Explanation: process the mouse input for the camera
//*************************************************************************
void Camera::ProcessMouseMotion(const Mouse& mouse)
{
	//get the offset from the previous mouse position to the current one
	float x_offset = (float)(_last_x - mouse.GetPosX());
	float y_offset = (float)(mouse.GetPosY() - _last_y);

	//store the mouse position for next time
	_last_x = mouse.GetPosX();
	_last_y = mouse.GetPosY();

	//dull down mouse movement so camera rotation is not so intense
	x_offset *= SENSITIVITY;
	y_offset *= SENSITIVITY;

	//clamp offset values so camera doesn't jump
	x_offset = MathUtil::Clamp(x_offset, OFFSET_CLAMP, -OFFSET_CLAMP);
	y_offset = MathUtil::Clamp(y_offset, OFFSET_CLAMP, -OFFSET_CLAMP);

	if(mouse.IsLeftButtonPressed())
	{
		Rotate(x_offset, y_offset);
	}
	else if (mouse.IsRightButtonPressed())
	{
		Zoom(y_offset);
	}
}

//*************************************************************************
// Class: Camera
// Function Name: ProcessKeyboardInput
// Argument{s}:
// const CamDir cam_dir: the direction for the camera to move
// Explanation: process the keyboard input for the camera
//*************************************************************************
void Camera::Move(const CamDir cam_dir)
{
	if(cam_dir == DIR_FORWARD)
	{ //move forward
		_pos += _target * SPEED;
	}
	if(cam_dir == DIR_BACK)
	{ //move back
		_pos -= _target * SPEED;
	}
	if (cam_dir == DIR_LEFT)
	{ //move left
		Vec3 leftVec = _target;
		leftVec = leftVec.Cross(Vec3(0.0f, 1.0f, 0.0f));
		leftVec.Normalize();
		_pos -= leftVec * SPEED;
	}
	if(cam_dir == DIR_RIGHT)
	{ //move right
		Vec3 rightVec = _target;
		rightVec = rightVec.Cross(Vec3(0.0f, 1.0f, 0.0f));
		rightVec.Normalize();
		_pos += rightVec * SPEED;
	}
}

//*************************************************************************
// Class: Camera
// Function Name: Rotate
// Argument{s}:
// float p_amount: the amount of pitch rotation for this frame
// float y_amount: the amount of yaw rotation for this frame
// Explanation: rotate the camera
//*************************************************************************
void Camera::Rotate(float p_amount, float y_amount)
{
	//add the movement amount to the angles for rotation
	_yaw += p_amount;
	_pitch += y_amount;

	//keep the pitch angle within the [-90, 90] range
	_pitch = MathUtil::Clamp(_pitch, PITCH_CLAMP, -PITCH_CLAMP);

	//convert angles from degrees to radians
	float yaw_rad = MathUtil::Deg2Rad(_yaw);
	float pitch_rad = MathUtil::Deg2Rad(_pitch);

	//convert the camera looking vector from spherical coordinates to cartesian coordinates
	//https://www.youtube.com/watch?v=1bTqPSiRLOo
	_target.x = cosf(yaw_rad) * cosf(pitch_rad);
	_target.y = sinf(pitch_rad);
	_target.z = sinf(yaw_rad) * cosf(pitch_rad);
	_target.Normalize();
}

//*************************************************************************
// Class: Camera
// Function Name: Zoom
// Argument{s}:
// float zoom: the amount to zoom for this frame
// Explanation: zoom into the scene
//*************************************************************************
void Camera::Zoom(float zoom)
{
	_fov += zoom;
	_fov = MathUtil::Clamp(_fov, DEFAULT_FOV, 1);
}
