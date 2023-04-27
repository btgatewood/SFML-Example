#include "world.h"

#include <iostream>


World::World(sf::Vector2u window_size, float tile_size)
	: window_size_(window_size)
	, tile_size_(tile_size)
{
	apple_.shape.setFillColor(sf::Color::Red);
	apple_.shape.setRadius(tile_size_ / 2.f);

	// NOTE: Seeding rng here because world is constructed before game.
	// TODO: Seed rng in main?
	srand(static_cast<unsigned int>(time(nullptr)));  // seed rng
	// NOTE: We need to be able to access console from here but it's not
	//		 initialized yet.
	std::cout << "Seeded rng with time(nullptr): " << time(nullptr) << "\n";
	respawn_apple();

	// create the walls
	for (int i = 0; i < 4; ++i)
	{
		walls_[i].setFillColor(sf::Color::Blue);

		if (!((i + 1) % 2)) // is wall vertical?
		{
			walls_[i].setSize(sf::Vector2f(static_cast<float>(window_size_.x), 
										   tile_size_));
		}
		else  // wall is horizontal
		{
			walls_[i].setSize(sf::Vector2f(tile_size_, 
										   static_cast<float>(window_size_.y)));
		}

		if (i < 2)
		{
			walls_[i].setPosition(0, 0);  // unnecessary if default pos is 0,0
		}
		else
		{
			walls_[i].setOrigin(walls_[i].getSize());
			walls_[i].setPosition(sf::Vector2f(window_size_));
		}
	}
}


void World::respawn_apple()
{
	int max_x = window_size_.x / static_cast<int>(tile_size_) - 2;
	int max_y = window_size_.y / static_cast<int>(tile_size_) - 2;
	apple_.position = sf::Vector2i{	rand() % max_x + 1, rand() % max_y + 1 };
	apple_.shape.setPosition(apple_.position.x * tile_size_,
							 apple_.position.y * tile_size_);

	// TODO: Check for snake collisions.
}


void World::fixed_update(Snake& player)
{
	if (player.get_position() == apple_.position)
	{
		player.add_segment();
		respawn_apple();
	}

	auto grid_size_x = window_size_.x / tile_size_;
	auto grid_size_y = window_size_.y / tile_size_;

	if (player.get_position().x < 1 || 
		player.get_position().y < 1 ||
		player.get_position().x > grid_size_x - 2 ||
		player.get_position().y > grid_size_y - 2)
	{
		player.reset();
	}
}


void World::render(Window& window)
{
	for (auto& wall : walls_)
	{
		window.draw(wall);
	}

	window.draw(apple_.shape);
}