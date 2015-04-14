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

	void damage(float damage);
	void aggro(){ _agentState = AgentState::CHASE; };

	bool inRange(glm::vec3 playerPos);
	bool lookForPlayer(glm::vec3 playerPos);

private:

	AgentState _agentState; 

	glm::vec3 _patPos, _patDir;

	glm::vec3 _fieldOfViewLeft, _fieldOfViewRight;

	float _life; //Giving the enemies a life total
	float _speed; //The agents need a movement speed
	float _range; //Giving the agent a range to his attacks.
	float _patrolTimer, _patrolLimit;

};