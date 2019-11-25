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

