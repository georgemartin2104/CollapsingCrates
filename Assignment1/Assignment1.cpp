#pragma once
#include <iostream>
#include <string>
#include "SDL.h"
#include "Game.h"
#include "GM_Timer.h"

Game *game = nullptr;

int main(int argc, char *argv[])
{
	//Creates a new game instance
	game = new Game();

	//Creates an object for an fps limit
	GM_Timer fpsTimer;
	const int fps = 60;
	const int DELTA_TIME = 1000 / fps;

	//Launches the game init function, tags can be changed here
	game->init("George Martin, CGP2011M Games Programming, MAR17644747, Collapsing Crates", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	while (game->running())
	{
		fpsTimer.resetTicksTimer();

		game->input();
		game->update();
		game->render();

		if (fpsTimer.getTicks() < DELTA_TIME)
		{
			SDL_Delay(DELTA_TIME - fpsTimer.getTicks());
		}
	}
	game->clean();
	return 0;
}

