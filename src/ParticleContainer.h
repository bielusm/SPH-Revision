#pragma once
#include "Particle.h"
#include <vector>
#include "glm\glm.hpp"
#include "Grid.h"
#include "rect.h"

class ParticleContainer
{
public:
	void setInBounds(Particle &p);
	~ParticleContainer();
	ParticleContainer(int MAXPARTICLES, Rect boundaries);
	void updateParticles(float dt);
	std::vector <Particle> particles;
	void getPositions(std::vector<float>& positions);
private:
	int MAXPARTICLES;
	void findNeighbors(Particle &p, int pIndex);
	Grid *grid;
	Rect boundaries;
};

