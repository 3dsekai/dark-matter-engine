//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: -
// Source File: [drawUtil.h]
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
#ifndef _DRAWUTIL_H_
#define _DRAWUTIL_H_
//*************************************************************************
// Includes
//*************************************************************************
#include "../math_lib/mathUtil.h"
#include "../math_lib/mat4.h"
#include "../camera/camera.h"
#include "../window/window.h"

//*************************************************************************
// Draw Utility Functions
//*************************************************************************
namespace DrawUtil
{
	Mat4 GenerateProjectionViewMatrix(const Camera& cam)
	{
		//get view matrix
		Mat4 view = cam.GetViewMatrix();
		//prepare projection matrix.
		float w = Window::GetInstance()->GetWindowWidth();
		float h = Window::GetInstance()->GetWindowHeight();
		Mat4 proj = Mat4::Identity().Perspective(MathUtil::Deg2Rad(cam.GetFieldOfView()), 1.0f*(w/h), 0.1f, 100.0f);
		//view-projection transform
		return proj * view;
	}

};
#endif
