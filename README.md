# SPH-Revision
A fluid simulation using the smoothed-particle hydrodynamics method.

## Compiling and Use
1. Clone this repo
2. Compile and run solution in visual studio

## Dependencies Used
1. [GLM](https://glm.g-truc.net/0.9.9/index.html)
2. [SFML](https://www.sfml-dev.org)

## Demo 
[Demo Video](https://youtu.be/nFGOnyIo52U)

## Parameters 
Various parameters can be adjusted in the file constants.h to give different simulations

```hVal``` The distance that particles can affect each other

```vis``` A constant that determines the viscosity of the liquid. Higher number = higher viscosity.

```g``` The force of gravity.

```p0``` The rest density of the particles.

```MAX_PARTICLES``` The total amount of particles in the simulation.

```mj``` The mass of the particles

## The Algorithm
This simulation is implemented from algorithm #1 in the paper [SPH Fluids in Computer Graphics](https://cg.informatik.uni-freiburg.de/publications/2014_EG_SPH_STAR.pdf).
```
For each timestep
  For each particle
    1. Find neighboring particles
  For each particle
    Use neighboring particles to calculate density
    Use density to calculate pressure
  For each particle
    Calculate the forces of Pressure, Viscosity and Gravity on each particle
    Calculate the velocity of each particle from the forces
    Calculate the position of each particle from the velocity
```
## References
For this simulation I used these references as well as many more:

[SPH Fluids in Computer Graphics](https://cg.informatik.uni-freiburg.de/publications/2014_EG_SPH_STAR.pdf)

[Particle-Based Fluid Simulation for Interactive Application](http://matthias-mueller-fischer.ch/publications/sca03.pdf)

[SPH survival Kit](http://www8.cs.umu.se/kurser/TDBD24/VT06/lectures/sphsurvivalkit.pdf)

[Fluid Simulation using Smoothed Particle Hydrodynamics](https://nccastaff.bournemouth.ac.uk/jmacey/MastersProjects/MSc15/06Burak/BurakErtekinMScThesis.pdf)

[Implementing SPH in 2D](https://bigtheta.io/2017/07/08/implementing-sph-in-2d.html)
