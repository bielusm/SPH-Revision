#include "ParticleContainer.h"
#include "glm\gtx\norm.hpp"
#include <iostream>
#include "rect.h"
#include "Constants.h"
#define lambda 0.4
#define BUFFER 0.3f

ParticleContainer::ParticleContainer(int MAXPARTICLES, Rect boundaries)
	: MAXPARTICLES(MAXPARTICLES), boundaries(boundaries)
{
	grid = new Grid(-500.0f, 500.0f, -500.0f, 500.0f);
	float neg = 1;

	int index = 0;

	for (int i = 0; i < MAXPARTICLES / 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			float x = -5.0f - (i * (particleSize + BUFFER));
			float y = -200.0f + (j * 20 * (particleSize + BUFFER)); 
			glm::vec3 pos(x, y, 1);
			glm::vec3 vel(0.0f, 0.0f, 0);
			particles.push_back(Particle(pos, vel, index));
			index++;
		}
	}

	grid->makeGrid(particles);

}

void ParticleContainer::updateParticles(float dt)
{
	int i = 0;
	for (Particle& p : particles)
	{
		p.clear();
		findNeighbors(p, i);
		i++;
	}
	float stepVal;

	stepVal = 0.001f;
	for (Particle& p : particles)
	{
		p.CalcDensity();
		p.CalcPressure();
	}

	for (Particle& p : particles)
	{

		p.CalcVelocity(stepVal);
		p.CalcPosition(stepVal);
		setInBounds(p);
		glm::ivec2 gc = grid->updateCoord(p.index, p.gridCoords, p.pos);
		p.gridCoords = gc;
	}
}

void ParticleContainer::findNeighbors(Particle& p, int pIndex)
{
	std::vector<int> indices = grid->neighborIndices(p);
	for (int i = 0; i < indices.size(); i++)
	{
		Particle* j = &particles[indices[i]];
		const float dist = glm::distance(p.pos, j->pos);
		if (dist < hVal && dist > 0)
		{
			p.addNeighbor(j);
		}

	}
}

void ParticleContainer::getPositions(std::vector<float>& positions)
{
	for (int i = 0; i < MAXPARTICLES; i++)
	{
		Particle p = particles[i];
		positions.push_back(p.pos.x);
		positions.push_back(p.pos.y);
		positions.push_back(1.0f);
	}
}

//boundary conditions from Particle-Based Fluid Simulation for Interactive Applications
//Matthias Müller, David Charypar and Markus Gross
void ParticleContainer::setInBounds(Particle &p)
{
	glm::vec2 pos = p.pos;
	glm::vec2 vel = p.localVelocity;
	if (pos.x < boundaries.left)
	{
		pos.x = boundaries.left + 1;
		vel.x = -vel.x;
	}
	else if (pos.x > boundaries.right)
	{
		pos.x = boundaries.right - 1;
		vel.x = -vel.x;
		
	}
	else if (pos.y > boundaries.top)
	{
		pos.y = boundaries.top - 1;
		vel.y = -vel.y;
	}
	else if (pos.y < boundaries.bottom)
	{
		pos.y = boundaries.bottom + 1;
		vel.y = -vel.y;
	}
	p.pos = pos;
	p.localVelocity = vel;
	
}
ParticleContainer::~ParticleContainer()
{
	delete grid;
}




