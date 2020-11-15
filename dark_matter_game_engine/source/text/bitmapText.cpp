//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: BitmapText
// Source File: [bitmapText.cpp]
//
// License:
// Copyright(C) <2020> <Christopher Tall>
//
// This software is copyrighted.
// The copyright notice and license information in this document must be
// preserved in every copy of the document AS IS. Attribution to the
// original author of this software must be given in either the
// modified source OR in the product's documentation.
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
#include "bitmapText.h"
#include "vec3.h"

//*************************************************************************
// Constructor
//*************************************************************************
BitmapText::BitmapText(const BitmapTextParameters& textParams, const Vec3& pos) :
	_textParams(textParams)
	, _pos(pos)
{
	SetupText();
}

//*************************************************************************
// Destructor
//*************************************************************************
BitmapText::~BitmapText()
{
	Delete();
}

//*************************************************************************
// Draw Text
//*************************************************************************
void BitmapText::Draw()
{
}

//*************************************************************************
// Delete Text
//*************************************************************************
void BitmapText::Delete()
{
}

//*************************************************************************
// set new text
//*************************************************************************
void BitmapText::SetText(const char* text)
{
	_textParams._text = text;
	SetupText();
}

//*************************************************************************
// Reset the text parameters
//*************************************************************************
void BitmapText::ResetTextParameters(const BitmapTextParameters& textParams)
{
	_textParams = textParams;
	SetupText();
}

//*************************************************************************
// Set text for display
//*************************************************************************
void BitmapText::SetupText()
{
}

