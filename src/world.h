#pragma once

#include <SFML/Graphics.hpp>
#include "console.h"
#include "snake.h"
#include "window.h"


class World
{
public:
	World(Console& console, sf::Vector2u window_size, float tile_size);

	void fixed_update(Snake& player);
	void render(Window& window);

private:
	void respawn_apple();

	Console& console_;

	float tile_size_;
	sf::Vector2u window_size_;

	sf::Vector2i apple_position_;
	sf::CircleShape apple_shape_;
	sf::RectangleShape walls_[4];
};