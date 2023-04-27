#pragma once

#include "window.h"
#include "console.h"


class Game
{
public:
	Game();

	void handle_input();
	void update(const sf::Time& delta_time);
	void render();

	Window* get_window()   { return &window_; }
	Console* get_console() { return &console_; }
	
private:
	Window window_;
	Console console_;
};
