#pragma once
#include <vector>
#include <glm/vec2.hpp>


class Particle
{
public:
	Particle() = default;
	Particle(glm::vec2 pos, glm::vec2 localVelocity, int index);
	~Particle();
	
	void clear();
	void addNeighbor(Particle *p);

	void CalcDensity();

	void CalcVelocity(float dt);
	void CalcPosition(float dt);
	
	glm::vec2 localVelocity;
	void CalcPressure();
	float density;
	std::vector<Particle*> neighbors;
	glm::vec2 pos;
	int index;
	glm::ivec2 gridCoords;
private: 
	float PressurePi(float pi);
	glm::vec2 fPressure();
	glm::vec2 fViscosity();
	glm::vec2 calcForces();
	glm::vec2 fOther();
	glm::vec2 dPi;
	glm::vec2 pressure;
	glm::vec2 pressureForce;
	float pressurePi;


};

