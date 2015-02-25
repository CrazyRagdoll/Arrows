#pragma once

#include "glm/glm.hpp"

#include "Cube.h"

class Arrow 
{
public:
	Arrow(glm::vec3 pos, glm::vec3 dir, float speed, int lifeTime);
	~Arrow();

	void draw(Cube& cube);
	//returns true when we are out of life	
	bool update();

private:
	int _lifeTime;
	float _speed;
	glm::vec3 _direction;
	glm::vec3 _position;

	float _gravity;
	int _floorTime;
};
