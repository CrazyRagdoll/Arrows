#include "PlayerStatus.h"

PlayerStatus::PlayerStatus() :
	_score(0.0f)
{

}

PlayerStatus::~PlayerStatus()
{

}

void PlayerStatus::init()
{
	_life = 1000.0f;
	_time = 1000.0f;
	_ammo = 10;
	std::cout << "Your life: " << _life << std::endl;
	std::cout << "Time left: " << _time << std::endl;
	std::cout << "Your ammo: " << _ammo << std::endl;
}

void PlayerStatus::reset()
{
	_life = 1000.0f;
	_time = 1000.0f;
	_ammo = 10;
	std::cout << "Your life: " << _life << std::endl;
	std::cout << "Time left: " << _time << std::endl;
	std::cout << "Your ammo: " << _ammo << std::endl;
}

void PlayerStatus::damage(float damage)
{
	_life -= damage;
	std::cout << "Your life: " << _life << std::endl;
}