#pragma once
#include <vector>
#include <SFML/Graphics.hpp>


// TODO: Should Segment and Direction be members of class Snake?
struct Segment
{
	Segment(int x, int y) 
		: position(x, y) 
	{}

	sf::Vector2i position;
};


enum class Direction 
{ 
	None, 
	Up, 
	Down, 
	Left, 
	Right
};


class Snake
{
public:
	Snake(int cell_size);

	void reset();

	void update();
	void render(sf::RenderWindow& window);

private:
	int cell_size_{ 16 };
	sf::RectangleShape body_rect_;

	std::vector<Segment> body_;

	Direction direction_{ Direction::None };
	int speed_{ 10 };
};
