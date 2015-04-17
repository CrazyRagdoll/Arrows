#pragma once

#include "glm/glm.hpp"

#include "Vertex.h"
#include "GLTexture.h"
#include "TextureLoader.h"
#include "GLSLProgram.h"

#include <iostream>
#include <cstddef>
#include <string>

enum class AgentState {PATROL, CHASE, ATTACK};

using namespace std;

class Agent 
{
public:
	Agent();
	~Agent();

	void init(string texture);

	void draw();

	//A cheeck to see if the player is in the agents Line of Sight
	bool lookForPlayer(glm::vec3 playerPos);

	//We need the enemies to have a position and to face a direction
	glm::vec3 _position, _direction;
	//We need the enemies ot have a height and width
	float _width, _height;

	float _viewDist, _viewRange; //Agent needs to have a view distance and range
	float _life; //Giving the enemies a life total
	float _speed; //The agents need a movement speed
	float _currentSpeed; //The agents will have varrying speeds! for chasing and patroling!!!
	float _attackSpeed, _asCount; //The agent needs an attack speed to regulate how fast he atttacks
	float _damage; //The amount of damage the agent does with an attack!
	float _range; //Giving the agent a range to his attacks.
	float _patrolTimer, _patrolLimit;

private: 	

	// Drawing variables
	GLuint _vboID; //vertex buffer object ID
	GLTexture _texture;

	TextureLoader _textureLoader;

	GLSLProgram _colorProgram;	

};