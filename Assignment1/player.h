#pragma once
#ifndef playerFile
#define playerFile

#include <random>
#include <time.h>
#include <iostream>
#include "SDL.h"

class player
{
public:
	player();
	~player();

	void initPlayer();
	void updatePlayer();

	SDL_Rect playerRect;
	SDL_Rect playerFrame;

	bool movingLeft = false;
	bool movingRight = false;
	bool jumpKeyPressed = false;
	bool goingUp = false;

	int playerTop = 0;
	int playerLeft = 0;
	int playerRight = 0;
	int playerBottom = 0;

	int getPlayerTop();
	int getPlayerLeft();
	int getPlayerRight();
	int getPlayerBottom();

	int counter = 0;


private:
	int newX = 0;
};

#endif