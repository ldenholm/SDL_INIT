#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

// MEMBERS

SDL_Texture* loadTexture(std::string path);
bool init();
bool loadMedia();
void cleanup();

// GLOBALS

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gCurrent = NULL;
int SCREEN_WIDTH = 1920;
int SCREEN_HEIGHT = 1080;

bool init()
{
	bool success = true;
	gWindow = SDL_CreateWindow("Render via hardware", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!gWindow)
	{
		printf("SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (!gRenderer)
		{
			printf("Rendered Init Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

			// Init PNG Loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_Image Error: %s\n", IMG_GetError());
				success = false;
			}
		}
	}
	return success;
}

SDL_Texture* loadTexture(std::string path)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (!loadedSurface)
	{
		printf("Image load error. Path: %s\n %s", path.c_str(), IMG_GetError());
	}

	// Create the texture from surface
	newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	if (!newTexture)
	{
		printf("Error creating texture: %s", SDL_GetError());
	}

	SDL_FreeSurface(loadedSurface);

	return newTexture;
}

bool loadMedia()
{
	bool success = true;
	std::string path = "media/Background_0.png";
	gCurrent = loadTexture(path);

	if (!gCurrent)
	{
		printf("Error loading: %s!\n", path.c_str());
		success = false;
	}

	return success;
}

void cleanup()
{
	SDL_DestroyTexture(gCurrent);
	gCurrent = NULL;
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	if (!init())
	{
		printf("Failed to initialize: %s", SDL_GetError());
	}

	if (!loadMedia())
	{
		printf("Failed to load graphics: %s", SDL_GetError());
	}

	bool running = true;
	SDL_Event e;

	while (running)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				running = false;
			}
		}

		SDL_RenderClear(gRenderer);
		SDL_RenderCopy(gRenderer, gCurrent, NULL, NULL);

		SDL_RenderPresent(gRenderer);
	}

	return 0;
}