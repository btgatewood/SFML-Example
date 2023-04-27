#pragma once

#include <SFML/Graphics.hpp>
#include "snake.h"
#include "window.h"


struct Item
{
	sf::CircleShape shape;
	sf::Vector2i position;
};


class World
{
public:
	World(sf::Vector2u window_size, float tile_size);

	void fixed_update(Snake& player);
	void render(Window& window);

private:
	void respawn_apple();

	Item apple_;
	sf::RectangleShape walls_[4];

	float tile_size_;
	sf::Vector2u window_size_;
};