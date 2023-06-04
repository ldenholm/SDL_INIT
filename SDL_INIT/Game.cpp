#include "Game.h"


// Public Members
// CTOR
Game::Game()
{
	mIsRunning = true;
	mWindow = NULL;
}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("Error initializing SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("Early Days v1", 200, 200, 1920, 1080, 0);
	if (!mWindow)
	{
		SDL_Log("Error creating windows: %s", SDL_GetError());
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

}