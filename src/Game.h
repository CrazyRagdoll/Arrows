#ifndef GAME_H_
#define GAME_H_

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>

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
	void gameLoop();
	void processInput();
	void drawGame();

	SDL_Window* _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;	

	//test sprite
	Sprite _sprite;
};

#endif
