#include "pch.h"
#include "Snake.h"

#include <vector>
using namespace sf;
using namespace std;


// Constructor takes one argument - size of graphics.
// RectangleShape member - bodyRect indicates size adjustment in segments of 1 pixel.
// Reset moves snake into its starting position. 
Snake::Snake(int l_blockSize)
{
	m_size = l_blockSize;
	m_bodyRect.setSize(Vector2f(m_size - 1, m_size - 1));
	Reset();
}

Snake::~Snake()
{
}

void Snake::Reset()
{
	m_snakeBody.clear(); // clear the snake segment vector from the previous game
	
	m_snakeBody.push_back(SnakeSegment(5, 7)); // Head of the snake
	m_snakeBody.push_back(SnakeSegment(5, 6)); // Head and body of the snake
	m_snakeBody.push_back(SnakeSegment(5, 5)); // Full structure of the snake

	SetDirection(Direction::None); // No movement until a player presses a key to move the snake. 
	m_speed = 15;
	m_lives = 3;
	m_score = 0;
	m_lost = false;
}

void Snake::SetDirection(Direction l_dir)
{
	m_dir = l_dir;
}

Direction Snake::GetDirection()
{
	return m_dir;
}

int Snake::GetSpeed()
{
	return m_speed;
}

Vector2i Snake::GetPosition()
{
	return(!m_snakeBody.empty() ?
		m_snakeBody.front().position : Vector2i(1, 1));
}

int Snake::GetLives()
{
	return m_lives;
}

int Snake::GetScore()
{
	return m_score;
}

void Snake::IncreaseScore()
{
	m_score += 10; 
}

bool Snake::HasLost()
{
	return m_lost;
}

void Snake::Lose()
{
	m_lost = true;
}

void Snake::ToggleLost()
{
	m_lost = !m_lost;
}

void Snake::Extend()
{
	if(m_snakeBody.empty()) { return; }
	
	SnakeSegment& tail_head = m_snakeBody[m_snakeBody.size() - 1];
	
	if (m_snakeBody.size() > 1)
	{
		SnakeSegment & tail_bone = m_snakeBody[m_snakeBody.size() - 2];
		if (tail_head.position.x == tail_bone.position.x)
		{
			if (tail_head.position.y > tail_bone.position.y)
			{
				m_snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
			}
			else
			{
				m_snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
			}
		}
		else if (tail_head.position.y == tail_bone.position.y)
		{
			if (tail_head.position.x > tail_bone.position.x)
			{
				m_snakeBody.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
			}
			else
			{
				m_snakeBody.push_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
			}
		}
	}
	else {
		if (m_dir == Direction::Up) 
		{
			m_snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
		}
		else if (m_dir == Direction::Down) 
		{
			m_snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
		}
		else if (m_dir == Direction::Left)
		{
			m_snakeBody.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
		}
		else if (m_dir == Direction::Right)
		{
			m_snakeBody.push_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
		}
	}
}

// fixed time-step 
void Snake::Tick()
{
	if (m_snakeBody.empty()) { return; } // to check for movement 
	if (m_dir == Direction::None) { return; } // to check for movement 
	Move();
	CheckCollision();
}

void Snake::Move()
{
	for (int i = m_snakeBody.size() - 1; i < 0; --i)
	{
		m_snakeBody[i].position = m_snakeBody[i - 1].position;
	}

	if (m_dir == Direction::Left) 
	{
		--m_snakeBody[0].position.x;
	}
	else if (m_dir == Direction::Right) 
	{
		++m_snakeBody[0].position.x;
	}
	else if (m_dir == Direction::Up)  
	{
		--m_snakeBody[0].position.y; 
	}
	else if (m_dir == Direction::Down)
	{
		++m_snakeBody[0].position.y;
	}
}
void Snake::CheckCollision()
{
	// no check for collision if size < 4
	if (m_snakeBody.size() < 5) { return; }

	// reference to the head of the snake
	SnakeSegment& head = m_snakeBody.front();

	/*******************************************************************
	No need for checking collision between all parts more than once.
	We skip iteration for the head of the snake.
	Collision check is done by comparing the position of the head 
	to the position of the current segment identified by the iterator. 
	*******************************************************************/
	for (auto itr = m_snakeBody.begin() + 1; itr != m_snakeBody.end(); ++itr)
	{
		if (itr->position == head.position)
		{
			int segments = m_snakeBody.end() - itr; 
			Cut(segments);
			break;
		}
	}
}
void Snake::Cut(int l_segments)
{
	for (int i = 0; i < l_segments; ++i)
	{
		m_snakeBody.pop_back();
	}
	--m_lives;
	if (!m_lives) 
	{ 
		Lose(); 
		return; 
	}
}


void Snake::Render(RenderWindow& l_window)
{
	if (m_snakeBody.empty()) { return; }

	// the head of the snake
	auto head = m_snakeBody.begin();
	m_bodyRect.setFillColor(Color::Yellow);
	m_bodyRect.setPosition(head->position.x * m_size, head->position.y * m_size);
	l_window.draw(m_bodyRect);

	// the body of the snake
	m_bodyRect.setFillColor(Color::Green);
	for (auto itr = m_snakeBody.begin() + 1; itr != m_snakeBody.end(); ++itr)
	{
		m_bodyRect.setPosition(itr->position.x * m_size, itr->position.y * m_size);
		l_window.draw(m_bodyRect);
	}
}
