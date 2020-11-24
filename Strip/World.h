#pragma once

#include "SFML/Graphics.hpp"
#include <string>


using namespace std;
using namespace sf;


class World
{
public:
	World(Vector2u l_windSize);
	~World();

	int GetBlockSize();

	void RespawnApple();

	void Update(Snake& l_player);

	void Render(RenderWindow& l_window);

private:

	Vector2u m_windowSize;
	Vector2i m_item; // keeps track of the apple's coordinates 
	int m_blockSize;

	CircleShape m_appleShape; // circle for drawing the apple
	RectangleShape m_bounds[4]; // returns 4 rectangles for the boundary graphics 
};

