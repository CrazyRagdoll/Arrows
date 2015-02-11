#include "Camera.h"

#include <iostream>
#include <string>

Camera::Camera() : _position(0.0f, 0.0f, 5.0f),
	_horizontalAngle(3.14f),
	_verticalAngle(0.0f),
	_fov(45.0f),
	_speed(3.0f),
	_mouseSpeed(0.00f),
	_projectionMatrix(1.0f)
{
}

Camera::~Camera()
{
}

void Camera::init(int screenWidth, int screenHeight) {
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;

	update();
}

void Camera::move(glm::vec3 v)
{
	_position += v;
	update();
}

void Camera::update()
{
	updateProjectionMatrix();
	updateViewMatrix();
}

void Camera::updateProjectionMatrix()
{
	//projection matrix
	_projectionMatrix = glm::perspective(_fov, 4.0f / 3.0f, 0.1f, 100.0f);
}

void Camera::updateViewMatrix()
{
	glm::vec3 right = glm::vec3(
		sin(_horizontalAngle - 3.14f/2.0f),
		0,
		cos(_horizontalAngle - 3.14f/2.0f)
	);
	
	glm::vec3 direction(
		cos(_verticalAngle) * sin(_horizontalAngle),
		sin(_verticalAngle),
		cos(_verticalAngle) * cos(_horizontalAngle)
	);

	glm::vec3 up = glm::cross(right, direction);

	//camera matrix
	_viewMatrix = glm::lookAt(
				_position, 		//where the camera currently is
				_position + direction,  //it will look here,
				up			//which way is up (0.1.0)
				);
}

