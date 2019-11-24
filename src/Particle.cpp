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
		pressurePi = PressurePi(idPi);
	}
	else
	{
		idPi = glm::vec2(p0, p0);
		pressurePi = PressurePi(idPi);
	}
}

glm::vec2 Particle::PressurePi(glm::vec2 dPi)
{
	float x, y;
	x = pow(idPi.x / p0, 7);
	y = pow(idPi.y / p0, 7);
	glm::vec2 pressurePi(x, y);
	return k * (pressurePi - 1.0f);
}

void Particle::CalcImmediateVelocity(float dt)
{
	glm::vec2 fVisG = fViscosity() + fOther();
	immediateVel = localVelocity + dt * (fVisG / mj);
	
}

void Particle::CalcImmediateDensity(float dt)
{

	glm::vec2 sum(0, 0);
	float a = 0;
	glm::vec2 b(0, 0);
	for (Particle *p : neighbors)
	{
		float xij = glm::length(pos - p->pos);


		a += mj * Kernel::poly6(abs(xij));

	
	}
	for (Particle *p : neighbors)
	{
		float xij = glm::length(pos - p->pos);
		b += (immediateVel - p->immediateVel)*Kernel::Wgradient((xij/hVal));
	}
	sum = a + dt * b;
	idPi = sum;
}



//using https://www10.cs.fau.de/publications/theses/2010/Staubach_BT_2010.pdf
static int counter = 0;
void Particle::fPressure()
{

	float sum = 0;
	glm::vec2 Pi = idPi;
	glm::vec2 Ai = pressurePi;
	glm::vec2 Pi2(pow(Pi.x, 2),pow(Pi.y,2));
	glm::vec2 Pj;
	glm::vec2 Pj2;
	glm::vec2 a;
	float  b;
	pressureForce = { 0.0f,0.0f };
	for (Particle *p : neighbors)
	{
		glm::vec2 Aj = p->pressurePi;
		 Pj = p->idPi;
		Pj2 = glm::vec2(pow(Pj.x, 2), pow(Pj.y, 2));

		a =  (Ai / Pi2 + Aj / Pj2)*mj;
		b = Kernel::spikyGrad((glm::length(pos-p->pos)/hVal));
		pressureForce += a * b;
		if (index == 33)
		{
			counter++;
		}
	}
	pressureForce *= -idPi;
}

glm::vec2 Particle::fViscosity()
{
	glm::vec2 sum(0.0f, 0.0f);
	glm::vec2 vi = localVelocity;
	for (Particle *p : neighbors)
	{
		glm::vec2 pj = p->idPi;
		glm::vec2 vj = p->localVelocity;
		glm::vec2 vij = vi - vj;
		glm::vec2 xij = (pos - p->pos);
		sum += (mj / p0) * vij * 
		(xij * Kernel::viscosityGrad(glm::length(xij)/hVal)) /
			(glm::dot(xij, xij) + (0.01f*pow(hVal, 2)));
	}
	return  mj* vis* 2 * sum;
}

glm::vec2 Particle::fOther()
{
	return p0* g;
}

void Particle::CalcVelocity(float dt)
{
		localVelocity = immediateVel +  dt * (pressureForce) / mj;
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
	Fi = glm::vec3( 0,0,0);
}

void Particle::addNeighbor(Particle *p)
{
	neighbors.push_back(p);
}
