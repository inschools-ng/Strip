#pragma once

#include "world.h"
#include "snake.h"
#include "Window.h"

#include "SFML/Graphics.hpp"
#include <string>


using namespace std;
using namespace sf;

class Game
{

public:

	Game();
	~Game();

	void HandleInput();

	void Update();

	void Render();	

	Window *GetWindow();

	float GetElapsed();

	void RestartClock();

private:

	Window m_window;

	Clock m_clock;
	float m_elapsed;

	World m_world;
	Snake m_snake;
};

