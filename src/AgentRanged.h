#pragma once

#include "Agent.h"
#include "Camera.h"
#include "Terrain.h"
#include "PlayerStatus.h"

class AgentRanged : public Agent
{
public:
	AgentRanged(glm::vec3 pos, glm::vec3 dir, float width, float height, float life);
	~AgentRanged();

	void init();

	void draw();

	bool update(float dt, PlayerStatus player, Camera camera);

	//A function to damage the agent's heath
	void damage(float damage) { _life -= damage; }
	//A function to get the attention of the agent
	void aggro(){ _agentState = AgentState::CHASE; };

	//Functions to hunt down the player
	void move(float dt, Camera camera);
	void scout(float dt, Camera camera);
	void patrol(float dt, Camera camera);
	void chase(float dt, Camera camera);
	void attack(float dt, Camera camera, PlayerStatus player);

	//A Check to see if the agent is in range to attack the player.
	bool inAttackRange(Camera camera);
	//A check to see if the next movement will make the agent collide with the player
	bool collideWithPlayer(Camera camera, glm::vec3 newPos);
	//A checkt o see if the next movement will make the agent walk into terrain
	bool collideWithTerrain(Terrain terrain, glm::vec3 newPos);

	//Returns how much damage the agent will do 
	float getDamage() { return _damage; }

	bool _hitPlayer; //A boolean to tell the game if the agent has hit the player

private:

	AgentState _agentState; 

	glm::vec3 _patPos, _patDir;

};