#pragma once

#include "Agent.h"
#include "Camera.h"

enum class AgentState {PATROL, CHASE, ATTACK};

class AgentMelee : public Agent
{
public:
	AgentMelee(glm::vec3 pos, glm::vec3 dir, float width, float height);
	~AgentMelee();

	void init();

	void draw();

	bool update(float dt, glm::vec3 playerPos);

	//A function to damage the agent's heath
	void damage(float damage);
	//A function to get the attention of the agent
	void aggro(){ _agentState = AgentState::CHASE; };

	//A function to attack the player
	void attack();

	//A Check to see if the agent is in range to attack the player.
	bool inMeleeRange(glm::vec3 playerPos);
	//A cheeck to see if the player is in the agents Line of Sight
	bool lookForPlayer(glm::vec3 playerPos);

private:

	AgentState _agentState; 

	glm::vec3 _patPos, _patDir;

	glm::vec3 _fieldOfViewLeft, _fieldOfViewRight;

	float _life; //Giving the enemies a life total
	float _speed; //The agents need a movement speed
	float _currentSpeed; //The agents will have varrying speeds! for chasing and patroling!!!
	float _range; //Giving the agent a range to his attacks.
	float _patrolTimer, _patrolLimit;

};