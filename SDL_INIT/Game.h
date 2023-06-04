#include <SDL.h>
class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

private:
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	bool mIsRunning;
	
	// Helper functions for game loop:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
};

