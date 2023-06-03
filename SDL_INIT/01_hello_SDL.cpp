//#include <SDL.h>
//#include <stdio.h>
//#include <string>
//
////Screen dimension constants
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;
//
//// Enums
//enum KeyPressSurfaces
//{
//	KEY_PRESS_SURFACE_DEFAULT,
//	KEY_PRESS_SURFACE_UP,
//	KEY_PRESS_SURFACE_DOWN,
//	KEY_PRESS_SURFACE_LEFT,
//	KEY_PRESS_SURFACE_RIGHT,
//	KEY_PRESS_SURFACE_TOTAL
//};
//
//// GLOBALS (nb. Allowing this anti pattern due to this being a single file program)
//
//SDL_Window* window = NULL;
//SDL_Surface* screenSurface = NULL;
//SDL_Surface* ground_tiles = NULL;
//// Maps surfaces to key press events
//SDL_Surface* keyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
//// Current rendered image
//SDL_Surface* currentSurface = NULL;
//
//// Methods
//
//bool init()
//{
//	bool success = false;
//	if (!(SDL_Init(SDL_INIT_VIDEO) < 0))
//	{
//		window = SDL_CreateWindow("Rendering an img via CPU", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//		success = true;
//		if (window != NULL)
//		{
//			screenSurface = SDL_GetWindowSurface(window);
//		}
//		else
//		{
//			printf("SDL Window was not created %s", SDL_GetError());
//			success = false;
//		}	
//	}
//	else
//	{
//		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
//	}
//	
//	return success;
//}
//
//// Load Individual Image
//SDL_Surface* loadSurface(std::string path)
//{
//	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
//	if (loadedSurface == NULL)
//	{
//		printf("Unable to load image at path: %s", SDL_GetError());
//	}
//	return loadedSurface;
//}
//
//// Load assets
//bool loadMedia()
//{
//	bool success = true;
//	std::string path = "media/press.bmp";
//
//	// Load Default
//	keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface(path);
//	if (keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
//	{
//		success = false;
//		printf("Unable to load image: %s", path.c_str());
//	}
//
//	// KeyUp
//	path = "media/up.bmp";
//	keyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface(path);
//	if (keyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
//	{
//		success = false;
//		printf("Unable to load image: %s", path.c_str());
//	}
//
//	// KeyDown
//	path = "media/down.bmp";
//	keyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface(path);
//	if (keyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
//	{
//		success = false;
//		printf("Unable to load image: %s", path.c_str());
//	}
//
//	// KeyLeft
//	path = "media/left.bmp";
//	keyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface(path);
//	if (keyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
//	{
//		success = false;
//		printf("Unable to load image: %s", path.c_str());
//	}
//
//	// KeyRight
//	path = "media/right.bmp";
//	keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface(path);
//	if (keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
//	{
//		success = false;
//		printf("Unable to load image: %s", path.c_str());
//	}
//
//	return success;
//}
//
//// Dalloc & Shutdown SDL
//void closeSDL()
//{
//	
//	for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i)
//	{
//		SDL_FreeSurface(keyPressSurfaces[i]);
//		keyPressSurfaces[i] = NULL;
//	}
//	
//	// this also destroys the screen surface
//	SDL_DestroyWindow(window);
//	window = NULL;
//
//	SDL_Quit;
//}
//
//
////int main( int argc, char* args[] )
////{
////	//Initialize SDL
////	if (!init())
////	{
////		printf("Failed to initialize: %s", SDL_GetError());
////	}
////
////	// Load media
////	if (!loadMedia())
////	{
////		printf("Failed to load graphics: %s", SDL_GetError());
////	}
////
////	bool quit = false;
////
////	SDL_Event e;
////
////	// Default surface
////	currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
////
////	// Game Loop:
////	while (!quit)
////	{
////		while (SDL_PollEvent(&e) != 0)
////		{
////			// Events are pushed to event stack and processed by polling the event queue.
////			// We ignore all but events typeof(SDL_QUIT) and process these by setting quit flag to true:
////			if (e.type == SDL_QUIT)
////			{
////				quit = true;
////			}
////			else if (e.type == SDL_KEYDOWN)
////			{
////				switch (e.key.keysym.sym)
////				{
////				case SDLK_UP:
////					currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_UP];
////					break;
////
////				case SDLK_DOWN:
////					currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
////					break;
////
////				case SDLK_LEFT:
////					currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
////					break;
////
////				case SDLK_RIGHT:
////					currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
////					break;
////
////				default:
////					currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
////					break;
////				}
////			}
////		}
////
////		// Blit the tiles_surface(source) onto the screen_surface(target)
////		SDL_BlitSurface(currentSurface, NULL, screenSurface, NULL);
////
////		// Update the window
////		SDL_UpdateWindowSurface(window);
////	}
////
////	closeSDL();
////	
////	return 0;
////}
