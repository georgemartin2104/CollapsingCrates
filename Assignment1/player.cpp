#include "player.h"



player::player()
{
}


player::~player()
{
}

void player::initPlayer()
{
	newX = rand() % 50;
	newX = newX * 16;
	playerRect.x = newX;
	playerRect.y = 568;
	playerRect.w = 16;
	playerRect.h = 32;

	playerFrame.x = 0;
	playerFrame.y = 0;
	playerFrame.h = 32;
	playerFrame.w = 16;
}

void player::updatePlayer()
{
	if (movingLeft == true)
	{
		if (playerRect.x >= 0)
		{
			playerRect.x--;
			playerRect.x--;
			playerFrame.x = 0;
			playerFrame.y = 0;
			playerFrame.h = 32;
			playerFrame.w = 16;
		}
	}
	if (movingRight == true)
	{
		if (playerRect.x <= 783)
		{
			playerRect.x++;
			playerRect.x++;
			playerFrame.x = 17;
			playerFrame.y = 0;
			playerFrame.h = 32;
			playerFrame.w = 16;
		}
	}
	if (jumpKeyPressed == true)
	{
		if (counter == 0)
		{
			goingUp = true;
		}
		if (goingUp == true)
		{
			if (counter < 26)
			{
				playerRect.y--;
				playerRect.y--;
				counter++;
				counter++;
			}
			if (counter < 32)
			{
				if (counter >= 26)
				{
					playerRect.y--;
					counter++;
				}
			}
			if (counter >= 32)
			{
				goingUp = false;
			}
		}
		if (goingUp == false)
		{
			if (counter >= 32)
			{
				counter++;
			}
			if (counter == 38)
			{
				counter = 31;
			}
			if (counter < 32)
			{
				if (counter >= 26)
				{
					playerRect.y++;
					counter--;
				}
			}
			if (counter < 26)
			{
				playerRect.y++;
				playerRect.y++;
				counter--;
				counter--;
			}
			if (counter <= 0)
			{
				jumpKeyPressed = false;
				counter = 0;
			}
		}
	}
	playerTop = playerRect.y;
	playerLeft = playerRect.x;
	playerRight = playerRect.x + playerRect.w;
	playerBottom = playerRect.y + playerRect.h;
}

int player::getPlayerTop()
{
	return playerTop;
}
int player::getPlayerLeft()
{
	return playerLeft;
}
int player::getPlayerRight()
{
	return playerRight;
}
int player::getPlayerBottom()
{
	return playerBottom;
}
