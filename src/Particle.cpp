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
		density = glm::vec2(p0, p0);
		pressurePi = PressurePi(density);
	}
}

glm::vec2 Particle::PressurePi(glm::vec2 dPi)
{
	float x, y;
	x = pow(density.x / p0, 7);
	y = pow(density.y / p0, 7);
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
	for (Particle* p : neighbors)
	{
		float xij = glm::length(pos - p->pos);


		a += mj * Kernel::W((xij)/hVal);


	}
	for (Particle* p : neighbors)
	{
		float xij = glm::length(pos - p->pos);
		b += (immediateVel - p->immediateVel) * Kernel::Wgradient((xij / hVal));
	}
	sum = a + dt * b;
	density = sum;
}



//using https://www10.cs.fau.de/publications/theses/2010/Staubach_BT_2010.pdf
//void Particle::fPressure()
//{
//
//	float sum = 0;
//	glm::vec2 Pi = density;
//	glm::vec2 Ai = pressurePi;
//	glm::vec2 Pi2(pow(Pi.x, 2), pow(Pi.y, 2));
//	glm::vec2 Pj;
//	glm::vec2 Pj2;
//	glm::vec2 a;
//	float  b;
//	pressureForce = { 0.0f,0.0f };
//	for (Particle* p : neighbors)
//	{
//		glm::vec2 Aj = p->pressurePi;
//		Pj = p->density;
//		Pj2 = glm::vec2(pow(Pj.x, 2), pow(Pj.y, 2));
//
//		a = (Ai / Pi2 + Aj / Pj2) * mj;
//		b = Kernel::spikyGrad((glm::length(pos - p->pos) / hVal));
//		pressureForce += a * b;
//	}
//	pressureForce *= -density;
//}

//from Mathhias Muller et all
void Particle::fPressure()
{
	glm::vec2 Ai = pressurePi;

	pressureForce = { 0.0f,0.0f };
	for (Particle* p : neighbors)
	{
		glm::vec2 Aj = p->pressurePi;
		glm::vec2 phiJ = p->density;

		pressureForce += mj *(Ai + Aj) / (phiJ * 2.0f ) * Kernel::spikyGrad(glm::length(pos - p->pos) / hVal);
		//pressureForce = (Ai + Aj) / (phiJ * 2.0f);
	}
	pressureForce = -pressureForce;
}

//glm::vec2 Particle::fViscosity()
//{
//	glm::vec2 sum(0.0f, 0.0f);
//	glm::vec2 vi = localVelocity;
//	for (Particle *p : neighbors)
//	{
//		glm::vec2 pj = p->idPi;
//		glm::vec2 vj = p->localVelocity;
//		glm::vec2 vij = vi - vj;
//		glm::vec2 xij = (pos - p->pos);
//		sum += (mj / p0) * vij * 
//		(xij * Kernel::viscosityGrad(glm::length(xij)/hVal)) /
//			(glm::dot(xij, xij) + (0.01f*pow(hVal, 2)));
//	}
//	return  mj* vis* 2 * sum;
//}

glm::vec2 Particle::fViscosity()
{
	glm::vec2 sum(0.0f, 0.0f);
	glm::vec2 vi = localVelocity;
	for (Particle* p : neighbors)
	{
		glm::vec2 pj = p->density;
		glm::vec2 vj = p->localVelocity;
		glm::vec2 vij = vi - vj;
		glm::vec2 xij = (pos - p->pos);
		sum += (mj / pj) * vij * Kernel::viscosityLap(glm::length(xij) / hVal);
	}
	return  vis * sum;

}

glm::vec2 Particle::fOther()
{
	return p0 * g;
}

void Particle::CalcVelocity(float dt)
{
	localVelocity = immediateVel + dt * (pressureForce) / mj;
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
