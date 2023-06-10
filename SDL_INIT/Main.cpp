#include "Game.h"

// Game object
Game* g_game = 0;

int main(int argc, char** argv)
{
	g_game = new Game();
	g_game->init("Early Days v1.1", 100, 100, g_game->SCREEN_WIDTH, g_game->SCREEN_HEIGHT, 0);
	while (g_game->running())
	{
		g_game->handleEvents();
		g_game->update();
		g_game->render();
	}
	g_game->clean();

	return 0;
}