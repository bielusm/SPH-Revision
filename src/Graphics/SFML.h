#pragma once
#include "IGraphics.hpp"
#include <SFML/Graphics.hpp>


class SFML : public Graphics
{
public:
	sf::RenderWindow createWindow(int width, int height);
	void draw();
};
