#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// GLOBALS (nb. Allowing this anti pattern due to this being a single file program)
SDL_Window* window = NULL;
SDL_Surface* screenBackground= NULL;
SDL_Surface* ground_tiles = NULL;

// Methods

bool init()
{
	bool success = false;
	if (!(SDL_Init(SDL_INIT_VIDEO) < 0))
	{
		window = SDL_CreateWindow("Rendering an img via CPU", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		success = true;
		if (!(window == NULL))
		{
			screenBackground = SDL_GetWindowSurface(window);
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

bool loadMedia()
{
	bool success = false;
	char tile_path[] = "media/ground_tiles.bmp";
	ground_tiles = SDL_LoadBMP(tile_path);
	if (!(ground_tiles == NULL))
	{
		success = true;
	}
	else
	{
		printf("Unable to load image at path: %s", tile_path);
	}
	return success;
}

// Free media & Shutdown SDL
void closeSDL();

int main( int argc, char* args[] )
{
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		
	}
	else
	{
		//Create window
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window != NULL )
		{
			//Get window surface
			screenSurface = SDL_GetWindowSurface(window);

			//Fill the surface white
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

			//Update the surface
			SDL_UpdateWindowSurface(window);

			//Hack to get window to stay up
			SDL_Event e;
			bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
		}
		else { printf("Window could not be created! SDL_Error: %s\n", SDL_GetError()); }
	}

	//Destroy window
	SDL_DestroyWindow( window );

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}
