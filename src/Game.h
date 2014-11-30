#ifndef GAME_H_
#define GAME_H_

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <vector>

#include "GLSLProgram.h"
#include "Sprite.h"
#include "GLTexture.h"
#include "Window.h"
#include "Camera.h"
#include "SpriteBatch.h"
#include "InputManager.h"
#include "Timing.h"
#include "Bullet.h"

enum class GameState {PLAY, EXIT};

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
	GameState _gameState;	

	GLSLProgram _colorProgram;
	Camera _camera;

	SpriteBatch _spriteBatch;

	InputManager _inputManager;

	FpsLimiter _fpsLimiter;

	std::vector<Bullet> _bullets;

	float _maxFPS;
	float _fps;
	float _time;
};

#endif
