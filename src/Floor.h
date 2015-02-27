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

	TextureLoader _textureLoader;

	GLSLProgram _colorProgram;	
};
