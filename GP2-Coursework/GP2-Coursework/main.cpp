// GP2-Coursework.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Game.h"

int main()
{
	std::cout << "Loading\n" << std::endl;
	Game game;

	game.run();

	return 0;
}
