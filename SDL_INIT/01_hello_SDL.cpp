#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

// Enums
enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

// GLOBALS (nb. Allowing this anti pattern due to this being a single file program)

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* ground_tiles = NULL;
// Maps surfaces to key press events
SDL_Surface* keyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
// Current rendered image
SDL_Surface* currentSurface = NULL;

// Methods

bool init()
{
	bool success = false;
	if (!(SDL_Init(SDL_INIT_VIDEO) < 0))
	{
		window = SDL_CreateWindow("Rendering an img via CPU", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		success = true;
		if (window)
		{
			screenSurface = SDL_GetWindowSurface(window);
			// Initialize png loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL Img lib did not initialize. SDL Error: %s\n", IMG_GetError());
				success = false;
			}
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

// Load Individual Image
SDL_Surface* loadSurface(std::string path)
{
	SDL_Surface* optimizedSurface = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (!loadedSurface)
	{
		printf("Unable to load image: %s\n SDL Error: %s", path.c_str(), SDL_GetError());
	}
	else
	{
		optimizedSurface = SDL_ConvertSurface(loadedSurface, screenSurface->format, 0);
		if (!optimizedSurface)
		{
			printf("Image stretch SDL Error: %s", SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}
	return optimizedSurface;
}

// Load assets
bool loadMedia()
{
	bool success = true;
	std::string path = "media/ground_tiles.bmp";

	// Load Default
	keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface(path);
	if (!keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT])
	{
		success = false;
		printf("Unable to load image: %s", path.c_str());
	}

	// KeyUp
	path = "media/avatar.bmp";
	keyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface(path);
	if (!keyPressSurfaces[KEY_PRESS_SURFACE_UP])
	{
		success = false;
		printf("Unable to load image: %s", path.c_str());
	}

	// KeyDown
	path = "media/attack.png";
	keyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface(path);
	if (!keyPressSurfaces[KEY_PRESS_SURFACE_DOWN])
	{
		success = false;
		printf("Unable to load image: %s", path.c_str());
	}

	// KeyLeft
	path = "media/walk_west.bmp";
	keyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface(path);
	if (!keyPressSurfaces[KEY_PRESS_SURFACE_LEFT])
	{
		success = false;
		printf("Unable to load image: %s", path.c_str());
	}

	// KeyRight
	path = "media/walk_east.bmp";
	keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface(path);
	if (!keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT])
	{
		success = false;
		printf("Unable to load image: %s", path.c_str());
	}

	return success;
}

// Dalloc & Shutdown SDL
void closeSDL()
{
	
	for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++)
	{
		SDL_FreeSurface(keyPressSurfaces[i]);
		keyPressSurfaces[i] = NULL;
	}

	SDL_FreeSurface(currentSurface);
	currentSurface = NULL;
	
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

	// Default surface
	currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

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
			else if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_UP:
					currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_UP];
					break;

				case SDLK_DOWN:
					currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
					break;

				case SDLK_LEFT:
					currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
					break;

				case SDLK_RIGHT:
					currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
					break;

				default:
					currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
					break;
				}
			}
		}

		// Stretch Rectangle
		SDL_Rect stretchRect{};
		stretchRect.x = 0;
		stretchRect.y = 0;
		stretchRect.w = SCREEN_WIDTH;
		stretchRect.h = SCREEN_HEIGHT;

		SDL_BlitScaled(currentSurface, NULL, screenSurface, &stretchRect);

		// Update the window
		SDL_UpdateWindowSurface(window);
	}

	closeSDL();
	
	return 0;
}
