#include "AgentMelee.h"

AgentMelee::AgentMelee(glm::vec3 pos, glm::vec3 dir, float width, float height): 
	_agentState(AgentState::PATROL),
	_patrolTimer(0.0f),
	_patrolLimit(200.0f),
	_life(100.0f),
	_speed(0.04f),
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

void AgentMelee::damage(float damage)
{
	_life -= damage;
}

bool AgentMelee::lookForPlayer(glm::vec3 playerPos)
{
	//Along with the current position of the player these two values form a triangle of view
	_fieldOfViewLeft  =  glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), _direction * 50.0f) + _direction * 100.0f + _position;
	_fieldOfViewRight = -glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), _direction * 50.0f) + _direction * 100.0f + _position;

	//Barycentric coordinate system collision detection
	glm::vec3 p2 = _fieldOfViewLeft; glm::vec3 p3 = _fieldOfViewRight; glm::vec3 p1 = _position;
	float alpha = ((p2.z - p3.z)*(playerPos.x - p3.x) + (p3.x - p2.x)*(playerPos.z - p3.z)) /
					((p2.z - p3.z)*(p1.x - p3.x) + (p3.x - p2.x)*(p1.z - p3.z));
	float beta  = ((p3.z - p1.z)*(playerPos.x - p3.x) + (p1.x - p3.x)*(playerPos.z - p3.z)) / 
					((p2.z - p3.z)*(p1.x - p3.x) + (p3.x - p2.x)*(p1.z - p3.z));
	float gamma = 1.0f - alpha - beta;

	if(alpha > 0 && beta > 0 && gamma > 0) {
		//std::cout << "I SEE YOU" << std::endl;
		return true;
	} 
	return false;
}

bool AgentMelee::update(float dt, glm::vec3 playerPos)
{
	if(lookForPlayer(playerPos)) { _agentState = AgentState::CHASE; } else { _agentState = AgentState::PATROL; }
	if(_agentState == AgentState::PATROL)
	{
		//Some simple patrolling math to make the agent move back and forth
		if(_patrolTimer == _patrolLimit) { _patrolLimit *= -1; _direction *= -1; } 
		if(_patrolLimit > 0) { _patrolTimer++; } else { _patrolTimer--; }
		_position += _direction * (_speed * dt);
	} else if(_agentState == AgentState::CHASE) {
		//Getting the direction to the player.
		_direction = glm::normalize(playerPos - _position);
		//Move towards the player
		_position.x += _direction.x * (_speed * dt);
		_position.z += _direction.z * (_speed * dt);
	} else if(_agentState == AgentState::ATTACK)
	{
	}
	
	if(_life <= 0) { return true; }
	return false;
}