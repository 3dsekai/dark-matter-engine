//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: Model
// Source File: [model.h]
//
// License:
// Copyright(C) <2019> <Christopher Tall>
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
#ifndef _MODEL_H_
#define _MODEL_H_

//*************************************************************************
// Includes
//*************************************************************************
#include "../math_lib/vec3.h"
#include "../math_lib/quat.h"
#include <vector>

class Mesh;
//*************************************************************************
// Model Class
//*************************************************************************
class Model
{
public:
	Model(const char* shaderName,
		  const char* modelName,
		  const Vec3& pos = Vec3(0.0f, 0.0f, 0.0f),
		  const Quat& rot = Quat::Identity(),
		  const Vec3& scale = Vec3(1.0f, 1.0f, 1.0f));

	~Model();

	void Draw();
	void Delete();

	inline void SetPosition(const Vec3& pos) { _pos = pos; };
	inline void SetRotation(const Quat& rot) { _rot = rot; };
	inline void SetScale(const Vec3& scale) { _scale = scale; };

	inline const Vec3 GetPosition() const { return _pos; };
	inline const Quat GetRotation() const { return _rot; };
	inline const Vec3 GetScale() const { return _scale; };

private:
	void LoadModel(const char* modelName);

private:
	const char* _shaderName; //model shader name
	const char* _modelName; //model path
	Vec3 _pos; //position
	Vec3 _scale; //scale
	Quat _rot; //rotation

	std::vector<Mesh*> _meshArr; //list of meshes that make up the model
};

#endif
