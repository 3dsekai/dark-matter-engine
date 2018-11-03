//*************************************************************************
// DarkMatter OpenGL 3D Engine Framework
// Class Name: Camera
// Source File: [camera.h]
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
#ifndef _CAMERA_H_
#define _CAMERA_H_

//*************************************************************************
// Include
//*************************************************************************
#include "../math_lib/vec3.h"
#include "../input/mouse.h"

class Mat4;

//*************************************************************************
// Camera Class
//*************************************************************************
class Camera
{
public:
	enum CamDir
	{
		DIR_NULL = 0,
		DIR_FORWARD,
		DIR_BACK,
		DIR_RIGHT,
		DIR_LEFT,
	};
public:
	Camera();
	Camera(const Vec3& pos, const Vec3& target, float fov, float yaw, float pitch);
	~Camera() = default;

	Mat4 GetViewMatrix() const;
	float GetFieldOfView() const;

	void ProcessMouseMotion(const Mouse& mouse);
	void Move(const CamDir cam_dir);

private:
	void Rotate(float p_amount, float y_amount);
	void Zoom(float zoom);

private:
	Vec3 _pos;	//camera position
	Vec3 _target;	//position of the camera's looking target
	float _fov;	//the camera's field of view
	float _yaw;	//the camera's yaw value (Euler y-rotation)
	float _pitch;	//the camera's pitch value (Euler x-rotation)
	int   _last_x;	//the mouse x-coordinate from the last frame
	int   _last_y;	//the mouse y-coordinate from the last frame
};

#endif
