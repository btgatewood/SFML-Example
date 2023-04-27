#pragma once

#include "window.h"
#include "console.h"
#include "snake.h"
#include "world.h"


class Game
{
public:
	Game();

	void handle_input();
	void update(const sf::Time& delta_time);
	void render();

	Window* get_window()   { return &window_; }
	
private:
	Window window_;
	Console console_;

	Snake snake_;
	World world_;
};
