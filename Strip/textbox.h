#pragma once


#include <vector>
#include <string>
#include "SFML/Graphics.hpp"

using MessageContainer = std::vector<std::string>;


class Textbox
{
public:
	Textbox();
	Textbox(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos);
	~Textbox();

	void Setup(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos);

	void Add(std::string l_message);
	void Clear();

	void Render(sf::RenderWindow& l_wind);

private:
	MessageContainer m_message;
	int m_numVisible;

	sf::RectangleShape m_backdrop;
	sf::Font m_font;
	sf::Text m_content;

};

