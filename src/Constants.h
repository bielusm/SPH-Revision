#pragma once
#include <math.h>

//most of these starting parameters are from https://www10.cs.fau.de/publications/theses/2010/Staubach_BT_2010.pdf
#define d 2 // dimensionns
#define p0 998.29f //rest density 
#define k 3.0f //gas stiffness
#define vis 3.5f //viscosity
#define g glm::vec2(0.0f,-9.81f) //gravity

#define particleSize 0.2f

const float hVal = 3.0f * particleSize;

#define MAX_PARTICLES 3000

//IHMSEN M., CORNELIS J., SOLENTHALER B., HORVATH C., TESCHNER M.: Implicit incompressible SPH.IEEE
//Transactions on Visualization and Computer Graphicss
//found in https://cg.informatik.uni-freiburg.de/publications/2014_EG_SPH_STAR.pdf
const float mj = powf(2.0f / 3.0f * hVal, 3) * p0;