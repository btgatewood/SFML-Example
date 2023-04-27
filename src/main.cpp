
#include <sstream>
#include <SFML/Graphics.hpp>
#include "game.h"


const int UPDATES_PER_SECOND = 50;
const int MAX_RENDERS_PER_SECOND = 100;

const sf::Time UPDATE_TIME = sf::seconds(1.f / UPDATES_PER_SECOND);
const sf::Time MIN_RENDER_TIME = sf::seconds(1.f / MAX_RENDERS_PER_SECOND);

int main()
{
	Game game;

	sf::Clock clock;

	sf::Time update_timer;
	sf::Time render_timer;
	sf::Time self_timer;

	int update_count{ 0 };
	int render_count{ 0 };

	while (!game.get_window()->is_done())
	{
		game.handle_input();

		sf::Time elapsed_time = clock.restart();

		update_timer += elapsed_time;
		while (update_timer > UPDATE_TIME)
		{
			game.update(UPDATE_TIME);
			update_timer -= UPDATE_TIME;
			++update_count;
		}

		render_timer += elapsed_time;
		if (render_timer > MIN_RENDER_TIME)
		{
			game.render();
			render_timer = sf::seconds(0);
			++render_count;
		}

		self_timer += elapsed_time;
		if (self_timer > sf::seconds(1.f))  // update fps data every 10 seconds
		{
			// TODO: Render fps data at top right of screen (not in console).
			std::ostringstream oss;
			oss << (render_count / 1.f) << "fps @ " 
				<< (update_count / 1.f) << "hz";
			// write fps data to game's console
			game.get_console()->add_message(oss.str());

			update_count = 0;
			render_count = 0;
			self_timer -= sf::seconds(1.f);
		}
	}

	return 0;
}
