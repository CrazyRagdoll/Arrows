#include "AgentMelee.h"

AgentMelee::AgentMelee(glm::vec3 pos, glm::vec3 dir, float width, float height): 
	_agentState(AgentState::CHASE),
	_patrolTimer(0.0f),
	_patrolLimit(200.0f),
	_life(100.0f),
	_speed(0.003f),
	_range(width + 2.0f)
{
	_position = pos;
	_direction = dir;
	_width = width;
	_height = height;
}

AgentMelee::~AgentMelee()
{

}

void AgentMelee::init()
{
	Agent::init("NONE");
}

void AgentMelee::draw()
{
	Agent::draw();
}

bool AgentMelee::update(float dt, glm::vec3 playerPos)
{
	//_playerPosition = playerPos;
	_dirToPlayer = playerPos - _position;
	glm::normalize(_dirToPlayer);
	if(_agentState == AgentState::PATROL)
	{
		//Some simple patrolling math to make the agent move back and forth
		if(_patrolTimer == _patrolLimit) { _patrolLimit *= -1; _direction *= -1; } 
		if(_patrolLimit > 0) { _patrolTimer++; } else { _patrolTimer--; }
		_position += _direction * _speed * dt;
	} else if(_agentState == AgentState::CHASE) {
		_position += _dirToPlayer * _speed * dt;
	}

	if(_agentState == AgentState::DEAD) { return true; }
	return false;
}