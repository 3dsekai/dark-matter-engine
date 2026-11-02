//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: CameraManager
// Source File: [cameraManager.cpp]
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
// Include
//*************************************************************************
#include "cameraManager.h"
#include "camera.h"

//*************************************************************************
// constructor
//*************************************************************************
CameraManager::CameraManager()
{
};
//*************************************************************************
// destructor
//*************************************************************************
CameraManager::~CameraManager()
{
	DestroyAll();
}
//*************************************************************************
//initialize
//*************************************************************************
void CameraManager::Init()
{
	for(int i = 0; i < RENDER_LAYER_NUM; i++)
	{
		_cam[i] = new Camera;
	}
}
//*************************************************************************
//update
//*************************************************************************
void CameraManager::Update()
{
	for(auto& cam : _cam)
	{
		cam.second->Update();
	}
}

//*************************************************************************
//get camera
//*************************************************************************
Camera* CameraManager::GetCamera(RENDER_LAYER layer)
{
	Camera* cam = nullptr;
	if(_cam.find(layer) != _cam.end())
	{
		cam = _cam[layer];
	}
	return cam;
}

//*************************************************************************
//destroy all cameras
//*************************************************************************
void CameraManager::DestroyAll()
{
	for(auto& cam : _cam)
	{
		delete cam.second;
		cam.second = nullptr;
	}
	_cam.clear();
}
