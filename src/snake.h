#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "console.h"
#include "window.h"


const sf::Vector2u WINDOW_SIZE{ 960, 960 };
const float	TILE_SIZE{ 24.f };


enum class Direction { None, Up, Down, Left, Right };

class Snake
{
public:
	Snake(Console& console);

	void reset();

	void fixed_update();
	void render(Window& window);

	void add_segment();

	Direction get_prev_direction();
	void set_direction(Direction dir) { direction_ = dir; }

	int get_speed()					  { return 8; }  // cells per second
	sf::Vector2i get_position()		  { return body_[0].position; }

private:
	Console& console_;

	struct Segment
	{
		Segment(int x, int y)
			: position(x, y)
		{}

		sf::Vector2i position;
	};

	Direction direction_{ Direction::None };
	std::vector<Segment> body_;
	sf::RectangleShape	 body_rect_;
};
