#pragma once

#include "Agent.h"

class Player : public Agent
{
public:
	Player();
	~Player();

	void init(int speed, glm::vec3 pos);	

	void update();

private:

};
