#ifndef GAME_H_
#define GAME_H_

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>

#include "GLSLProgram.h"
#include "Camera.h"
#include "Sprite.h"

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

	SDL_Window* _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;	

	//test sprites
	Sprite _sprite;

	GLSLProgram _colorProgram;

	Camera _camera;

	float _time;
};

#endif
