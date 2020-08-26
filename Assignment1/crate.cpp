#include "crate.h"



crate::crate()
{
}


crate::~crate()
{
}

void crate::createCrate()
{	
	// If there is space on screen
	if (counter < 1875)
	{
		// Check if the previous spawn location is the same as the new spawn location
		while (previousSpawn == newX)
		{
			// Create a new random location at the top of the screen (times by the width of the crate)
			newX = rand() % 50;
			newX = newX * 16;
		}
		previousSpawn = newX;
		// Create a rectangle for the crate with the new location
		dstRect.x = newX;
		dstRect.y = 1;
		dstRect.w = 16;
		dstRect.h = 16;
		// Store the SDL_Rect in the crates array
		crateLocations[counter] = dstRect;
		// Increase the counter of number of crates
		counter++;
		// Outputs to console the new number of crates
		std::cout << "Number of crates: " << counter << std::endl;
	}
}

void crate::updateCrates()
{
	for (int i = 0; i < counter; i++)
	{
		// Checks if the crate is stacked on top of another crate
		bool crateStacked = false;
		// Represents hitbox for each side of the crate
		int thisCrateTop = 0;
		int thisCrateLeft = 0;
		int thisCrateRight = 0;
		int thisCrateBottom = 0;
		// Used to store the crate being updated from the array
		SDL_Rect updatingRect;
		// Used to check for collision, then replaces the crate at the top of the pile in the array
		SDL_Rect checkCrate;

		// Gets the current crate being updated
		updatingRect = crateLocations[i];
		// Assigns hitboxes
		thisCrateTop = updatingRect.y;
		thisCrateLeft = updatingRect.x;
		thisCrateRight = updatingRect.x + updatingRect.w;
		thisCrateBottom = updatingRect.y + updatingRect.h;

		// If the crate is at the bottom of the screen, stop moving
		if (thisCrateBottom == 600)
		{
			topCrates[thisCrateLeft] = updatingRect;

			if (hasLogged[i] != true)
			{
				// Outputs to the console that the crate has collided with another crate
				std::cout << "Crate has collided with the floor" << std::endl;
				hasLogged[i] = true;
			}
		}

		// Sets the check crate to the highest crate below the moving crate
		checkCrate = topCrates[thisCrateLeft];
		if (thisCrateLeft == checkCrate.x)
		{
			// If the bottom of the moving crate has collided with the top of the highest crate
			if (thisCrateBottom == checkCrate.y)
			{
				// Tell the crate it is stacked
				crateStacked = true;
				
				// Sets the once moving crate to the top crate and tells the below crate to stop checking for collision
				topCrates[thisCrateLeft] = updatingRect;
				if (hasLogged[i] != true)
				{
					hasLogged[i] = true;
					// Outputs to console that the crate has collided with another crate
					std::cout << "Crate has collided with another crate!" << std::endl;
				}
			}
		}

		// If the crate has not collided with the floor or another crate, move the crate down
		if (crateStacked == false && thisCrateBottom != 600)
		{
			//Update player locations
			playerTop = playerPointer->getPlayerTop();
			playerLeft = playerPointer->getPlayerLeft();
			playerRight = playerPointer->getPlayerRight();
			playerBottom = playerPointer->getPlayerBottom();

			/*//Check for collision with player
			if (thisCrateTop == playerTop || thisCrateLeft == playerTop || thisCrateRight == playerTop || thisCrateBottom == playerTop || thisCrateTop == playerLeft || thisCrateLeft == playerLeft || thisCrateRight == playerLeft || thisCrateBottom == playerLeft || thisCrateTop == playerRight || thisCrateLeft == playerRight || thisCrateRight == playerRight || thisCrateBottom == playerRight || thisCrateTop == playerBottom || thisCrateLeft == playerBottom || thisCrateRight == playerBottom || thisCrateBottom == playerBottom)
			{
				std::cout << "Collision detected between crate and player!" << std::endl;
				didPlayerDie = true;
			}*/
			updatingRect.y++;
			
		}
		crateLocations[i] = updatingRect;
	}
}
