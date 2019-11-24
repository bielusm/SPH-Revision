#pragma once
#include <vector>
#include <glm/vec2.hpp>


class Particle
{
public:
	Particle() = default;
	Particle(glm::vec2 pos, glm::vec2 localVelocity, int index, float size);
	~Particle();
	
	glm::vec2 PressurePi(glm::vec2 pi);
	void clear();
	void addNeighbor(Particle *p);

	void CalcImmediateVelocity(float dt);
	void CalcImmediateDensity(float dt);

	void fPressure();
	glm::vec2 fViscosity();
	glm::vec2 fOther();

	void CalcVelocity(float dt);
	void CalcPosition(float dt);
	
	glm::vec2 localVelocity;
	glm::vec2 immediateVel;
	void CalcPressure();
	glm::vec2 density;
	glm::vec2 dPi;
	glm::vec2 pressure;
	std::vector<Particle*> neighbors;
	glm::vec2 pos;
	float size;
	glm::vec2 Fi;
	glm::vec2 pressureForce;
	glm::vec2 pressurePi;
	glm::ivec2 gridCoords;
	int index;
};

