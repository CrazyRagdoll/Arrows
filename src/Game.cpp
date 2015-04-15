#include "Game.h"
#include "Errors.h"

Game::Game() : 
	_screenWidth(1024), 
	_screenHeight(768), 
	_time(0.0f),  
	_gameState(GameState::PLAY),
	_maxFPS(60.0f),
	_SHOTSPEED(100.0f),
	_shotTimer(100.0f),
	_shotPower(0.0f),
	_paused(false),
	_floorSize(250.0f)
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

	//Adding an agent
	_meleeAgents.emplace_back(glm::vec3(0.0f, 7.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 2.5f, 7.5f);
	
	//Adding some terrain to the game
	//generateTerrain(5, 1, 5.0f, _floorSize);

	//initialize the shaders.
	initShaders();

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
		while(_gameState == GameState::MAIN_MENU)
		{

		}
		while(_gameState == GameState::PLAY)
		{
			//This block of code is used to rotate the camera using mouse input.
			static double lastTime = SDL_GetTicks();
			
			//finding the time since the current and last frame
			double currentTime = SDL_GetTicks();
			float deltaTime = float(currentTime - lastTime);

			_fpsLimiter.begin();
			
			processInput();
			_time += 0.01;
		
			_camera.update();

			//update the camera to see if the player is falling or not
			if(_camera.checkFloorCollision(_floor)) { _camera._onFloor = true; } else { _camera._onFloor = false; }

			//Check to see if the player is the terrain
			for( int i = 0; i < _terrain.size(); i++)
			{
				if(_camera.checkOnTerrain(_terrain[i])) { _camera._onTerrain = true; break; } else { _camera._onTerrain = false; }

			}

			//update all the arrows
			for (int i = 0; i < _arrows.size();)
			{
				if(_arrows[i].update(deltaTime) == true)
				{
					_arrows[i] = _arrows.back();
					_arrows.pop_back();
				} else {
					i++;
				}
			}

			if(_meleeAgents.size() <= 0)
			{
				_meleeAgents.emplace_back(glm::vec3(0.0f, 7.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 2.5f, 7.5f);
			}

			//updating all of the melee agents
			for (int i = 0; i < _meleeAgents.size();)
			{
				if(_meleeAgents[i].update(deltaTime, _camera.getPosition()) == true)
				{
					_meleeAgents[i] = _meleeAgents.back();
					_meleeAgents.pop_back();
				} else {
					i++;
				}
			}

			//Incrementing shot timer to regulate shooting speed
			_shotTimer++;
			
			drawGame();

			//Checking collisions between the arrows and STUFFS
			for (int i = 0; i < _arrows.size(); i++)
			{
				if(_arrows[i].checkCollision(_cube)) { _arrows[i].hit(); }
				if(_arrows[i].checkFloorCollision(_floor)) { _arrows[i].hit(); }
				for(int j = 0; j < _terrain.size(); j++)
				{
					if(_arrows[i].checkTerrainCollision(_terrain[j])) { _arrows[i].hit(); }
				}
				for(int j = 0; j < _meleeAgents.size(); j++)
				{
					if(_arrows[i].checkAgentCollision(_meleeAgents[j]) && _arrows[i].getActive()) 
						{ 
							std::cout << "HIT" << std::endl; 
							_arrows[i].hitAgent();
							_meleeAgents[j].damage(50); _meleeAgents[j].aggro(); 
						}
				}
			}


			_fps = _fpsLimiter.end();
			
			//print only once every 10 frames
			static int frameCounter = 0;
			frameCounter++;
			if (frameCounter == 1000)
			{
				std::cout << "Fps: " << _fps << std::endl;
				frameCounter = 0;
			}

			lastTime = currentTime;
		}
		while (_gameState == GameState::PAUSE)
		{
			processPauseInput();
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
	while (SDL_PollEvent(&evnt)) 
	{
		switch (evnt.type) 
		{
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
	if (_inputManager.isKeyPressed(SDLK_ESCAPE)){
		_paused = true;
	}
	if (!_inputManager.isKeyPressed(SDLK_ESCAPE) && _paused){
		_gameState = GameState::PAUSE;
		_paused = false;
	}
	if (_inputManager.isKeyPressed(SDLK_LCTRL)){
		//_camera._crouched = true;
	} else { /*_camera._crouched = false; */ }
	if (_inputManager.isKeyPressed(SDLK_LSHIFT)){
		SPEED *= 2;
	}
	if (_inputManager.isKeyPressed(SDLK_w) && !_inputManager.isKeyPressed(SDLK_a) && !_inputManager.isKeyPressed(SDLK_s) && !_inputManager.isKeyPressed(SDLK_d)){
		_camera.move(SPEED, deltaTime);
		for( int i = 0; i < _terrain.size(); i++)
		{
			if(_camera.checkTerrainCollision(_terrain[i])) { _camera.move(-SPEED, deltaTime); }
		}
	}
	if (!_inputManager.isKeyPressed(SDLK_w) && !_inputManager.isKeyPressed(SDLK_a) && _inputManager.isKeyPressed(SDLK_s) && !_inputManager.isKeyPressed(SDLK_d)){
		_camera.move(-SPEED, deltaTime);
		for( int i = 0; i < _terrain.size(); i++)
		{
			if(_camera.checkTerrainCollision(_terrain[i])) { _camera.move(SPEED, deltaTime); }
		}	
	}
	if (!_inputManager.isKeyPressed(SDLK_w) && _inputManager.isKeyPressed(SDLK_a) && !_inputManager.isKeyPressed(SDLK_s) && !_inputManager.isKeyPressed(SDLK_d)){
		_camera.strafe(-SPEED, deltaTime);
		for( int i = 0; i < _terrain.size(); i++)
		{
			if(_camera.checkTerrainCollision(_terrain[i])) { _camera.strafe	(SPEED, deltaTime); }
		}
	}
	if (!_inputManager.isKeyPressed(SDLK_w) && !_inputManager.isKeyPressed(SDLK_a) && !_inputManager.isKeyPressed(SDLK_s) && _inputManager.isKeyPressed(SDLK_d)){
		_camera.strafe(SPEED, deltaTime);
		for( int i = 0; i < _terrain.size(); i++)
		{
			if(_camera.checkTerrainCollision(_terrain[i])) { _camera.strafe(-SPEED, deltaTime); }
		}
	}
	if (_inputManager.isKeyPressed(SDLK_w) && _inputManager.isKeyPressed(SDLK_a) && !_inputManager.isKeyPressed(SDLK_s) && !_inputManager.isKeyPressed(SDLK_d))
	{
		_camera.move(SPEED/2, deltaTime); _camera.strafe(-SPEED/2, deltaTime);
		for( int i = 0; i < _terrain.size(); i++)
		{
			if(_camera.checkTerrainCollision(_terrain[i])) { _camera.move(-SPEED/2, deltaTime); _camera.strafe(SPEED/2, deltaTime); }
		}
	}
	if (_inputManager.isKeyPressed(SDLK_w) && !_inputManager.isKeyPressed(SDLK_a) && !_inputManager.isKeyPressed(SDLK_s) && _inputManager.isKeyPressed(SDLK_d))
	{
		_camera.move(SPEED/2, deltaTime); _camera.strafe(SPEED/2, deltaTime);
		for( int i = 0; i < _terrain.size(); i++)
		{
			if(_camera.checkTerrainCollision(_terrain[i])) { _camera.move(-SPEED/2, deltaTime); _camera.strafe(-SPEED/2, deltaTime); }
		}
	}
	if (!_inputManager.isKeyPressed(SDLK_w) && _inputManager.isKeyPressed(SDLK_a) && _inputManager.isKeyPressed(SDLK_s) && !_inputManager.isKeyPressed(SDLK_d))
	{
		_camera.move(-SPEED/2, deltaTime); _camera.strafe(-SPEED/2, deltaTime);
		for( int i = 0; i < _terrain.size(); i++)
		{
			if(_camera.checkTerrainCollision(_terrain[i])) { _camera.move(SPEED/2, deltaTime); _camera.strafe(SPEED/2, deltaTime); }
		}
	}
	if (!_inputManager.isKeyPressed(SDLK_w) && !_inputManager.isKeyPressed(SDLK_a) && _inputManager.isKeyPressed(SDLK_s) && _inputManager.isKeyPressed(SDLK_d))
	{
		_camera.move(-SPEED/2, deltaTime); _camera.strafe(SPEED/2, deltaTime);
		for( int i = 0; i < _terrain.size(); i++)
		{
			if(_camera.checkTerrainCollision(_terrain[i])) { _camera.move(-SPEED/2, deltaTime); _camera.strafe(-SPEED/2, deltaTime); }
		}
	}
	if (_inputManager.isKeyPressed(SDLK_SPACE)){
		if(!_camera._jumping && !_camera._falling){
			_camera.jump(1.0f, deltaTime);		
		}
	}
	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)){
		if(_shotPower <= 10.0f){
			_shotPower += 0.10f;
		}
 	}
 	if (!_inputManager.isKeyPressed(SDL_BUTTON_LEFT) && _shotPower > 0)
 	{
 		if(_shotTimer >= _SHOTSPEED){
			_shotTimer = 0.0f;
			glm::vec3 displacement = glm::vec3(_camera.getDirection());
			normalize(displacement);
			displacement *= 3;
			glm::vec3 position = glm::vec3(_camera.getPosition() + displacement);
			glm::vec3 direction = glm::vec3(_camera.getDirection());	
			normalize(direction);
			_arrows.emplace_back(position, direction, _shotPower, 1.0f, 250, "NONE");	
			std::cout << "Shot Speed: " << _shotPower << std::endl;	
		} 		
 		_shotPower = 0.0f;
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

void Game::processPauseInput()
{
	SDL_Event evnt;

	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evnt)) 
	{
		switch (evnt.type) 
		{
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
	if (_inputManager.isKeyPressed(SDLK_ESCAPE)){
		_paused = true;
	}
	if (!_inputManager.isKeyPressed(SDLK_ESCAPE) && _paused){
		_gameState = GameState::PLAY; 
		_paused = false;
	}

	//reset the mouse position
	SDL_WarpMouseInWindow(_window.getWindow(), _screenWidth/2, _screenHeight/2);

}

void Game::drawGame()
{
	// Setting the base depth to 1.0
	glClearDepth(1.0);

	// Clearing the Colour and Depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Enable the shader
	_colorProgram.use();

	//setting the texture location inside the fragment shader
	glUniform1i(_colorProgram.getUniformLocation("mySampler"), 0);

	//set the camera matrix
	GLuint pLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 projectionMatrix = _camera.getProjectionMatrix();
	glm::mat4 viewMatrix = _camera.getViewMatrix();
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 cameraMatrix = projectionMatrix * viewMatrix * modelMatrix;

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	//creating and drawing a cube
	_cube.init(0.0f, 10.0f, 0.0f, 5.0f, "../src/Textures/NeHe.bmp");
	_cube.draw();

	//Adding a floor to the scene
	_floor.init(_floorSize);
	_floor.draw();

	//Updating the melee agents
	for (int i = 0; i < _meleeAgents.size(); i++)
	{
		_meleeAgents[i].init();
		_meleeAgents[i].draw();
	}

	//Adding some "terrain"
	for (int i = 0; i < _terrain.size(); i++)
	{
		_terrain[i].init();
		_terrain[i].draw();
	}

	//Drawing the arrows into the scene
	for (int i = 0; i < _arrows.size(); i++)
	{
		_arrows[i].init();
		_arrows[i].draw();
	}

	//disable the shaders
	_colorProgram.unuse();

	// Swap the buffers and draw everything onto the screencd 
	_window.swapBuffer();
}

void Game::generateTerrain(int blocks, int terrainLevel, float size, float floorSize)
{
	for (int i = 0; i < blocks; i++ )
	{
		//dublicate position
		bool dupe = false;
		int floorSize2 = 2*floorSize;
		//Randomize some coordinates
		int rand_x = rand() % floorSize2 - floorSize;
		int rand_z = rand() % floorSize2 - floorSize;
		//Create the position vector
		glm::vec3 pos = glm::vec3(rand_x, size * terrainLevel, rand_z);

		//If there are no other pieces of terrain create the first block
		if( i == 0){
			_terrain.emplace_back(pos, size);			
		} else {
			for (int j = 0; j < _terrain.size(); j++)
			{
				if(pos.x - size < _terrain[j]._position.x + size && pos.x + size > _terrain[j]._position.x - size &&
					pos.y - size < _terrain[j]._position.y + size && pos.y + size > _terrain[j]._position.y - size && 
					pos.z - size < _terrain[j]._position.z + size && pos.z + size > _terrain[j]._position.z - size)
				{
					std::cout << "Spawning inside!!" << std::endl;
					dupe = true;
				}
			}
			if(!dupe) 
			{
				_terrain.emplace_back(pos, size);
			} else {
				i--;
			}
		}
	}
}