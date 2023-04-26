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

	void fixed_update();
	void render(sf::RenderWindow& window);

	void add_segment();

private:
	void reset();

	// void move();
	// void check_collisions();

	std::vector<Segment> body_;
	Direction			 direction_	{ Direction::None };
	sf::RectangleShape	 body_rect_;
	float				 cell_size_ { 16.f };
};
