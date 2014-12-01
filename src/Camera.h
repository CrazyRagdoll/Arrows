#pragma once

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

//Camera class for 2D games
class Camera
{
public:
	Camera();
	~Camera();

	//sets up the orthographic matrix and screen dimensions
	void init(int screenWidth, int screenHeight);

	//updates the camera matrix if needed
	void update();

	glm::vec3 convertScreenToWorld(glm::vec3 screenCoords);

	//setters
	void setPosition(const glm::vec3& newPosition) { _position = newPosition; _needsMatrixUpdate = true; }
	void setScale(float newScale) { _scale = newScale; _needsMatrixUpdate = true; }

	//getters
	glm::vec3 getPosition() { return _position; }
	float getScale() { return _scale; }
	glm::mat4 getCameraMatrix() { return _cameraMatrix; }

private:
	int _screenWidth, _screenHeight;
	bool _needsMatrixUpdate;
	float _scale;
	glm::vec3 _position;
	glm::mat4 _cameraMatrix;
	glm::mat4 _orthoMatrix;
};
