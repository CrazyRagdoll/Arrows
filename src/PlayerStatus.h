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
	void setWave(int   wave) { _wave = wave; }

	//Some simple getters.
	float getLife() { return _life; }
	float getTime() { return _time; }
	int   getAmmo() { return _ammo; }
	int   getWave() { return _wave; }

	//incrementers
	void incTime(float time) { _time += time; std::cout << "Your time: " << _time << std::endl; }
	void incAmmo(int   ammo) { _ammo += ammo; std::cout << "Your ammo: " << _ammo << std::endl; }
	void incWave(int   wave) { _wave += wave; std::cout << "Starting Wave: " << _wave << "." << std::endl;}

private:

	float _life;
	float _time;
	float _score;
	int _ammo;
	int _wave;

};