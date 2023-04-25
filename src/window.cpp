#include "window.h"


Window::Window(const sf::Vector2u& size, const std::string& title)
{
	window_size_ = size;
	window_title_ = title;
	is_fullscreen_ = false;
	is_done_ = false;

	create_window();
}


void Window::process_events()
{
	sf::Event event;

	while (render_window_.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			is_done_ = true;
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				is_done_ = true;
			}
			else if (event.key.code == sf::Keyboard::F5)
			{
				// NOTE: Optimal resolution on laptop is 1920x1080.
				toggle_fullscreen();  // NOTE: Going fullscreen is buggy af.
			}
		}
	}
}


void Window::toggle_fullscreen()
{
	is_fullscreen_ = !is_fullscreen_;
	destroy_window();
	create_window();
}


void Window::create_window()  // NOTE: Private method.
{
	auto style = (is_fullscreen_ ? sf::Style::Fullscreen : sf::Style::Default);
	render_window_.create({ window_size_.x, window_size_.y }, window_title_, style);
}
