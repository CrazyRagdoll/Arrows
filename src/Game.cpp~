#include "Game.h"

Game::Game()
{
	_window = nullptr;
	_screenWidth = 680;
	_screenHeight = 420;
}

Game::~Game()
{

}

void Game::run()
{
	initSystems();
}

void Game::initSystems()
{
	SDL_Init(SDL_INIT_EVERYTHING); // initialize SDL

	_window = SDL_CreateWindow("Arrows", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
}
