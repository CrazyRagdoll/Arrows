#ifndef CAMERA_H_
#define CAMERA_H_

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera {
public:
	Camera();	
	~Camera();

	void init(int screenWidth, int screenHeight);
	
	void update();

	void setPosition(const glm::vec3& newPosition){ _position = newPosition; _needsMatrixUpdate = true;}
	void setScale(float newScale) { _scale = newScale; _needsMatrixUpdate = true;}

	glm::vec3 getPosition() { return _position; }
	float getScale() { return _scale; }
	glm::mat4 getCameraMatrix() { return _cameraMatrix; }

private:
	int _screenWidth;
	int _screenHeight;
	bool _needsMatrixUpdate;
	float _scale;
	glm::vec3 _position;
	glm::mat4 _cameraMatrix;
	glm::mat4 _orthoMatrix;
};

#endif
