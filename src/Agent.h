#pragma once

#include "glm/glm.hpp"

#include "Vertex.h"
#include "GLTexture.h"
#include "TextureLoader.h"
#include "GLSLProgram.h"

#include <iostream>
#include <cstddef>
#include <string>

using namespace std;

class Agent 
{
public:
	Agent();
	~Agent();

	void init(string texture);

	void draw();

	//We need the enemies to have a position and to face a direction
	glm::vec3 _position, _direction;
	//We need the enemies ot have a height and width
	float _width, _height;

private: 	

	GLuint _vboID; //vertex buffer object ID
	GLTexture _texture;

	TextureLoader _textureLoader;

	GLSLProgram _colorProgram;	

};