#include "game.h"


Game::Game()
{
	console_.setup(12, 16, 320, window_.get_size().y);
}

void Game::handle_input()
{
	window_.process_events();
}

void Game::update(const sf::Time& elapsed_time)
{
	// TODO: Fixed update.
}

void Game::render()
{
	window_.begin_draw();
	console_.render(window_);
	window_.end_draw();
}