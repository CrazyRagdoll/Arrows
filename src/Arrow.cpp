#include "Arrow.h"
#include "Cube.h"

Arrow::Arrow(glm::vec3 pos, glm::vec3 dir, float speed, int lifeTime) :
	_gravity(0.010f),
	_floorTime(100)
{
	_lifeTime = lifeTime;
	_position = pos;
	_direction = dir;
	_speed = speed;
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

bool Arrow::update()
{	
	//checking to see if the arrow is still in flight or not, then updating its position and deleting after a certain time
	if((_position.y + (_direction.y * _speed)) < -0.5){
		_floorTime--;
	} else {
		_direction.y -= _gravity;
		_position += _direction * _speed;
		_lifeTime--;
	}

	if(_lifeTime == 0 || _floorTime == 0) { return true; }
	return false;
}
