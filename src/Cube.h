#pragma once

#include "glm/glm.hpp"

#include "GLTexture.h"

class Cube 
{
public:
	Cube();
	~Cube();

	void init(float x, float y, float z, float width);

	void draw();

private:
	float _x;
	float _y;
	float _z;
	float _width;

	glm::vec3 _position;

	GLuint _vboID; //vertex buffer object ID
	GLTexture _texture;
};
