#include "snake.h"


Snake::Snake(int cell_size) : cell_size_(cell_size)
{
	body_rect_.setSize(sf::Vector2f(cell_size_ - 1.f, cell_size_ - 1.f));
	reset();
}


void Snake::reset()
{
	body_.clear();

	body_.push_back(Segment(7, 8));
	body_.push_back(Segment(7, 7));
	body_.push_back(Segment(7, 6));

	direction_ = Direction::None;
}
