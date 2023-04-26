#include "world.h"


World::World(sf::Vector2u window_size, float tile_size)
	: window_size_(window_size)
	, tile_size_(tile_size)
{
	apple_.shape.setFillColor(sf::Color::Red);
	apple_.shape.setRadius(tile_size_ / 2.f);
	respawn_apple();

	// TODO: Create walls.
}


void World::respawn_apple()
{
	int max_x = window_size_.x / static_cast<int>(tile_size_) - 2;
	int max_y = window_size_.y / static_cast<int>(tile_size_) - 2;
	apple_.position = sf::Vector2i{	rand() % max_x + 1, rand() % max_y + 1 };
	apple_.shape.setPosition(apple_.position.x * tile_size_,
							 apple_.position.y * tile_size_);
}


void World::fixed_update(Snake& player)
{
	if (player.get_position() == apple_.position)
	{
		player.add_segment();
		respawn_apple();
	}
}


void World::render(Window& window)
{
	window.draw(apple_.shape);
}