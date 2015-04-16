#pragma once

#include <iostream>

class PlayerStatus 
{
public:

	PlayerStatus();
	~PlayerStatus();

	void init();

	void reset();

	void damage(float damage);

	//Some simple setters
	void setLife(float life) { _life = life; }
	void setTime(float time) { _time = time; }
	void setAmmo(int   ammo) { _ammo = ammo; }

	//Some simple getters.
	float getLife() { return _life; }
	float getTime() { return _time; }
	int   getAmmo() { return _ammo; }

	//incrementers
	void incLife(float life) { _life += life; std::cout << "Your life: " << _life << std::endl; }
	void incTime(float time) { _time += time; std::cout << "Your time: " << _time << std::endl; }
	void incAmmo(int   ammo) { _ammo += ammo; std::cout << "Your ammo: " << _ammo << std::endl; }

private:

	float _life;
	float _time;
	int _ammo;

};