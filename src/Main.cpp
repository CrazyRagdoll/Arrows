//#include <Windows.h> When I want to try and compile it on windows

#include <iostream>

#include "Game.h"

int main(int argc, char** argv) {	
	Game game;
	game.run();

	std::cout << "Enter any key to quit... ";
	int a;
	std::cin >> a;

	return 0;
}
