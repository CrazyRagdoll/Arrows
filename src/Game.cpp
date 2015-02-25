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
	_maxFPS(60.0f),
	_SHOTSPEED(100.0f),
	_shotTimer(100.0f)
{
	_camera.init(_screenWidth, _screenHeight);
	SDL_WarpMouseInWindow(_window.getWindow(), _screenWidth/2, _screenHeight/2);
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

	//creating the window screen
	_window.create("Arrows", _screenWidth, _screenHeight, 0);

	//hiding the cursor
	SDL_ShowCursor(0);		

	//initialize the shaders.
	initShaders();

	_spriteBatch.init();

	_fpsLimiter.init(_maxFPS);
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
		_fpsLimiter.begin();
		
		processInput();
		_time += 0.01;
	
		_camera.update();

		//update all the arrows
		for (int i = 0; i < _arrows.size();)
		{
			if(_arrows[i].update() == true)
			{
				_arrows[i] = _arrows.back();
				_arrows.pop_back();
			} else {
				i++;
			}
		}
		//Incrementing shot timer to regulate shotting speed
		_shotTimer++;
		
		drawGame();

		_fps = _fpsLimiter.end();
		
		//print only once every 10 frames
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 1000)
		{
			std::cout << "Fps: " << _fps << std::endl;
			frameCounter = 0;
		}
	}
}

void Game::processInput()
{
	SDL_Event evnt;

	float SPEED = 0.05f;

	//This block of code is used to rotate the camera using mouse input.
	static double lastTime = SDL_GetTicks();
	
	//finding the time since the current and last frame
	double currentTime = SDL_GetTicks();
	float deltaTime = float(currentTime - lastTime);

	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
				break;
			case SDL_KEYDOWN:
				_inputManager.pressKey(evnt.key.keysym.sym);
				break;
			case SDL_KEYUP:
				_inputManager.releaseKey(evnt.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				_inputManager.pressKey(evnt.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				_inputManager.releaseKey(evnt.button.button);
				break;
			}
		}
	if (_inputManager.isKeyPressed(SDLK_LSHIFT)){
		SPEED *= 2;
	}
	if (_inputManager.isKeyPressed(SDLK_w)){
		_camera.move(SPEED, deltaTime);
	}
	if (_inputManager.isKeyPressed(SDLK_s)){
		_camera.move(-SPEED, deltaTime);
	}
	if (_inputManager.isKeyPressed(SDLK_a)){
		_camera.strafe(-SPEED, deltaTime);
	}
	if (_inputManager.isKeyPressed(SDLK_d)){
		_camera.strafe(SPEED, deltaTime);
	}
	if (_inputManager.isKeyPressed(SDLK_SPACE)){
		if(!_camera._jumping && !_camera._falling){
			_camera.jump(SPEED/2, deltaTime);		
		}
	}
	if (_inputManager.isKeyPressed(SDLK_z)){
		_camera.jump(-SPEED/2, deltaTime);
	}
	if (_inputManager.isKeyPressed(SDLK_LCTRL)){
		//Crouch button
	}
	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)){
		if(_shotTimer >= _SHOTSPEED){
			_shotTimer = 0.0f;
			glm::vec3 displacement = glm::vec3(_camera.getDirection());
			normalize(displacement);
			displacement *=3;
			glm::vec3 position = glm::vec3(_camera.getPosition() + displacement);
			glm::vec3 direction = glm::vec3(_camera.getDirection());

			_arrows.emplace_back(position, direction, 1.0f, 250);			
		}
 	}
	if (_inputManager.isKeyPressed(SDLK_m)){
		SDL_ShowCursor(1);		
	} else {
		SDL_ShowCursor(0);
	}

	//get the postion of the mouse at this frame
	int xMousePos, yMousePos;
	SDL_GetMouseState(&xMousePos, &yMousePos);

	//reset the mouse position
	SDL_WarpMouseInWindow(_window.getWindow(), _screenWidth/2, _screenHeight/2);

	//update the rotation of the camera
	_camera.rotate(xMousePos, yMousePos);

	lastTime = currentTime;	
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
	
	//set the camera matrix
	GLuint pLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 projectionMatrix = _camera.getProjectionMatrix();
	glm::mat4 viewMatrix = _camera.getViewMatrix();
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 cameraMatrix = projectionMatrix * viewMatrix * modelMatrix;

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	_cube.init(0.0f, 0.0f, 0.0f, 5.0f);
	_cube.draw();
	
	for (int i = 0; i < _arrows.size(); i++)
	{
		_arrows[i].draw(_cube);
	}

	//unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	_colorProgram.unuse();

	// Swap the buffers and draw everything onto the screencd 
	_window.swapBuffer();
}