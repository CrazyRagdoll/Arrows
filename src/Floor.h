#pragma once

#include "glm/glm.hpp"

#include <iostream>
#include "GLTexture.h"
#include "TextureLoader.h"
#include "GLSLProgram.h"

class Floor
{
public:
	Floor();
	~Floor();

	void initFloor(float x, float y, float z, float width);

	void draw();

	float _x;
	float _y;
	float _z;
	float _width;

private:

	glm::vec3 _position;

	GLuint _vboID; //vertex buffer object ID
	GLTexture _texture;

	TextureLoader _textureLoader;

	GLSLProgram _colorProgram;	
};