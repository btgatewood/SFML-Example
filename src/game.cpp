#include "game.h"


Game::Game() 
	: window_(WINDOW_SIZE, "SFML Example")
	, world_(console_, WINDOW_SIZE, TILE_SIZE)
	, snake_(console_)
{
	// TODO: Setup console using constructor?
	console_.setup(12, 16, 320, window_.get_size().y);

	// srand(static_cast<unsigned int>(time(nullptr)));
	// console_.add_message("Seeded rng with: " + std::to_string(time(nullptr)));
}

void Game::handle_input()
{
	window_.process_events();

	const auto is_key_pressed = sf::Keyboard::isKeyPressed;
	const auto W = sf::Keyboard::W;

	if (is_key_pressed(W) && 
		snake_.get_prev_direction() != Direction::Down)
	{
		snake_.set_direction(Direction::Up);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
		snake_.get_prev_direction() != Direction::Up)
	{
		snake_.set_direction(Direction::Down);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
		snake_.get_prev_direction() != Direction::Right)
	{
		snake_.set_direction(Direction::Left);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
		snake_.get_prev_direction() != Direction::Left)
	{
		snake_.set_direction(Direction::Right);
	}
}

void Game::update(const sf::Time& delta_time)  // NOTE: delta_time is fixed
{
	static sf::Time elapsed;
	const sf::Time timestep{ sf::seconds(1.f / snake_.get_speed()) };

	elapsed += delta_time;
	if (elapsed >= timestep)
	{
		snake_.fixed_update();
		world_.fixed_update(snake_);
		// TODO: if snake.lost(), then snake.reset()?
		elapsed -= timestep;
	}
}

void Game::render()
{
	window_.begin_draw();

	world_.render(window_);
	snake_.render(window_);
	console_.render(window_);

	window_.end_draw();
}
