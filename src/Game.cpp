#include "Game.h"
#include "Errors.h"

#include <iostream>
#include <string>

Game::Game() : 
	_screenWidth(1024), 
	_screenHeight(768), 
	_time(0.0f), 
	_window(nullptr), 
	_gameState(GameState::PLAY)
{
}

Game::~Game()
{

}

void Game::run()
{
	initSystems();

	//test sprite
	_sprite.init(-1.0f, -1.0f, 2.0f, 2.0f);

	gameLoop();
}

void Game::initSystems()
{
	// Initialize ALL OF THE SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	// Creating and opening an SDL window.
	_window = SDL_CreateWindow("Arrows", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
	if (_window == nullptr)
	{
		fatalError("SDL window could not be created!");
	}

	// Setting up the OpenGL context
	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr)
	{
		fatalError("SDL_GL context could not be created!");
	}

	// Setting up Glew
	GLenum error = glewInit();
	if(error != GLEW_OK) //GLEW_OK = 0 enum. Which means glew initalized
	{
		fatalError("Could not initalize glew!");
	}

	// Enabling double buffer to make the game smoother by removing flickering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Clearing the screen and setting it to blue
	glClearColor(0.0f, 0.0f, 2.0f, 2.0);

	initShaders();
}

void Game::initShaders()
{
	_colorProgram.compileShaders("../src/Shaders/colorShading.vert", "../src/Shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.linkShaders();
}

void Game::gameLoop() 
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		_time += 0.01;
		drawGame();
	}
}

void Game::processInput()
{
	SDL_Event evnt;

	// Will keep the CPU looking for events untill one is pressed.
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

void Game::drawGame()
{
	// Setting the base depth to 1.0
	glClearDepth(1.0);

	// Clearing the Colour and Depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();

	GLuint timeLocation = _colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation, _time);

	//draw our sprite
	_sprite.draw();

	_colorProgram.unuse();

	// Swap the buffers and draw everything onto the screencd 
	SDL_GL_SwapWindow(_window);
}
