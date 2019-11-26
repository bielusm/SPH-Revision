#include <SFML/Main.hpp>
#include "Particle.h"
#include <glm/glm.hpp>
#include "Kernel.h"
#include "Constants.h"

Particle::Particle(glm::vec2 pos, glm::vec2 localVelocity, int index)
	:pos(pos), localVelocity(localVelocity), index(index)
{
	density = 0;
	pressurePi = 0;
}

void Particle::CalcPressure()
{
	pressurePi = PressurePi(density);
}

float Particle::PressurePi(float dPi)
{
	//http://matthias-mueller-fischer.ch/publications/sca03.pdf
	//proposed by Desbrun and Gascuel 1996
	return k * (density - p0);
}

void Particle::CalcDensity()
{
	density = 0;
	float a = 0;
	glm::vec2 b(0, 0);

	for (Particle* p : neighbors)
	{
		float xij = glm::length(pos - p->pos);


		density += mj * Kernel::poly6((xij));
	}
	if (neighbors.size() == 0)
		density = p0;
}



//pressure calculation from https://bigtheta.io/2017/07/08/implementing-sph-in-2d.html
glm::vec2 Particle::fPressure()
{
	float Ai = pressurePi;

	glm::vec2 pressureForce = { 0.0f,0.0f };
	for (Particle* p : neighbors)
	{
		float Aj = p->pressurePi;
		float phiJ = p->density;

		pressureForce += glm::normalize(pos-p->pos) *((Ai + Aj)/ 2.0f) * (mj /phiJ) * Kernel::spikyGrad(glm::length(pos - p->pos));
	}
	return -pressureForce;
}

//viscosity calculation from https://bigtheta.io/2017/07/08/implementing-sph-in-2d.html
glm::vec2 Particle::fViscosity()
{
	glm::vec2 sum(0.0f, 0.0f);
	glm::vec2 vi = localVelocity;
	for (Particle* p : neighbors)
	{
		float pj = p->density;
		glm::vec2 vj = p->localVelocity;
		glm::vec2 vji = vj - vi;
		glm::vec2 xij = (pos - p->pos);
		sum+= vis * mj * (vji)/p->density * Kernel::viscosityLap(glm::length(xij));
		//	sum += (mj / pj) * vji * Kernel::viscosityLap(glm::length(xij));
	}
	return  sum;

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
	localVelocity += calcForces() / mj;
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
}

void Particle::addNeighbor(Particle* p)
{
	neighbors.push_back(p);
}
