#include "Game.h"
#include <iostream>

Game::Game()
{
	// init members variables
	mIsRunning = true;
	mWindow = NULL;
	mRenderer = NULL;
	mTicksCount = 0;
}

Game::~Game()
{
}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("Failed to init. Error: %s", SDL_GetError());
		return false;
	}
	
	SDL_Log("Init success!");
	mWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
	
	if (!mWindow)
	{
		SDL_Log("Failed to initialize Window");
		return false;
	}

	SDL_Log("Window success!");
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!mRenderer)
	{
		SDL_Log("Failed to initialize Renderer");
		return false;
	}

	SDL_Log("Renderer success!");
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	SDL_Log("Initialization completed succesfully");
	mIsRunning = true;
	return true;
}


void Game::update()
{
	// Frame limiting ensuring ~16.6ms is used per frame:
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	// Delta time = curentTicks - lastFrameTicks
	// getTicks gives ms so 1s/1000ms to convert to s
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	
	// limit max deltaTime so we can debug and not cause the simulation to jump:
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	
	// Update tick counts
	mTicksCount = SDL_GetTicks();

	// Todo: upd game objects in game world as a function of deltaTime
}

void Game::handleEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		default:
			break;
		}
	}
}

void Game::clean()
{
	SDL_Log("Releasing resources");
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

void Game::render()
{
	/*
	* Graphics are an output, here are the steps:
	* - clear the back buffer to a color (the game's current buffer).
	* - draw the entire scene on the back buffer.
	* - swap the front and back buffers for display to show new scene.
	*/

	SDL_RenderClear(mRenderer);
	SDL_RenderPresent(mRenderer);
}