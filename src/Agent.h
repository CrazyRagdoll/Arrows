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
using namespace glm;

class Agent 
{
public:
	Agent();
	~Agent();

	void init(glm::vec3 position, float width, float height, string texture);

	void draw();

private:

	//We need the enemies to have a position and to face a direction
	vec3 _position, _direction; 
	//We need the enemies ot have a height and width
	float _width, _height; 
	//Giving the enemies a life total
	float _life, _speed;

	GLuint _vboID; //vertex buffer object ID
	GLTexture _texture;

	TextureLoader _textureLoader;

	GLSLProgram _colorProgram;	

};