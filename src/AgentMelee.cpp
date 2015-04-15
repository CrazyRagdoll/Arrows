#include "AgentMelee.h"

AgentMelee::AgentMelee(glm::vec3 pos, glm::vec3 dir, float width, float height): 
	_agentState(AgentState::PATROL),
	_patrolTimer(0.0f),
	_patrolLimit(200.0f),
	_life(100.0f),
	_speed(0.04f),
	_currentSpeed(_speed),
	_range(width + 2.0f)
{
	_position = pos; _patPos = pos;
	_direction = dir; _patDir = dir;
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
		return true;
	} 
	return false;
}

bool AgentMelee::inMeleeRange(glm::vec3 playerPos)
{
	return(playerPos.x < _position.x + _width &&
			playerPos.x > _position.x - _width &&
			playerPos.y < _position.y + _height &&
			playerPos.y > _position.y - _height &&
			playerPos.z < _position.z + _height &&
			playerPos.z > _position.z - _height);
}

void AgentMelee::attack()
{

}

bool AgentMelee::update(float dt, glm::vec3 playerPos)
{	
	if(_agentState == AgentState::PATROL)
	{
		_currentSpeed = _speed;
		//Some simple patrolling math to make the agent move back and forth
		if(_patrolTimer == _patrolLimit) { _patrolLimit *= -1; _direction *= -1; } 
		if(_patrolLimit > 0) { _patrolTimer++; } else { _patrolTimer--; }
		_position += _direction * (_currentSpeed * dt);
		//If the agent finds the player Chase that mofo!
		if(lookForPlayer(playerPos)) { _agentState = AgentState::CHASE; } 
	} else if(_agentState == AgentState::CHASE) {
		_currentSpeed = _speed * 2;
		//Getting the direction to the player.
		_direction = glm::normalize(playerPos - _position);
		//Move towards the player
		_position.x += _direction.x * (_currentSpeed * dt);
		_position.z += _direction.z * (_currentSpeed * dt);
		//If the agent gets in attack range of the player attack!
		if(inMeleeRange(playerPos)){ _agentState = AgentState::ATTACK; } 
	} else if(_agentState == AgentState::ATTACK)
	{
		std::cout << "Rawrrrrrr" << std::endl;
		_agentState = AgentState::CHASE;
	}
	
	if(_life <= 0) { return true; }
	return false;
}