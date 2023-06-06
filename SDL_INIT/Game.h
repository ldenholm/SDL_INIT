#include <SDL.h>

struct Vector2
{
	float x;
	float y;
};

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

private:
	bool mIsRunning;
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Vector2 mPaddlePos;
	Vector2 mBallPos;
	Uint32 mTicksCount;
	int mLPaddleDir;

	// Helper functions for game loop:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void HandleLPaddleDirection(const Uint8* kbState);
	void HandleLPaddleMovement(float deltaTime);
};