#pragma once

#include <string>

#include <SFML/Graphics.hpp>


class Window
{
public:
	Window(const sf::Vector2u& size, const std::string& title);
	~Window()						  { destroy_window(); }

	void process_events();

	void begin_draw()				  { render_window_.clear(); }
	void draw(sf::Drawable& drawable) { render_window_.draw(drawable); }
	void end_draw()					  { render_window_.display(); }

	void toggle_fullscreen();

	bool is_fullscreen()			  { return is_fullscreen_; }
	bool is_done()					  { return is_done_; }

	const sf::Vector2u& get_size()	  { return window_size_; }

private:
	void create_window();
	void destroy_window()			  { render_window_.close(); }

	sf::RenderWindow render_window_;
	sf::Vector2u window_size_;
	std::string window_title_;
	bool is_fullscreen_;
	bool is_done_;
};
