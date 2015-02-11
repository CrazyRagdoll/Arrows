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

	void move(vec3 v);

	mat4 getViewMatrix(){ return _viewMatrix; }
	mat4 getProjectionMatrix(){ return _projectionMatrix; }

	void updateProjectionMatrix();	
	void updateViewMatrix();

private:

	int _screenWidth, _screenHeight;
	
	vec3 _position;

	float _horizontalAngle, _verticalAngle, _fov, _speed, _mouseSpeed;

	mat4 _viewMatrix, _projectionMatrix;
};
