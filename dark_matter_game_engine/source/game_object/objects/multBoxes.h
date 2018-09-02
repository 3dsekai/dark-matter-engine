#pragma once

#include <vector>
#include "../../meshes/cube.h"
#include "../gameObjBase.h"

class MultBoxes : public GameObjBase
{
public:
	MultBoxes();
	~MultBoxes();

	//initialize game object
	void Init() override;
	//update game object
	void Update(float time, const Mouse& mouse, const Keyboard& keyboard) override;
	//draw game object
	void Draw(Camera& cam) override;
	//delete game object
	void Release() override;
	//set position
	void SetPosition(const Vec3& pos) 
	{
		_pos = pos;
	};

private:
	std::vector<Cube*> _cubes;
	Vec3 _pos;
};
