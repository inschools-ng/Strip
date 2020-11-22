#include "pch.h"
#include "World.h"

#include <vector>

using namespace std;
using namespace sf;


World::World(Vector2u l_windSize)
{
	m_blockSize = 16;

	m_windowSize = l_windSize;
	
	RespawnApple(); // place apple somewhere on the grid

	m_appleShape.setFillColor(Color::Red);
	m_appleShape.setRadius(m_blockSize / 2);
	
	
	for (int i = 0; i < 4; ++i)
	{
		// set up a red rectangle wall on each side of the rectangle bounds
		m_bounds[i].setFillColor(Color(150, 0, 0));
		
		// to know how big each wall has to be on a specific axis 
		if (!((i + 1) % 2))
		{
			m_bounds[i].setSize(Vector2f(m_windowSize.x, m_windowSize.y)); 
		}
		else {
			m_bounds[i].setSize(Vector2f(m_blockSize, m_windowSize.y)); 
		}

		if (i < 2)
		{
			m_bounds[i].setPosition(0, 0);
		}
		else {
			m_bounds[i].setOrigin(m_bounds[i].getSize());
			m_bounds[i].setPosition(Vector2f(m_windowSize));
		}
	}

}

void World::RespawnApple()
{
	int maxX = (m_windowSize.x / m_blockSize) - 2;
	int maxY = (m_windowSize.y / m_blockSize) - 2;
	m_item = Vector2i(
		rand() % maxX + 1, rand() % maxY + 1);
	m_appleShape.setPosition(
		m_item.x * m_blockSize,
		m_item.y * m_blockSize);
}

void World::Update(Snake& l_player)
{
	if (l_player.GetPosition() == m_item) {
		l_player.Extend();
		l_player.IncreaseScore();
		RespawnApple();
	}


	int gridSize_x = m_windowSize.x / m_blockSize;
	int gridSize_y = m_windowSize.y / ;


	if (l_player.GetPosition().x <= 0 || l_player.GetPosition().y <= 0 ||
		l_player.GetPosition().x >= gridSize_x - 1 || l_player.GetPosition().y >= gridSize_y - 1)
	{
		l_player.Lose();
	}
}


World::~World()
{
}