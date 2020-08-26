#pragma once
#ifndef GameFile
#define GameFile
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "crate.h"
#include "player.h"

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void input();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; };
	bool playerDeath = false;

private:
	bool isRunning;
	SDL_Window *window;
	SDL_Renderer *renderer;

	int createCrateCounter = 0;
	int totalTimeElapsed = 0;
	double secondsForCrateSpawn = 1;
	crate* crateManager = new crate;
	player* playerManager = new player;
	bool firstInput = true;
	bool firstUpdate = true;
	bool firstRender = true;
	bool hasLogged = false;
};

#endif