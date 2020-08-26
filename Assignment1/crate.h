#pragma once
#ifndef crateFile
#define crateFile

#include <random>
#include <iostream>
#include <time.h>
#include "SDL.h"
#include "player.h"
class crate
{
public:
	crate();
	~crate();

	SDL_Rect crateLocations[1875];

	void createCrate();
	void updateCrates();
	int counter = 0;
	bool didPlayerDie = false;

private:
	SDL_Rect dstRect;

	SDL_Rect topCrates[1875];

	bool hasLogged[1875];
	int previousSpawn = 0;
	int newX = 0;
	player* playerPointer = new player;
	SDL_Rect playerLocation = playerPointer->playerRect;
	int playerTop = playerPointer->playerRect.y;
	int playerLeft = playerPointer->playerRect.x;
	int playerRight = playerPointer->playerRect.x + playerPointer->playerRect.w;
	int playerBottom = playerPointer->playerRect.y + playerPointer->playerRect.h;
	
};

#endif