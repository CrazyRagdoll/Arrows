#pragma once

#include "Agent.h"
#include "Camera.h"
#include "Terrain.h"
#include "PlayerStatus.h"

enum class AgentState {PATROL, CHASE, ATTACK};

class AgentMelee : public Agent
{
public:
	AgentMelee(glm::vec3 pos, glm::vec3 dir, float width, float height);
	~AgentMelee();

	void init();

	void draw();

	bool update(float dt, PlayerStatus player, Camera camera);

	//A function to damage the agent's heath
	void damage(float damage);
	//A function to get the attention of the agent
	void aggro(){ _agentState = AgentState::CHASE; };

	//A functions to hunt down the player
	void move(float dt, Camera camera);
	void patrol(float dt, Camera camera);
	void chase(float dt, Camera camera);
	void attack(float dt, Camera camera, PlayerStatus player);

	//A Check to see if the agent is in range to attack the player.
	bool inMeleeRange(Camera camera);
	//A cheeck to see if the player is in the agents Line of Sight
	bool lookForPlayer(glm::vec3 playerPos);
	//A check to see if the next movement will make the agent collide with the player
	bool collideWithPlayer(Camera camera, glm::vec3 newPos);

	//Returns how much damage the agent will do 
	float getDamage() { return _damage; }

	bool _hitPlayer; //A boolean to tell the game if the agent has hit the player

private:

	AgentState _agentState; 

	glm::vec3 _patPos, _patDir;

	glm::vec3 _fieldOfViewLeft, _fieldOfViewRight;

	float _life; //Giving the enemies a life total
	float _speed; //The agents need a movement speed
	float _currentSpeed; //The agents will have varrying speeds! for chasing and patroling!!!
	float _attackSpeed, _asCount; //The agent needs an attack speed to regulate how fast he atttacks
	float _damage; //The amount of damage the agent does with an attack!
	float _range; //Giving the agent a range to his attacks.
	float _patrolTimer, _patrolLimit;

};