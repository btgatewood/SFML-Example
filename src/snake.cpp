#include "snake.h"


Snake::Snake(Console& console)
	: console_(console)
{
	body_rect_.setSize(sf::Vector2f(TILE_SIZE - 1.f, TILE_SIZE - 1.f));
	reset();
}


void Snake::reset()
{
	body_.clear();

	body_.push_back(Segment(8, 8));
	body_.push_back(Segment(7, 8));
	body_.push_back(Segment(6, 8));

	direction_ = Direction::None;
}


void Snake::fixed_update()
{
	if (direction_ == Direction::None) { return; }

	// move body
	for (size_t i = body_.size() - 1; i != 0; --i)  // loop in reverse
	{
		body_[i].position = body_[i - 1].position;
	}

	// move head
	if (direction_ == Direction::Left)
	{
		body_[0].position.x -= 1;
	}
	else if (direction_ == Direction::Right)
	{
		body_[0].position.x += 1;
	}
	else if (direction_ == Direction::Up)
	{
		body_[0].position.y -= 1;
	}
	else if (direction_ == Direction::Down)
	{
		body_[0].position.y += 1;
	}

	// check collisions
	if (body_.size() < 5) { return; }

	Segment& head = body_.front();
	for (auto itr = body_.begin() + 1; itr != body_.end(); ++itr)
	{
		if (head.position == itr->position)  // body collision
		{
			// TODO: game_over() or cut_segments()?
			// ex:	auto num_segments = body_.end() - itr;
			//		cut_segments(num_sugments);
			reset();
			console_.add_message("Player ate it's tail.");
			break;  // avoid crashing the program
		}
	}
}


void Snake::render(Window& window)
{
	// draw body
	body_rect_.setFillColor(sf::Color::Green);
	for (auto itr = body_.begin() + 1; itr != body_.end(); ++itr)
	{
		body_rect_.setPosition(itr->position.x * TILE_SIZE,
							   itr->position.y * TILE_SIZE);
		window.draw(body_rect_);
	}

	// draw head
	const auto& head = body_.front();
	body_rect_.setFillColor(sf::Color::Yellow);
	body_rect_.setPosition(head.position.x * TILE_SIZE, 
						   head.position.y * TILE_SIZE);
	window.draw(body_rect_);
}


void Snake::add_segment()
{
	// added segment will be moved to the tail's position on next update
	Segment& head = body_.front();
	body_.push_back(Segment(head.position.x, head.position.y));
}


Direction Snake::get_prev_direction()
{
	Segment& head = body_[0];
	Segment& prev = body_[1];  // 2nd element is previous head position

	if (head.position.x == prev.position.x)
	{
		return head.position.y > prev.position.y ?
			Direction::Down : Direction::Up;
	}
	else  // if (head.position.y == prev.position.y)
	{
		return head.position.x > prev.position.x ?
			Direction::Right : Direction::Left;
	}
}