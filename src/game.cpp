#include "game.h"


Game::Game() 
	: window_(sf::Vector2u(1440, 810), "SFML Example")
{
	// TODO: Use console's constructor for setup.
	console_.setup(12, 16, 480, window_.get_size().y);

	srand(static_cast<unsigned int>(time(nullptr)));
	console_.add_message("Seeded rng with {" + std::to_string(time(nullptr)) + "}.");
}

void Game::handle_input()
{
	window_.process_events();

	const auto is_key_pressed = sf::Keyboard::isKeyPressed;
	const auto W = sf::Keyboard::W;
	const auto A = sf::Keyboard::A;

	// poll keyboard state

	if (is_key_pressed(W))
	{
		console_.add_message("Key pressed: UP");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		console_.add_message("Key pressed: DOWN");
	}
	if (is_key_pressed(A))
	{
		console_.add_message("Key pressed: LEFT");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		console_.add_message("Key pressed: RIGHT");
	}
}

void Game::update(const sf::Time& delta_time)  // NOTE: delta_time is fixed.
{
	/*
	static sf::Time elapsed;
	const sf::Time timestep{ sf::seconds(0.1) };

	elapsed += delta_time;
	if (elapsed >= timestep)
	{
		fixed_update()
		elapsed -= timestep;
	}
	*/
}

void Game::render()
{
	window_.begin_draw();

	// TODO: Render scene here.

	console_.render(window_);
	window_.end_draw();
}
