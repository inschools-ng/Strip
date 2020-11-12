#pragma once

#include "SFML/Graphics.hpp"
#include <string>
#include <vector>


using namespace std;
using namespace sf;


struct SnakeSegment {
	SnakeSegment (int x, int y) : position(x, y){}
	Vector2i position;
};

using SnakeContainer = std::vector<SnakeSegment>;

enum class Direction {None, Up, Down, Left, Right };

Direction ::Direction ()
{
}

Direction ::~Direction ()
{
}

class Snake
{
public:
	Snake(int l_blockSize);
	~Snake();

	// Helper methods.
	void SetDirection(Direction l_dir);
	Direction GetDirection();
	int GetSpeed();
	Vector2i GetPosition();
	int GetLives();
	int GetScore();
	void IncreaseScore();
	bool HasLost();

	void Lose(); // Handle losing here.
	void ToggleLost();

	void Extend(); // Grow the snake.
	void Reset(); // Reset to the starting position
	
	void Move(); // Movement method. 
	void Tick(); // Update method. 

	void Cut(int l_segments); // Method for cutting snake.
	void Render(RenderWindow& l_window);

private:
	void CheckCollision(); // Checking for collisions.

	SnakeContainer m_snakeBody;	// Segment vector
	int m_size; // Size of the graphics.
	Direction m_dir; // Current direction
	int m_speed; // Speed of the snake
	int m_lives; // Lives
	int m_score; // Score
	bool m_lost; // Losing state
	RectangleShape m_bodyRect; // Shape used in rendering
};

