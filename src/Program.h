#pragma once
#include "ParticleContainer.h"
#include <SFML/Graphics.hpp>

class Program
{
public:
	Program();
	~Program();

	void run();
private:
	void draw(sf::RenderWindow& window);
	void simulate(float dt);

	ParticleContainer *pc;
};

