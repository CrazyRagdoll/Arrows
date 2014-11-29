#include "Game.h"
#include "Errors.h"
#include "ResourceManager.h"

#include <iostream>
#include <string>

Game::Game() : 
	_screenWidth(1024), 
	_screenHeight(768), 
	_time(0.0f),  
	_gameState(GameState::PLAY),
	_maxFPS(60.0f)
{
	_camera.init(_screenWidth, _screenHeight);
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
	// Initialize ALL OF THE SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	// Enabling double buffer to make the game smoother by removing flickering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	_window.create("Arrows", _screenWidth, _screenHeight, 0);

	initShaders();

	_spriteBatch.init();
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
	
		_camera.update();
		
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

    const float CAMERA_SPEED = 20.0f;
    const float SCALE_SPEED = 0.1f;	
	
    //Will keep looping until there are no more events to process
    while (SDL_PollEvent(&evnt)) {
        switch (evnt.type) {
            case SDL_QUIT:
                _gameState = GameState::EXIT;
                break;
            case SDL_MOUSEMOTION:
                //std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
                break;
	    case SDL_KEYDOWN:
		switch(evnt.key.keysym.sym)
		{
		    case SDLK_w:
			_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, CAMERA_SPEED));
			break;
		    case SDLK_s:
			_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, -CAMERA_SPEED));
			break;
       		    case SDLK_d:
			_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
			break;
		    case SDLK_a:
			_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
			break;
		    case SDLK_q:
			_camera.setScale(_camera.getScale() + SCALE_SPEED);
			break;
		    case SDLK_e:
			_camera.setScale(_camera.getScale() - SCALE_SPEED);
			break;		
		}
		
        }
    }
}

void Game::drawGame()
{
	// Setting the base depth to 1.0
	glClearDepth(1.0);

	// Clearing the Colour and Depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Enable the shader
	_colorProgram.use();

	//using texture unit0
	glActiveTexture(GL_TEXTURE0);
	//get the uniform location
	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");	
	//tell the shader that the texture is in texture unit 0	
	glUniform1i(textureLocation, 0);
	
	//set the constantly chaning time variable
	GLuint timeLocation = _colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation, _time);
	
	//set the camera matrix
	GLuint pLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	_spriteBatch.begin();
	
	glm::vec4 pos(0.0f,0.0f,50.0f,50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	GLTexture texture = ResourceManager::getTexture("../src/Textures/PNG/CharacterRight_Standing.png");
	Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	_spriteBatch.draw(pos, uv, texture.id, 0.0f, color);

	_spriteBatch.end();

	_spriteBatch.renderBatch();

	//unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	//glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.unuse();

	// Swap the buffers and draw everything onto the screencd 
	_window.swapBuffer();
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
