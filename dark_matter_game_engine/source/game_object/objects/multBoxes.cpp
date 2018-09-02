#include "multBoxes.h"
#include "../../define/shader_define.h"

//constructor
MultBoxes::MultBoxes()
{
}

//constructor
MultBoxes::~MultBoxes()
{
	for (auto it = _cubes.begin(); it != _cubes.end(); it++)
	{
		delete *it;
		(*it) = nullptr;
	}
	_cubes.clear();
}

//initialize game object
void MultBoxes::Init()
{
	//cube 1
	_cubes.push_back(new Cube(SOLID_CUBE_SHADER_NAME,
					 		  Vec3(0.0f, 0.0f, 0.0f),
							  Vec3(1.0, 1.0f, 1.0f),
							  Vec3(0.0f, 0.0f, 0.0f),
							  Vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	//cube 2 
	_cubes.push_back(new Cube(SOLID_CUBE_SHADER_NAME,
					 		  Vec3(5.0f, 0.0f, 0.0f),
							  Vec3(1.0, 1.0f, 1.0f),
							  Vec3(0.0f, 0.0f, 0.0f),
							  Vec4(0.0f, 1.0f, 0.0f, 1.0f)));

	//cube 3
	_cubes.push_back(new Cube(SOLID_CUBE_SHADER_NAME,
					 		  Vec3(2.5f, 5.0f, 0.0f),
							  Vec3(1.0, 1.0f, 1.0f),
							  Vec3(0.0f, 0.0f, 0.0f),
							  Vec4(0.0f, 0.0f, 1.0f, 1.0f)));
}

//update game object
void MultBoxes::Update(float time, const Mouse& mouse, const Keyboard& keyboard)
{
}

//draw game object
void MultBoxes::Draw(Camera& cam)
{
	for(auto it = _cubes.begin(); it != _cubes.end(); it++)
	{
		(*it)->Draw(cam);
	}
}

//delete game object
void MultBoxes::Release()
{
	_is_kill = true;
}
