#include "Arrow.h"
#include "Cube.h"

Arrow::Arrow(glm::vec3 pos, glm::vec3 dir, float speed, int lifeTime) :
	_gravity(-0.002f),
	_floorTime(100),
	_stuck(false)
{
	_lifeTime = lifeTime;
	_position = pos;
	_direction = dir;
	_speed = speed;
	_velocity = dir * speed;
}

Arrow::~Arrow()
{

}

void Arrow::init()
{
	Cube::init(_position.x, _position.y, _position.z, 1.0f);
}

void Arrow::draw()
{
	Cube::draw();
}

bool Arrow::update(float dt)
{	
	//checking to see if the arrow is still in flight or not, then updating its position and deleting after a certain time
	if((_position.y + (_direction.y * _speed)) < -0.5 || _stuck){
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