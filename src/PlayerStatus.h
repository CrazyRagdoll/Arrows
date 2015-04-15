#pragma once

class PlayerStatus 
{
public:

	PlayerStatus();
	~PlayerStatus();

	//Some simple getters.
	float getLife() { return _life; }
	float getTime() { return _time; }
	int   getAmmo() { return _ammo; }

	void  incAmmo( int ammo ) { _ammo += ammo; }

private:

	float _life;
	float _time;
	int _ammo;

};