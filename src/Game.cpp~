#include "Game.h"

#include <iostream>
#include <string>

void fatalError(std::string errorString)
{
	std::cout << errorString << std:endl;
	std::cout << "Enter any key to quit...";
	int tmp;
	std::cin >> tmp;
	SDL_Quit();
	exit(1);
}

Game::Game()
{
	_window = nullptr;
	_screenWidth = 680;
	_screenHeight = 420;
	_gameState = GameState::PLAY;
}

Game::~Game()
{

}

void Game::run()
{
	initSystems();
	gameLoop();
}

void Game::initSystems()
{
	SDL_Init(SDL_INIT_EVERYTHING); // initialize SDL

	_window = SDL_CreateWindow("Arrows", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
	
	if (_window == nullptr)
	{
		fatalError("SDL window could not be created!");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr)
	{
		fatalError("SDL_GL context could not be created!");
	}

	GLenum error = glewInit();
	if(error != GLEW_OK)
	{
		fatalError("Could not initalize glew!");
	} 
}

void Game::gameLoop() 
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
	}
}

void Game::processInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
				break;
		}
	}
}
