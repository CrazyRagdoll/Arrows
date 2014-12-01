#pragma once

#include "glm/glm.hpp"

#include "SpriteBatch.h"

class Bullet 
{
public:
	Bullet(glm::vec3 pos, glm::vec3 dir, float speed, int lifeTime);
	~Bullet();

	void draw(SpriteBatch& spriteBatch);
	//returns true when we are out of life	
	bool update();

private:
	int _lifeTime;
	float _speed;
	glm::vec3 _direction;
	glm::vec3 _position;
	
};
