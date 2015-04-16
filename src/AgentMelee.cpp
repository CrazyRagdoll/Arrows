#include "AgentMelee.h"

AgentMelee::AgentMelee(glm::vec3 pos, glm::vec3 dir, float width, float height): 
	_agentState(AgentState::PATROL),
	_patrolTimer(0.0f),
	_patrolLimit(200.0f),
	_life(100.0f),
	_speed(0.04f),
	_attackSpeed(75.0f),
	_asCount(_attackSpeed),
	_damage(200.0f),
	_hitPlayer(false),
	_currentSpeed(_speed),
	_range(10.0f)
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
	//by using the cross product of the direction the agent is facing and which way is up I can find points to the left and right.
	_fieldOfViewLeft  =  glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), _direction * 50.0f) + _direction * 100.0f + _position;
	_fieldOfViewRight = -glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), _direction * 50.0f) + _direction * 100.0f + _position;

	//Barycentric coordinate system collision detection
	glm::vec3 p2 = _fieldOfViewLeft; glm::vec3 p3 = _fieldOfViewRight; glm::vec3 p1 = _position;
	float alpha = ((p2.z - p3.z)*(playerPos.x - p3.x) + (p3.x - p2.x)*(playerPos.z - p3.z)) /
					((p2.z - p3.z)*(p1.x - p3.x) + (p3.x - p2.x)*(p1.z - p3.z));
	float beta  = ((p3.z - p1.z)*(playerPos.x - p3.x) + (p1.x - p3.x)*(playerPos.z - p3.z)) / 
					((p2.z - p3.z)*(p1.x - p3.x) + (p3.x - p2.x)*(p1.z - p3.z));
	float gamma = 1.0f - alpha - beta;

	//If all of the values are above 0 the player is inside the LoS triangle.
	if(alpha > 0 && beta > 0 && gamma > 0) {
		return true;
	} 
	return false;
}

bool AgentMelee::inMeleeRange(Camera camera)
{
	glm::vec3 playerPos = camera.getPosition();
	float width = camera.getPlayerWidth();
	float height = camera.getPlayerHeight();
	return(playerPos.x - width < _position.x + _width + _range &&
			playerPos.x + width > _position.x - _width - _range &&
			playerPos.y - height < _position.y + _height + _range &&
			playerPos.y + height > _position.y - _height - _range &&
			playerPos.z - width < _position.z + _width + _range &&
			playerPos.z + width > _position.z - _width - _range);
}

bool AgentMelee::collideWithPlayer(Camera camera, glm::vec3 newPos)
{
	glm::vec3 playerPos = camera.getPosition();
	float width = camera.getPlayerWidth();
	float height = camera.getPlayerHeight();
	return(playerPos.x - width < _position.x + _width &&
		playerPos.x + width > _position.x - _width &&
		playerPos.y - height < _position.y + _height &&
		playerPos.y + height > _position.y - _height &&
		playerPos.z - width < _position.z + _width &&
		playerPos.z + width > _position.z - _width);
}

void AgentMelee::move(float dt, Camera camera)
{
	glm::vec3 newPos = _position + _direction * (_currentSpeed * dt);
	if(!collideWithPlayer(camera, newPos))
	{
		_position = newPos;
	}
}

void AgentMelee::patrol(float dt, Camera camera)
{
	//Some simple patrolling math to make the agent move back and forth
	if(_patrolTimer == _patrolLimit) { _patrolLimit *= -1; _direction *= -1; } 
	if(_patrolLimit > 0) { _patrolTimer++; } else { _patrolTimer--; }
	move(dt, camera);
	//If the agent finds the player Chase that mofo!
	if(lookForPlayer(camera.getPosition())) { _agentState = AgentState::CHASE; } 
}

void AgentMelee::chase(float dt, Camera camera)
{
	//If the agent gets in attack range of the player attack!
	if(inMeleeRange(camera)){ _agentState = AgentState::ATTACK; } 
	//Getting the direction to the player.
	_direction = glm::normalize(camera.getPosition() - _position);
	//Move towards the player
	move(dt, camera);
}

void AgentMelee::attack(float dt, Camera camera, PlayerStatus player)
{
	//Getting the direction to the player.
	_direction = glm::normalize(camera.getPosition() - _position);
	//Move towards the player
	move(dt, camera);

	//if the agent has stopped his attack "animation"
	if(_asCount == 0) 
	{ 
		if (inMeleeRange(camera)) {
			_hitPlayer = true;
		}
		_agentState = AgentState::CHASE; 
		_asCount = _attackSpeed;
	} else { 
		_asCount--; 
	}
}

bool AgentMelee::update(float dt, PlayerStatus player, Camera camera)
{	
	if(_agentState == AgentState::PATROL)
	{
		_currentSpeed = _speed;
		patrol(dt, camera);
		
	} else if(_agentState == AgentState::CHASE) {
		_currentSpeed = _speed * 1.5;
		chase(dt, camera);
		
	} else if(_agentState == AgentState::ATTACK)
	{
		_currentSpeed = _speed/2;
		attack(dt, camera, player);
	}
	
	if(_life <= 0) { return true; }
	return false;
}