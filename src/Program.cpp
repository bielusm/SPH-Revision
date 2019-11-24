#include "Program.h"
#include "ParticleContainer.h"
#include <SFML/graphics.hpp>

Program::Program(int height, int width)
	: height(height), width(width)
{
	pc = new ParticleContainer(1000);
}


Program::~Program()
{
	delete pc;
}
void Program::run()
{
	float dt = 100;
	sf::RenderWindow window(sf::VideoMode(width, height), "SPH");
	sf::Vector2<float> pos(0.0f, 0.0f);
	sf::Vector2<float> size(width, height);
	sf::View view(pos,size);
	view.rotate(180);
	window.setView(view);



	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//restart clock to zero and return time elapsed
		sf::Time dt = clock.restart();
		float ms = dt.asMilliseconds();
		

		simulate(ms);
		draw(window);
	}
}

void Program::simulate(float dt)
{
	pc->updateParticles(dt);
}


void Program::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::Black);
	std::vector<float> pos;
	pc->getPositions(pos);
	for (int i = 0; i < pos.size(); i += 3)
	{
		const int x = pos[i];
		const int y = pos[i + 1];
		int z = pos[i + 2];

		sf::CircleShape shape(3.0f);
		shape.setFillColor(sf::Color::Blue);
		shape.setPosition(x, y);
		window.draw(shape);
		
	}


	//sf::CircleShape shape(100.0f);
	//shape.setFillColor(sf::Color::Green);
	////shape.setPosition(x, y);
	//window.draw(shape);

	window.display();
}





