#include "snake.h"


Snake::Snake(int cell_size) : cell_size_(static_cast<float>(cell_size))
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


/* -------------------------------------------------------------------------- */
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

	if (body_.size() < 5) { return; }

	// check collisions
	Segment& head = body_.front();

	for (auto itr = body_.begin() + 1; itr != body_.end(); ++itr)
	{
		if (head.position == itr->position)  // body collision
		{
			/* TODO: ???
			 *
			 * auto num_segments = body_.end() - itr;
			 * cut_segments(num_sugments);
			 *
			 * game_over();
			 *  
			 */
			reset();
		}
	}
}


/* -------------------------------------------------------------------------- */
void Snake::render(sf::RenderWindow& window)
{
	// draw body
	body_rect_.setFillColor(sf::Color::Green);
	for (auto itr = body_.begin() + 1; itr != body_.end(); ++itr)
	{
		body_rect_.setPosition(itr->position.x * cell_size_,
							   itr->position.y * cell_size_);
		window.draw(body_rect_);
	}

	// draw head
	const auto& head = body_.front();
	body_rect_.setFillColor(sf::Color::Yellow);
	body_rect_.setPosition(head.position.x * cell_size_, 
						   head.position.y * cell_size_);
	window.draw(body_rect_);
}


/* -------------------------------------------------------------------------- */
void Snake::add_segment()
{
	Segment& tail = body_.back();  // last element

	if (body_.size() > 1)
	{
		// use tail's next position to determine next segment position
		Segment& next = body_[body_.size() - 2];  // next to last element

		if (tail.position.x == next.position.x)
		{
			if (tail.position.y > next.position.y)  // tail is moving up
			{
				body_.push_back(Segment(tail.position.x, tail.position.y + 1));
			}
			else  // tail is moving down
			{
				body_.push_back(Segment(tail.position.x, tail.position.y - 1));
			}
		}
		else
		{
			if (tail.position.x > next.position.x)  // tail is moving left
			{
				body_.push_back(Segment(tail.position.x + 1, tail.position.y));
			}
			else  // tail is moving right
			{
				body_.push_back(Segment(tail.position.x - 1, tail.position.x));
			}
		}
	}
	else  // NOTE: I don't think we will ever use this next condition.
	{
		// use the snake's head direction to determine next segment position
		if (direction_ == Direction::None)
		{
			return;  // don't add segment if snake is not moving
		}
		else if (direction_ == Direction::Up)
		{
			body_.push_back(Segment(tail.position.x, tail.position.y + 1));
		}
		else if (direction_ == Direction::Down)
		{
			body_.push_back(Segment(tail.position.x, tail.position.y - 1));
		}
		else if (direction_ == Direction::Left)
		{
			body_.push_back(Segment(tail.position.x + 1, tail.position.y));
		}
		else if (direction_ == Direction::Right)
		{
			body_.push_back(Segment(tail.position.x - 1, tail.position.y));
		}
	}
}