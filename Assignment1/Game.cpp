#include "Game.h"

SDL_Texture* crateTex;
SDL_Texture* playerTex;
SDL_Texture* menu1Tex;
SDL_Texture* menu2Tex;

Game::Game()
{

}


Game::~Game()
{

}

//Initialise the game
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	//Allows for changing on flags e.g. fullscreen, resizable
	int flags = SDL_WINDOW_RESIZABLE;

	// Create a random seed for the rand function in crate.h
	srand(time(NULL));

	//Check for SDL to be initalised, if not initialise SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		//print in console that sdl has been initalised, later to be put in a log file
		std::cout << "SDL Initialised!" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			//print in console that a window has been initalised, later to be put in a log file
			std::cout << "Window created!" << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer)
		{
			//Set colour to white
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			//print in console that a renderer has been initalised, later to be put in a log file
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;
	}
	else {
		//If SDL is not initalised sets is running to false
		isRunning = false;
	}
	IMG_Init(SDL_INIT_EVERYTHING);

	SDL_Surface* tmpSurface = IMG_Load("./content/crateTexture.png");
	crateTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	SDL_Surface* playerTmpSurface = IMG_Load("./content/playerTexture.png");
	playerTex = SDL_CreateTextureFromSurface(renderer, playerTmpSurface);
	SDL_FreeSurface(playerTmpSurface);
	SDL_Surface* menu1TmpSurface = IMG_Load("./content/menuTexture1.png");
	menu1Tex = SDL_CreateTextureFromSurface(renderer, menu1TmpSurface);
	SDL_FreeSurface(menu1TmpSurface);
	SDL_Surface* menu2TmpSurface = IMG_Load("./content/menuTexture2.png");
	menu2Tex = SDL_CreateTextureFromSurface(renderer, menu2TmpSurface);
	SDL_FreeSurface(menu2TmpSurface);
	SDL_Rect menuButton1{ 100, 0, 100, 50 };
	SDL_Rect menuButton2{ 200, 0, 100, 50 };
	SDL_Rect menuLocation1{ 350, 200, 100, 50 };
	SDL_Rect menuLocation2{ 350, 400, 100, 50 };

	bool gameStarted = false;

	while (!gameStarted)
	{
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, menu1Tex, &menuButton1, &menuLocation1);
		SDL_RenderCopy(renderer, menu2Tex, &menuButton2, &menuLocation2);
		SDL_Event event;
		SDL_PollEvent(&event);
		bool menuChanged = false;
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
				case SDLK_s:
					menuButton1.x = 0;
					if (menuButton2.x == 200)
					{
						menuButton2.x = 300;
					}
					if (menuButton2.x == 0)
					{
						menuButton2.x = 100;
					}
					break;
				case SDLK_w:
					menuButton1.x = 100;
					if (menuButton2.x == 300)
					{
						menuButton2.x = 200;
					}
					if (menuButton2.x == 100)
					{
						menuButton2.x = 0;
					}
					break;
				case SDLK_a:
					if (menuButton2.x == 300)
					{
						menuChanged = true;
						menuButton2.x = 100;
						fullscreen = true;
					}
					if (menuButton2.x == 100 && menuChanged == false)
					{
						menuButton2.x = 300;
						fullscreen = false;
					}
					break;
				case SDLK_d:
					if (menuButton2.x == 300)
					{
						menuChanged = true;
						menuButton2.x = 100;
						fullscreen = true;
					}
					if (menuButton2.x == 100 && menuChanged == false)
					{
						menuButton2.x = 300;
						fullscreen = false;
					}
					break;
				case SDLK_SPACE:
					if (menuButton1.x == 100)
					{
						gameStarted = true;
					}
					break;
			}
			break;
		}
		SDL_RenderPresent(renderer);
	}

	//Example of changing to fullscreen
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			//print in console that a window has been initalised, later to be put in a log file
			std::cout << "Window created!" << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer)
		{
			//Set colour to white
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			//print in console that a renderer has been initalised, later to be put in a log file
			std::cout << "Renderer created!" << std::endl;
		}
		SDL_Surface* tmpSurface = IMG_Load("./content/crateTexture.png");
		crateTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
		SDL_FreeSurface(tmpSurface);
		SDL_Surface* playerTmpSurface = IMG_Load("./content/playerTexture.png");
		playerTex = SDL_CreateTextureFromSurface(renderer, playerTmpSurface);
		SDL_FreeSurface(playerTmpSurface);
	}


	playerManager->initPlayer();
}

void Game::input()
{
	//Creates an event manager
	SDL_Event event;
	SDL_PollEvent(&event);
	//Checks event type
	switch (event.type)
	{
	//If event type is that SDL has been quit, sets isRunning to false
	case SDL_QUIT:
		isRunning = false;
		break;

	case SDL_KEYDOWN:

		switch (event.key.keysym.sym)
		{
		case SDLK_d:
			playerManager->movingRight = true;
			if (hasLogged == false)
			{
				std::cout << "D key pressed!" << std::endl;
				hasLogged = true;
			}
			break;

		case SDLK_a:
			playerManager->movingLeft = true;
			if (hasLogged == false)
			{
				std::cout << "A key pressed!" << std::endl;
				hasLogged = true;
			}
			break;

		case SDLK_w:
			playerManager->jumpKeyPressed = true;
			if (hasLogged == false)
			{
				std::cout << "W key pressed!" << std::endl;
				hasLogged = true;
			}
			break;
		}
		break;

	case SDL_KEYUP:

		switch (event.key.keysym.sym)
		{
		case SDLK_d:
			playerManager->movingRight = false;
			std::cout << "D key released!" << std::endl;
			hasLogged = false;
			break;

		case SDLK_a:
			playerManager->movingLeft = false;
			std::cout << "A key released!" << std::endl;
			hasLogged = false;
			break;

		case SDLK_w:
			std::cout << "W key released!" << std::endl;
			hasLogged = false;
			break;
		}
		break;

	default:
		break;
	}
	if (firstInput == true)
	{
		std::cout << "Input running correctly!" << std::endl;
		firstInput = false;
	}
}

void Game::update()
{
	playerManager->updatePlayer();
	crateManager->updateCrates();
	createCrateCounter++;
	totalTimeElapsed++;
	if (createCrateCounter == secondsForCrateSpawn * 60)
	{
		crateManager->createCrate();
		createCrateCounter = 0;
	}
	if (totalTimeElapsed == 15 * 60)
	{
		secondsForCrateSpawn = 0.5;
	}
	if (totalTimeElapsed == 30 * 60)
	{
		secondsForCrateSpawn = 0.25;
	}
	if (totalTimeElapsed == 45 * 60)
	{
		secondsForCrateSpawn = 0.15;
	}
	if (firstUpdate == true)
	{
		std::cout << "Update running correctly!" << std::endl;
		firstUpdate = false;
	}
	if (totalTimeElapsed == 3600)
	{
		std::cout << "You WIN!" << std::endl;
		isRunning = false;
	}
	/*if (crateManager->didPlayerDie == true)
	{
		std::cout << "You DIED!" << std::endl;
		isRunning = false;
	}*/
}

void Game::render()
{
	//Initialise SDL2_Image
	//IMG_Init(SDL_INIT_EVERYTHING);

	//Load in textures
	
	//Quit SDL2_Image
	//IMG_Quit();
	//Clears the screen
	SDL_RenderClear(renderer);
	//SDL_RenderCopy(renderer, crateTex, NULL, NULL);
	SDL_RenderCopy(renderer, playerTex, &playerManager->playerFrame, &playerManager->playerRect);
	for (int i = 0; i < crateManager->counter; i++)
	{
		SDL_RenderCopy(renderer, crateTex, NULL, &crateManager->crateLocations[i]);
	}
	//Presents things that have been rendered to the screen
	SDL_RenderPresent(renderer);
	if (firstRender == true)
	{
		std::cout << "Render running correctly!" << std::endl;
		firstRender = false;
	}
}

void Game::clean()
{
	//Destroys the window
	SDL_DestroyWindow(window);
	//Destroys the renderer
	SDL_DestroyRenderer(renderer);
	//Quits SDL
	SDL_Quit();
	//Prints in console that the game was cleaned, to be moved to a log file
	std::cout << "Game Cleaned!" << std::endl;
}