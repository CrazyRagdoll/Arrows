#include "Game.h"
#include "Errors.h"

#include <iostream>
#include <string>

Game::Game() : 
	_screenWidth(1024), 
	_screenHeight(768), 
	_time(0.0f), 
	_window(nullptr), 
	_gameState(GameState::PLAY),
	_maxFPS(60.0f)
{

}

Game::~Game()
{

}

void Game::run()
{
	initSystems();

	_sprites.push_back(new Sprite());
	_sprites.back()->init(-1.0f, -1.0f, 1.0f, 1.0f, "../src/Textures/PNG/CharacterRight_Standing.png");

	_sprites.push_back(new Sprite());
	_sprites.back()->init(0.0f, -1.0f, 1.0f, 1.0f, "../src/Textures/PNG/CharacterRight_Standing.png");

	gameLoop();
}

void Game::initSystems()
{
	// Initialize ALL OF THE SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	// Enabling double buffer to make the game smoother by removing flickering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

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

	//Check the openGL version
	std::printf("***   OpenGL Version: %s   ***\n", glGetString(GL_VERSION)); 	
	
	// Clearing the screen and setting it to blue
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	//set vsync
	SDL_GL_SetSwapInterval(1);

	initShaders();
}

void Game::initShaders()
{
	_colorProgram.compileShaders("../src/Shaders/colorShading.vert", "../src/Shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}

void Game::gameLoop() 
{
	while (_gameState != GameState::EXIT)
	{
		//used for frame time measuring
		float startTicks = SDL_GetTicks();
		
		processInput();
		_time += 0.01;
	
		drawGame();
		calculateFPS();
		
		//print only once every 10 frames
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 10)
		{
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}

		float frameTicks = SDL_GetTicks() - startTicks;

		//limiting the fps
		if (1000.0f / _maxFPS > frameTicks) {
			SDL_Delay(1000.0f / _maxFPS - frameTicks);	
		}
		
	}
}

void Game::processInput()
{
    SDL_Event evnt;

    //Will keep looping until there are no more events to process
    while (SDL_PollEvent(&evnt)) {
        switch (evnt.type) {
            case SDL_QUIT:
                _gameState = GameState::EXIT;
                break;
            case SDL_MOUSEMOTION:
                //std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
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
	glActiveTexture(GL_TEXTURE0);

	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");	
	glUniform1i(textureLocation, 0);
	
	GLuint timeLocation = _colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation, _time);
	
	for(int i = 0; i < _sprites.size(); i++)
	{
		_sprites[i]->draw();
	}

	//glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.unuse();

	// Swap the buffers and draw everything onto the screencd 
	SDL_GL_SwapWindow(_window);
}

void Game::calculateFPS()
{
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	static float prevTicks = SDL_GetTicks();
	
	float currentTicks;
	currentTicks = SDL_GetTicks();

	_frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

	prevTicks = currentTicks;

	int count;
	currentFrame++;
	if (currentFrame < NUM_SAMPLES)
	{
		count = currentFrame;
	} else {
		count = NUM_SAMPLES;
	}

	float frameTimeAverage = 0;
	for (int i = 0; i < count; i++)
	{
		frameTimeAverage += frameTimes[i];
	}

	frameTimeAverage /= count;

	if (frameTimeAverage > 0) 
	{
		_fps = 1000.0f / frameTimeAverage;
	} else {
		_fps = 60.0f;
	}
}
