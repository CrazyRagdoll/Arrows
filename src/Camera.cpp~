#include "Camera.h"

Camera::Camera() : 
	_position(0.0f, 0.0f, 0.0f), 
	_cameraMatrix(1.0f), 
	_orthoMatrix(1.0f),
	_scale(1.0f), 
	_needsMatrixUpdate(true),
	_screenWidth(500),
	_screenHeight(500)
{

}

Camera::~Camera()
{

}

void Camera::init(int screenWidth, int screenHeight)
{
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
	_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
}

void Camera::update()
{

	if(_needsMatrixUpdate)
	{
		glm::vec3 translate(-_position.x, -_position.y, -_position.z);
		_cameraMatrix = glm::translate(_orthoMatrix, translate);
		glm::vec3 scale(_scale, _scale, _scale);
		_cameraMatrix = glm::scale(_cameraMatrix, scale); 
		_needsMatrixUpdate = false;
	}	

}
