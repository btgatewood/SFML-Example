#include "console.h"

void Console::setup(int max_lines, int char_size, int width, 
					unsigned int screen_height)
{
	max_lines_ = max_lines;
	line_height_ = char_size * 1.2f;  // magic number

	background_.setSize(sf::Vector2f(static_cast<float>(width),
									 static_cast<float>(max_lines * line_height_))); 
	background_.setFillColor(sf::Color(255, 255, 255, 32));

	// set position to bottom left of screen
	sf::Vector2f position{ 0.f, screen_height - background_.getSize().y };
	background_.setPosition(position);

	font_.loadFromFile("data/CascadiaMono.ttf");

	text_.setFont(font_);
	text_.setCharacterSize(char_size);
	text_.setFillColor(sf::Color::White);
}

void Console::add_message(std::string msg)
{
	lines_.push_back(msg);

	while (lines_.size() > max_lines_)
	{
		lines_.erase(lines_.begin());
	}
}

void Console::render(Window& window)
{
	std::string str;
	for (std::string& line : lines_)
	{
		str.append(line + "\n");
	}
	text_.setString(str);

	// set position to bottom left of screen
	float y = window.get_size().y - (lines_.size() * line_height_);
	text_.setPosition(3.f, y);

	window.draw(background_);
	window.draw(text_);
}