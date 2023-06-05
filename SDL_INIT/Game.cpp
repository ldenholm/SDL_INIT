#include "Game.h"


// Public Members
// CTOR
Game::Game()
{
	mIsRunning = true;
	mWindow = NULL;
	mRenderer = NULL;
	mBallPos.x = 512;
	mBallPos.y = 384;
	mPaddlePos.x = 0;
	mPaddlePos.y = 384;
	mTicksCount = 0;
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
	// frame limiting ensuring ~16.6ms is used per frame:
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
	
	// Create walls
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	const int thickness = 15;
	SDL_Rect wall = { 0, 0, 1024, thickness };
	SDL_RenderFillRect(mRenderer, &wall);
	// bottom
	wall.y = (768 - thickness);
	SDL_RenderFillRect(mRenderer, &wall);
	// right
	wall.x = (1024 - thickness);
	wall.y = 0;
	wall.w = thickness;
	wall.h = 768;
	SDL_RenderFillRect(mRenderer, &wall);

	// Draw Ball (for x&y / by half of thickness to account for its own width/height.
	SDL_Rect ball = {
		static_cast<int>(mBallPos.x - thickness / 2),
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);

	// Draw player1 paddle
	SDL_Rect lPlayerPaddle = {
		0,
		static_cast<int>(mPaddlePos.y - 64),
		thickness,
		128
	};
	SDL_RenderFillRect(mRenderer, &lPlayerPaddle);

	SDL_RenderPresent(mRenderer);
}