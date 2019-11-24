#pragma once
class Kernel
{
public:
	static float poly6(float r);
	static float viscosityGrad(float r);
	static float viscosityLap(float r);
	static float spikyGrad(float r);
	static float W(float q);
	static float WLaplacian(float q);
	static float Wgradient(float q);
};