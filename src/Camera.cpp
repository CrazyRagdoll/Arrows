#include "Camera.h"

#include <iostream>
#include <string>

double TO_DEG = 180/3.14;

Camera::Camera() : _position(0.0f, 50.0f, 10.0f),
	_horizontalAngle(3.14f),
	_verticalAngle(0.0f),
	_fov(45.0f),
	_mouseSpeed(0.01f),
	_speed(3.0f),
	_projectionMatrix(1.0f),
	_vertFoV(75.0f),
	_jumping(false),
	_falling(true),
	_onFloor(false),
	_onTerrain(false),
	_crouched(false),
	_initJumpSpeed(5.0f),
	_jumpSpeed(_initJumpSpeed),
	_playerHeight(10.0f),
	_playerWidth(2.5f),
	_gravityIntensity(0.9)
{
}

Camera::~Camera()
{
}

void Camera::init(int screenWidth, int screenHeight) {
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
	update();
	updateProjectionMatrix();
	updateViewMatrix();
}

void Camera::rotate(double xpos, double ypos)
{
	_horizontalAngle += _mouseSpeed * float(_screenWidth/2 - xpos);
	float verticalDeg = (_verticalAngle + (_mouseSpeed * float(_screenHeight/2 - ypos))) * TO_DEG ;
	//To make sure the player cannot look past the vertical view distance
	if(verticalDeg > -_vertFoV && verticalDeg < _vertFoV)
	{
		_verticalAngle += _mouseSpeed * float(_screenHeight/2 - ypos);
	}	
	updateViewMatrix();
}

void Camera::update()
{
	_right = glm::vec3(
		sin(_horizontalAngle - 3.14f/2.0f),
		0,
		cos(_horizontalAngle - 3.14f/2.0f)
	);
	
	_direction = glm::vec3(
		cos(_verticalAngle) * sin(_horizontalAngle),
		sin(_verticalAngle),
		cos(_verticalAngle) * cos(_horizontalAngle)
	);

	//Calculating which way is up
	_up = glm::cross(_right, _direction);

	// if you're not jumping then you're falling!!
	if(!_jumping && !_onFloor && !_onTerrain){ _falling = true; }

	// Do the jumping & falling math to update the camera position!
	if(_jumping){
		//Jumping maths
		_jumpSpeed *= _gravityIntensity;
		_position.y += 1.0f * _jumpSpeed;
		//To stop the ascending and cause the camera to fall
		if(_jumpSpeed < 0.2)
		{
			_jumping = false;
			_falling = true;
		}
	}
	if(_falling){
		//Make sure the camera is no on the floor or terrain
		if(!_onFloor && !_onTerrain){
			//Do the falling maths!
			_jumpSpeed *= 2 - _gravityIntensity;
			_position.y -= 1.0f * _jumpSpeed;
		} else {
			_falling = false;
			_jumpSpeed = 0.2;
		}
	} 

	//If the player falls through the floor reset his position
	if(_position.y <= -5000){ resetCameraPosition(); }
}

//A function to reset the camera to its original position
void Camera::resetCameraPosition()
{
	_horizontalAngle = 3.14f;
	_verticalAngle = 0.0f; 	
	_position = vec3(0.0f, 5.0f, 10.0f);
	updateProjectionMatrix();
	updateViewMatrix();
}

void Camera::updateProjectionMatrix()
{
	//projection matrix
	_projectionMatrix = glm::perspective(_fov, 4.0f / 3.0f, 0.1f, 1000.0f);
}

void Camera::updateViewMatrix()
{
	//camera matrix
	_viewMatrix = glm::lookAt(
				_position, 		//where the camera currently is
				_position + _direction,  //it will look here,
				_up			//which way is up (0.1.0)
				);
}

/* ******** Player movement functions ******** */

void Camera::move(float speed, float dt)
{
	_position.x += _direction.x * dt * speed;
	_position.z += _direction.z * dt * speed;
	updateViewMatrix();
}
void Camera::strafe(float speed, float dt)
{
	_position += _right * dt * speed;
	updateViewMatrix();
}
void Camera::jump(float speed, float dt)
{ 

	_jumpSpeed = _initJumpSpeed * speed;
	_jumping = true;
	updateViewMatrix();
}

/* ******** Collision detection functions ******** */

bool Camera::checkFloorCollision(Floor& floor)
{
	//if(_crouched) { _playerHeight = 5.0f; } else { _playerHeight = 10.0f; }
	return(_position.y - _playerHeight < floor._y &&
		   _position.x < floor._x + floor._width &&
		   _position.x > floor._x - floor._width &&
		   _position.z < floor._z + floor._width &&
		   _position.z > floor._z - floor._width); 
}

bool Camera::checkOnTerrain(Terrain& terrain)
{
	return(_position.x - _playerWidth < terrain._position.x + terrain._size &&
		   _position.x + _playerWidth > terrain._position.x - terrain._size &&
		   _position.y - _playerHeight - 3.5f <= terrain._position.y + terrain._size &&
		   _position.y + _playerHeight > terrain._position.y - terrain._size - 5.0f &&
		   _position.z - _playerWidth < terrain._position.z + terrain._size &&
		   _position.z + _playerWidth > terrain._position.z - terrain._size);
}

bool Camera::checkUnderTerrain(Terrain& terrain)
{

}

bool Camera::checkTerrainCollision(Terrain& terrain)
{
	return(_position.x - _playerWidth < terrain._position.x + terrain._size &&
		   _position.x + _playerWidth > terrain._position.x - terrain._size &&
		   _position.y - _playerHeight < terrain._position.y + terrain._size &&
		   _position.y + _playerHeight > terrain._position.y - terrain._size &&
		   _position.z - _playerWidth < terrain._position.z + terrain._size &&
		   _position.z + _playerWidth > terrain._position.z - terrain._size); 
}