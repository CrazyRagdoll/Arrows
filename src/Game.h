#ifndef GAME_H_
#define GAME_H_

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <vector>

#include "GLSLProgram.h"
#include "Sprite.h"
#include "GLTexture.h"

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
	void calculateFPS();

	SDL_Window* _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;	

	std::vector <Sprite*> _sprites;

	GLSLProgram _colorProgram;

	float _fps;
	float _maxFPS;
	float _frameTime;

	float _time;
};

#endif
