#ifndef __Game__
#define __Game__

#include <SDL.h>

class Game
{
public:
	Game();
	~Game();
	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void render();
	void update();
	void handleEvents();
	void clean();
	bool running() { return mIsRunning; }
	static const int SCREEN_WIDTH = 2048;
	static const int SCREEN_HEIGHT = 1080;

private:
	bool mIsRunning;
	Uint32 mTicksCount;
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	SDL_Texture* mTexture;
	SDL_Rect mSourceRect;
	SDL_Rect mDestRect;
};

#endif // !__Game__