#include "pch.h"
#include "game.h"
#include "Snake.h"
#include "Window.h"

#include "SFML/Graphics.hpp"
#include <string>
#include <vector>

using namespace std;
using namespace sf;


Game::Game()
	: m_window("Snake", Vector2u(800, 600)), m_snake(m_world.GetBlockSize()), m_world(Vector2u(800, 600))
{

}



Game::~Game()
{
}

// Processing input checks for key presses.
void Game::HandleInput()
{
	if ((Keyboard::isKeyPressed(sf::Keyboard::Up) 
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
		&& m_snake.GetDirection() != Direction::Down)

	{

		m_snake.SetDirection(Direction::Up);

	}

	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) 
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::S)) 
			&& m_snake.GetDirection() != Direction::Up)

		 {

			m_snake.SetDirection(Direction::Down);

		 }

	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) 
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
			&& m_snake.GetDirection() != Direction::Right)

		 {

			m_snake.SetDirection(Direction::Left);

		 }

	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) 
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
			&& m_snake.GetDirection() != Direction::Left)

		 {

			m_snake.SetDirection(Direction::Right);

		 }
}


// fixed time-step updates the appropriate amount of times per second
// the fixed time step uses snake speed. 
// reset the snake if player loses 
void Game::Update()
{

	float timestep = 1.0f / m_snake.GetSpeed();

	if (m_elapsed >= timestep)
	{
		m_snake.Tick();
		m_world.Update(m_snake);
		m_elapsed -= timestep;
		
		if (m_snake.HasLost())
		{
			m_snake.Reset();
		}
	}

}

void Game::Render()
{
	m_window.BeginDraw();

	// Render here 
	m_world.Render(*m_window.GetRenderWindow());
	m_snake.Render(*m_window.GetRenderWindow());

	m_window.EndDraw();

}

Window *Game::GetWindow()
{
	return &m_window;
}

float Game::GetElapsed()
{
	return m_elapsed;
}

void Game::RestartClock()
{
	m_elapsed += m_clock.restart().asSeconds();
}
