#include "Arrow.h"

Arrow::Arrow(glm::vec3 pos, glm::vec3 dir, float speed, float width, int lifeTime) :
	_gravity(-0.002f),
	_floorTime(100),
	_stuck(false)
{
	_lifeTime = lifeTime;
	_position = pos;
	_direction = dir;
	_speed = speed;
	_width = width;
	_velocity = dir * speed;
}

Arrow::~Arrow()
{

}

void Arrow::init()
{
	Cube::init(_position.x, _position.y, _position.z, _width, "NONE");
}

void Arrow::draw()
{	
	Cube::draw(); 
}

bool Arrow::update(float dt)
{	
	//checking to see if the arrow is still in flight or not, then updating its position and deleting after a certain time
	if(_stuck){
		_floorTime--;
	} else {
		//SUVAT to figure out the effects of gravity on the velocity v = u + at
		_velocity.y += (dt * _gravity);
		_position += _velocity;
		_lifeTime--;
	}

	if(_lifeTime == 0 || _floorTime == 0) { return true; }
	return false;
}

void Arrow::clean()
{

}

bool Arrow::checkFloorCollision(Floor& floor)
{
	//if(_crouched) { _playerHeight = 5.0f; } else { _playerHeight = 10.0f; }
	return(_position.y - _width < floor._y &&
		   _position.x < floor._x + floor._width &&
		   _position.x > floor._x - floor._width &&
		   _position.z < floor._z + floor._width &&
		   _position.z > floor._z - floor._width); 
}

bool Arrow::checkAgentCollision(Agent& agent)
{
	return(_position.x - _width < agent._position.x + agent._width &&
			_position.x + _width > agent._position.x - agent._width &&
			_position.y - _width < agent._position.y + agent._height &&
			_position.y + _width > agent._position.y - agent._height &&
			_position.z - _width < agent._position.z + agent._width &&
			_position.z + _width > agent._position.z - agent._width);
}

//Checking only the TIP of the arrow against stuffs
bool Arrow::checkTerrainCollision(Terrain& terrain)
{
	return(_position.x < terrain._position.x + terrain._size &&
		   _position.x > terrain._position.x - terrain._size &&
		   _position.y < terrain._position.y + terrain._size &&
		   _position.y > terrain._position.y - terrain._size &&
		   _position.z < terrain._position.z + terrain._size &&
		   _position.z > terrain._position.z - terrain._size); 
}