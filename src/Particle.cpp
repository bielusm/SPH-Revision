#include <SFML/Main.hpp>
#include "Particle.h"
#include <glm/glm.hpp>
#include "Kernel.h"
#include "Constants.h"

Particle::Particle(glm::vec2 pos, glm::vec2 localVelocity, int index, float size)
	:pos(pos), localVelocity(localVelocity), index(index)
{
}

void Particle::CalcPressure()
{
	if (neighbors.size() > 0)
	{
		pressurePi = PressurePi(density);
	}
	else
	{
		density = p0;
		pressurePi = PressurePi(density);
	}
}

float Particle::PressurePi(float dPi)
{
	//http://matthias-mueller-fischer.ch/publications/sca03.pdf
	//proposed by Desbrun and Gascuel 1996
	return k * (density - p0);
}

void Particle::CalcImmediateVelocity(float dt)
{
	glm::vec2 fVisG = fViscosity() + fOther();
	immediateVel = localVelocity + dt * (fVisG / mj);

}

void Particle::CalcDensity()
{
	float sum = 0;
	float a = 0;
	glm::vec2 b(0, 0);
	for (Particle* p : neighbors)
	{
		float xij = glm::length(pos - p->pos);


		sum += mj * Kernel::poly6((xij));
	}
	density = sum;
}



//using https://www10.cs.fau.de/publications/theses/2010/Staubach_BT_2010.pdf
//from Mathhias Muller et all
glm::vec2 Particle::fPressure()
{
	float Ai = pressurePi;

	pressureForce = { 0.0f,0.0f };
	for (Particle* p : neighbors)
	{
		float Aj = p->pressurePi;
		float phiJ = p->density;

		pressureForce += mj * (Ai + Aj) / (phiJ * 2.0f) * Kernel::spikyGrad(glm::length(pos - p->pos));
	}
	return -pressureForce;
}

glm::vec2 Particle::fViscosity()
{
	glm::vec2 sum(0.0f, 0.0f);
	glm::vec2 vi = localVelocity;
	for (Particle* p : neighbors)
	{
		float pj = p->density;
		glm::vec2 vj = p->localVelocity;
		glm::vec2 vij = vj - vi;
		glm::vec2 xij = (pos - p->pos);
		sum += (mj / pj) * vij * Kernel::viscosityLap(glm::length(xij));
	}
	return  vis * sum;

}

glm::vec2 Particle::fOther()
{
	return p0 * g;
}

glm::vec2 Particle::calcForces()
{
	return fPressure() + fViscosity() + fOther();
}



void Particle::CalcVelocity(float dt)
{
	localVelocity += calcForces() /mj;
}

void Particle::CalcPosition(float dt)
{
	pos += dt * localVelocity;
}



Particle::~Particle()
{
}

void Particle::clear()
{
	neighbors.clear();
	Fi = glm::vec3(0, 0, 0);
}

void Particle::addNeighbor(Particle* p)
{
	neighbors.push_back(p);
}
