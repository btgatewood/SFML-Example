#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "window.h"

class Console
{
public:
	void setup(int max_lines, int char_size, int width, unsigned int screen_height);
	void add_message(std::string msg);

	void render(Window& window);

private:
	std::vector<std::string> lines_;

	int max_lines_{ 0 };
	float line_height_{ 0.f };

	sf::RectangleShape background_;
	sf::Font font_;
	sf::Text text_;
};
