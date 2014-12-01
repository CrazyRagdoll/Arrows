#pragma once

#include "glm/glm.hpp"
#include "SpriteBatch.h"

class Agent
{
public:
	Agent();
	virtual ~Agent();

private:

protected:
	glm::vec3 _position;
	float _speed;
};
