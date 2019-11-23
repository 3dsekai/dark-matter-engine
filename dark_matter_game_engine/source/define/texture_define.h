//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: -
// Source File: [texture_define.h]
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

/*************************************************************************


	NOTE:
	textures are located under the directory: resources/img/...
	all texture files defined here must contain the relative path
	from the "img" folder.
	
	[example]
	
	absolute path:
	resources/img/cube/box.jpg
	
	relative path defined here:
	cube/box.jpg

	
**************************************************************************/

//*************************************************************************
// box texture
// source:
// https://www.deviantart.com/dactilardesign/art/Crate-generator-342135330
//*************************************************************************
#define BOX_TEXTURE ("resources/img/cube/box.jpg")
//*************************************************************************
// box2 texture
// source:
// https://learnopengl.com/img/textures/container2.png
//*************************************************************************
#define BOX2_TEXTURE ("resources/img/cube/box2.jpg")
#define BOX2_SPEC_TEX ("resources/img/cube/box2_specular.jpg")

//*************************************************************************
// miscellaneous
//*************************************************************************
#define BLACK_TEXTURE ("resources/img/misc/black_dot_texture.png")