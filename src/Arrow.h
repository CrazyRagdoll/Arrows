#pragma once

#include "glm/glm.hpp"

#include "Cube.h"
#include "Floor.h"
#include "Terrain.h"
#include "Agent.h"

class Arrow : public Cube
{
public:
	Arrow(glm::vec3 pos, glm::vec3 dir, float speed, float size, int lifeTime);
	~Arrow();

	void init();

	void draw();

	bool update(float dt);

	void hit(){ _stuck = true; };

	void clean();

	bool checkFloorCollision(Floor& floor);
	bool checkTerrainCollision(Terrain& terrain);
	bool checkAgentCollision(Agent& agent);

private:
	int _lifeTime;
	float _speed, _width;
	glm::vec3 _direction;
	glm::vec3 _position;
	glm::vec3 _velocity;

	bool _stuck;

	float _gravity;

	int _floorTime;
};