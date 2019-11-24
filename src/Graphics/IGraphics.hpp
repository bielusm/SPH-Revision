#include <SFML/Graphics.hpp>


class Graphics {
public: 


	Graphics(int width, int height)
		:width(width), height(height) {}

	virtual void draw() = 0;
private:
	int width;
	int height;
};