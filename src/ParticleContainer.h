#pragma once
#include "Particle.h"
#include <vector>
#include "glm\glm.hpp"
#include "Grid.h"
class ParticleContainer
{
public:
	ParticleContainer(int MAXPARTICLES);
	~ParticleContainer();
	void updateParticles(float dt);
	std::vector <Particle> particles;
	void getPositions(std::vector<float>& positions);
private:
	int MAXPARTICLES;
	void findNeighbors(Particle &p, int pIndex);
	Grid *grid;
};

