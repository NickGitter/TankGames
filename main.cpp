
#include <SDL.h>
#include <SDL_image.h>
#include <Windows.h>
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <string>
#include "Game.h"
#undef main

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	if (TheGame::Instance()->init("Tank's Game", 50, 50, 640, 480, 0))
		TheGame::Instance()->run();
	else {
		std::cout << "ERROR\n";
		getchar();
	}
	return 0;
}