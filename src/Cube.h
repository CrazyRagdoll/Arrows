#pragma once

#include "glm/glm.hpp"

#include "GLTexture.h"
#include <string>
#include "TextureLoader.h"
#include "GLSLProgram.h"

using namespace std;

class Cube 
{
public:
	Cube();
	~Cube();

	void init(float x, float y, float z, float width);

	bool checkCollision(Cube& cube);

	void draw();

private:
	float _x, _y, _z, _width;

	glm::vec3 _position;

	GLuint _vboID; //vertex buffer object ID
	GLTexture _texture;

	TextureLoader _textureLoader;

	GLSLProgram _colorProgram;	
};