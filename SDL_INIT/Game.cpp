#include "Game.h"

// Globals

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int thickness = 15;
const float paddleH = 128.0f;

// Public Members

Game::Game()
{
	mIsRunning = true;
	mWindow = NULL;
	mRenderer = NULL;
	mBallPos.x = 512.0f;
	mBallPos.y = 384.0f;
	mPaddlePos.x = 0.0f;
	mPaddlePos.y = 384.0f;
	mTicksCount = 0;
	mLPaddleDir = 0;
}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("Error initializing SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("Early Days v1", 200, 200, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
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
	// Capture keyboard state
	const Uint8* state = SDL_GetKeyboardState(NULL);

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

	// Handle Paddle movement lPlayer
	HandleLPaddleDirection(state);

	// Handle escape
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
	HandleLPaddleMovement(deltaTime);
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

void Game::HandleLPaddleDirection(const Uint8* kbState)
{
	mLPaddleDir = 0;
	if (kbState[SDL_SCANCODE_W])
	{
		mLPaddleDir -= 1; // upwards aka -y
	}
	if (kbState[SDL_SCANCODE_S])
	{
		mLPaddleDir +=  1; // down aka +y
	}
}

void Game::HandleLPaddleMovement(float deltaTime)
{
	if (mLPaddleDir != 0)
	{
		// add scalar of 300 pixels p/sec, note delTime is already in s
		mPaddlePos.y += (mLPaddleDir * 300.0f * deltaTime);
		// Add boundary conditions so the paddle does not move off screen:
		// If top of paddle reaches y = 0 then prevent further upwards movement
		// pad.y is middle of paddle so y must be less than half paddles height plus thickness of top border:
	}
	if (mPaddlePos.y < (paddleH / 2.0f + thickness))
	{
		// stop movement
		mPaddlePos.y = (paddleH / 2.0f + thickness);
	}
	else if (mPaddlePos.y > (SCREEN_HEIGHT - thickness - paddleH / 2.0f))
	{
		mPaddlePos.y = (SCREEN_HEIGHT - thickness - paddleH / 2.0f);
	}
}
