#include "Game.h"
#include <SDL_image.h>
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

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("Failed to init. Error: %s", SDL_GetError());
		return false;
	}

	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
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

	// Init PNG Loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_Image Error: %s\n", IMG_GetError());
		return false;
	}

	SDL_Log("Renderer success!");
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	SDL_Log("Initialization completed succesfully");
	mIsRunning = true;

	// loading assets:
	SDL_Surface* pTempSurface = IMG_Load("media/side_walk.png");
	if (!pTempSurface)
	{
		printf("Image load error.\n %s", IMG_GetError());
	}
	mTexture = SDL_CreateTextureFromSurface(mRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);
	// set the x & y offset
	mSourceRect.x = mDestRect.x = 0;
	mSourceRect.y = mDestRect.y = 0;
	mSourceRect.w = mSourceRect.h = 64;
	mDestRect.w = mSourceRect.w;
	mDestRect.h = mSourceRect.h;

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
	// animate viking:
	mSourceRect.x = mSourceRect.w * int(((SDL_GetTicks() / 100) % 4));
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
	SDL_RenderCopy(mRenderer, mTexture, &mSourceRect, &mDestRect);
	SDL_RenderPresent(mRenderer);
}