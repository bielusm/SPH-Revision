#define _USE_MATH_DEFINES 
#include <ATLComTime.h>
#include "Kernel.h"
#include "Constants.h"

//http://matthias-mueller-fischer.ch/publications/sca03.pdf
float Kernel::poly6(float r)
{
	if (0 <= r && r <= hVal)
	{
		const float  a = 315.0f / (64.0f * M_PI * pow(hVal, 9));
		const float b = pow(hVal, 2) - pow(pow(r, 2), 3);
		return a * b;
	}
	else
	{
		return 0;
	}
}

//float Kernel::viscosityGrad(float r)
//{
//	if (abs(r) > hVal)
//		return 0;
//	float c = 15.0f / (2.0f * M_PI * pow(hVal, 3));
//	float v = -(3 * abs(r) / 2 * pow(hVal, 3)) + (2 / pow(hVal, 2)) - (hVal / (2 * pow(abs(r), 3)));
//	return c * v;
//}

float Kernel::viscosityLap(float r)
{
	if (r < hVal&& r > 0)
		return 45.0f / (M_PI * pow(hVal, 6)) * (hVal - r);
	else
		return 0;
}

//from http://www8.cs.umu.se/kurser/TDBD24/VT06/lectures/sphsurvivalkit.pdf
float Kernel::spikyGrad(float r)
{
	if (r <= hVal && r >= 0)
		return -45.0f / (M_PI * pow(hVal, 6)) * pow(hVal - r, 2) * r;
	else
			return 0;
}
//float Kernel::W(float q)
//{
//	float fq;
//	if (0 <= q && q < 1)
//	{
//		fq = 2.0f / 3.0f - pow(q, 2) + 1.0f / 2.0f * pow(q, 3);
//		fq *= 10.0f / 7.0f * M_PI;
//	}
//	else if (1 <= q && q < 2)
//	{
//		fq = 1.0f / 6.0f * pow(2.0f - q, 3);
//		fq *= 10.0f / 7.0f * M_PI;
//	}
//	else
//	{
//		fq = 0;
//	}
//	float wq = (1.0f / pow(hVal, d)) * fq;
//	return wq;
//}

//float Kernel::WLaplacian(float q)
//{
//	float fq;
//	if (0 < q && q < 1)
//	{
//		fq = 3 * q - 2;
//	}
//	else if (1 <= q && q < 2)
//	{
//		fq = 3 * (2 - q);
//	}
//	else
//	{
//		return 0;
//	}
//	float wq = (1.0f / pow(hVal, d)) * 10.0f / (7.0f * M_PI) * fq;
//	return wq;
//}

//I am just taking the derivativeof W (m4 cubic spline) 
//derived from https://cg.informatik.uni-freiburg.de/publications/2014_EG_SPH_STAR.pdf eq 5
//float Kernel::Wgradient(float q)
//{
//	float fq;
//	if (0 < q && q < 1)
//	{
//		fq = (-2 * q) + (3.0f * pow(q, 2) / 2.0f);
//	}
//	else if (1 <= q && q < 2)
//	{
//		fq = 1.0f / 6.0f * pow(3 * (2 - q), 2) * (-1);
//	}
//	else
//	{
//		return 0;
//	}
//	float wq = (1.0f / pow(hVal, d)) * 10.0f / (7.0f * M_PI) * fq;
//	return wq;
//}


