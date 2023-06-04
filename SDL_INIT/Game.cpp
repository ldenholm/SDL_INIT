#include "Game.h"
#include <vector>


// Public Members
// CTOR
Game::Game()
{
	mIsRunning = true;
	mWindow = NULL;
	mRenderer = NULL;
}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("Error initializing SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("Early Days v1", 200, 200, 1024, 768, 0);
	if (!mWindow)
	{
		SDL_Log("Error creating windows: %s", SDL_GetError());
		return false;
	}

	// Enable GPU rendering and vsync
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("Error initializing renderer: %s", SDL_GetError());
		return false;
	}

	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown()
{
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

// Private Members

void Game::ProcessInput()
{
	// Handle events in the queue:
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
}

void Game::UpdateGame()
{

}

void Game::GenerateOutput()
{
	/*
	* Graphics are an output, here are the steps:
	* - clear the back buffer to a color (the game's current buffer).
	* - draw the entire scene on the back buffer.
	* - swap the front and back buffers for display to show new scene.
	*/

	// blue w/ 100% opacity.
	SDL_SetRenderDrawColor(mRenderer, 237, 194, 242, 255);
	SDL_RenderClear(mRenderer);
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	const int thickness = 15;
	// Create walls
	std::vector<SDL_Rect> walls{ {0, 0, 1024, thickness}, {0, (768 - thickness), 1024, thickness}, {0, 0, thickness, 768}, {(1024 - thickness), 0, thickness, 768} };
	for (SDL_Rect wall : walls)
	{
		SDL_RenderFillRect(mRenderer, &wall);
	}
	
	SDL_RenderPresent(mRenderer);
}