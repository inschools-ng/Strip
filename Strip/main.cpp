#include "game.h"
#include "Snake.h"
#include "Window.h"
#include "World.h"

#include <ctime>
#include <cstdlib>

#include "SFML/Graphics.hpp"
#include <string>

int main(int argc, void** argv[])
{
	srand(static_cast<int>(time(nullptr)) % rand());

	Game game;

	while (!game.GetWindow()->IsDone())
	{
		game.HandleInput();
		game.Update();
		game.Render();
		game.RestartClock();
	}

	return 0;
}