//*************************************************************************
// DarkMatter OpenGL 3D Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: GameObjFactory
// Source File: [gameObjFactory.cpp]
//
// License:
// Copyright(C) <2018>  <Christopher Tall>
//
// This is software is copyrighted.
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
#include "gameObjFactory.h"
#include "objects/multBoxes.h"

//*************************************************************************
// Class: GameObjFactory
// Function Name: CreateGameObject
// Explanation: create a new instance of the specified object
// Argument{s}:
// Other: -
//*************************************************************************
GameObjBase* GameObjFactory::GenerateGameObject(CREATE_ID id)
{
	switch (id)
	{
	case CREATE_OBJ_ID_BOXES:
		return new MultBoxes;
		break;
	}
	return nullptr;
}