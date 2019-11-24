#include "Program.h"
#include <SFML/Window.hpp>

//adapted from https://www.sfml-dev.org/tutorials/2.5/window-window.php
namespace Program
{
	void go()
	{
		sf::Window window(sf::VideoMode(800, 600), "SPH");
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
		}
	}
}