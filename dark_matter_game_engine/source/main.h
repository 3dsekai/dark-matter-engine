//*************************************************************************
// Dark Matter OpenGL 3D Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Source file: [main.h]
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
// Includes
//*************************************************************************
#include <GL/glew.h>		//glew; access to OpenGL 3.3 functions
#include <GL/freeglut.h>	//GLUT is the tool kit to interface with the OS

//*************************************************************************
// Macros
//*************************************************************************
//ms = 1000 / fps
#define FPS_TO_MS_120 (8.33) 
#define FPS_TO_MS_60 (16.66) 
#define FPS_TO_MS_30 (33.33)
//window dimensions
#define SCREEN_WIDTH (1920)
#define SCREEN_HEIGHT (1080)
#define SCREEN_POS_X (0)
#define SCREEN_POS_Y (0)
