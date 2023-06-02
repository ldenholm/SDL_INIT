#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// GLOBALS (nb. Allowing this anti pattern due to this being a single file program)
SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* ground_tiles = NULL;

// Methods

bool init()
{
	bool success = false;
	if (!(SDL_Init(SDL_INIT_VIDEO) < 0))
	{
		window = SDL_CreateWindow("Rendering an img via CPU", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		success = true;
		if (window != NULL)
		{
			screenSurface = SDL_GetWindowSurface(window);
		}
		else
		{
			printf("SDL Window was not created %s", SDL_GetError());
			success = false;
		}	
	}
	else
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	
	return success;
}

// Load bmp
bool loadMedia()
{
	bool success = false;
	char tile_path[] = "media/ground_tiles.bmp";
	ground_tiles = SDL_LoadBMP(tile_path);
	if (ground_tiles != NULL)
	{
		success = true;
	}
	else
	{
		printf("Unable to load image at path: %s", tile_path);
	}
	return success;
}

// Dalloc & Shutdown SDL
void closeSDL()
{
	SDL_FreeSurface(ground_tiles);
	ground_tiles = NULL;
	
	// this also destroys the screen surface
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit;
}

int main( int argc, char* args[] )
{
	//Initialize SDL
	if (!init())
	{
		printf("Failed to initialize: %s", SDL_GetError());
	}

	// Load media
	if (!loadMedia())
	{
		printf("Failed to load graphics: %s", SDL_GetError());
	}

	bool quit = false;

	SDL_Event e;

	// Game Loop:
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			// Events are pushed to event stack and processed by polling the event queue.
			// We ignore all but events typeof(SDL_QUIT) and process these by setting quit flag to true:
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		// Blit the tiles_surface(source) onto the screen_surface(target)
		SDL_BlitSurface(ground_tiles, NULL, screenSurface, NULL);

		// Update the window
		SDL_UpdateWindowSurface(window);
	}

	closeSDL();
	
	return 0;
}
