#include "Program.h"
#include "ParticleContainer.h"
#include <SFML/graphics.hpp>


Program::Program()
{
	pc = new ParticleContainer(200);
}


Program::~Program()
{
	delete pc;
}
void Program::run()
{
	float dt = 100;
	sf::RenderWindow window(sf::VideoMode(200,200), "SPH");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else
			{
				simulate(dt);
				draw(window);
			}
		}
	}
}

void Program::simulate(float dt)
{
	pc->updateParticles(dt);
}

void Program::draw(sf::RenderWindow& window)
{
	//window->clear(sf::Color::Black);
	//std::vector<float> pos;
	//for (int i = 0; i < pos.size(); i += 3)
	//{
	//	const int x = pos[i];
	//	const int y = pos[i + 1];
	//	//int z = pos[i + 2];

	//	sf::CircleShape shape(100.0f);
	//	shape.setFillColor(sf::Color::Green);
	//	//shape.setPosition(x, y);
	//	window->draw(shape);
	//	
	//}

	//window->display();


	sf::CircleShape shape(100.f);
	window.clear();
	window.draw(shape);
	window.display();


}





