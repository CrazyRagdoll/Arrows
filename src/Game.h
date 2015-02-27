#ifndef GAME_H_
#define GAME_H_

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <vector>

#include "GLSLProgram.h"
#include "Window.h"
#include "Camera.h"
#include "InputManager.h"
#include "Timing.h"
#include "Arrow.h"
#include "Cube.h"
#include "Floor.h"

enum class GameState {PLAY, MAIN_MENU, EXIT};

class Game
{
public:
	Game();
	~Game();

	void run();

private:
	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();

	Window _window;
	int _screenWidth;
	int _screenHeight;

	Cube _cube;	

	Floor _floor;

	GameState _gameState;	

	GLSLProgram _colorProgram;

	Camera _camera;

	InputManager _inputManager;

	FpsLimiter _fpsLimiter;

	std::vector<Arrow> _arrows;

	float _maxFPS;
	float _fps;
	float _time;
	float _shotTimer, _SHOTSPEED;
};

#endif
