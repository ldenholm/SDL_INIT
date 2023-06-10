#ifndef __Game__
#define __Game__

#include <SDL.h>

class Game
{
public:
	Game();
	~Game();
	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void render();
	void update();
	void handleEvents();
	void clean();
	bool running() { return mIsRunning; }
	static const int SCREEN_WIDTH = 1024;
	static const int SCREEN_HEIGHT = 768;

private:
	bool mIsRunning;
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;

};

#endif // !__Game__