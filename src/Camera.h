#pragma once

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
using namespace glm;

//Camera class for 2D games
class Camera
{
public:
	Camera();
	~Camera();

	void init(int screenWidth, int screenHeight);

	void update();

	//camera translation functions for player movement
	void move(float speed, float dt);
	void strafe(float speed, float dt);
	void jump(float speed, float dt);

	//mouse rotation movement for the player view
	void rotate(double xpos, double ypos);

	//Getters
	mat4 getViewMatrix(){ return _viewMatrix; }
	mat4 getProjectionMatrix(){ return _projectionMatrix; }
	vec3 getPosition(){ return _position; }
	vec3 getDirection(){ return _direction; }
	vec3 getUp(){ return _up; }

	void updateProjectionMatrix();	
	void updateViewMatrix();

	bool _jumping, _falling;

private:

	int _screenWidth, _screenHeight;
	
	vec3 _position, _direction, _right, _up;

	float _horizontalAngle, _verticalAngle, _fov, _mouseSpeed, _speed, _vertFoV;
	float _initJumpSpeed, _jumpSpeed, _gravityIntensity, _FLOOR;

	mat4 _viewMatrix, _projectionMatrix;
};