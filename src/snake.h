#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "window.h"


const sf::Vector2u WINDOW_SIZE{ 960, 960 };
const float	TILE_SIZE{ 24.f };


enum class Direction
{
	None,
	Up,
	Down,
	Left,
	Right
};


struct Segment  // TODO: Should Segment struct be a private member of Snake class?
{
	Segment(int x, int y) 
		: position(x, y) 
	{}

	sf::Vector2i position;
};


class Snake
{
public:
	Snake();

	void reset();

	void fixed_update();
	void render(Window& window);

	void add_segment();

	Direction get_prev_direction();
	void set_direction(Direction dir) { direction_ = dir; }

	int get_speed()					  { return 8; }  // cells per second
	sf::Vector2i get_position()		  { return body_[0].position; }

private:
	// void move();
	// void check_collisions();

	Direction direction_{ Direction::None };

	std::vector<Segment> body_;
	sf::RectangleShape	 body_rect_;
};
