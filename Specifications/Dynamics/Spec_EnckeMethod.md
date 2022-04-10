# Specification for Orbit Propagation with Encke's Method

## 1.  Overview

1. functions
   - The `EnckeOrbitPropagation` class calculates the satellite position and velocity with Encke's method including disturbances and controlled accelerations by the satellite.
   - This orbit propagation mode provides an accurate and efficient orbit calculation with disturbance forces.
   - We can also use it for an accurate relative orbit propagation, and the feature will be implemented soon.

2. files
   - src/Dynamics/Orbit/EnckeOrbitPropagation.cpp, .h
   - We use [KeplerOrbit](./Spec_KeplerOrbit.md) libraries to calculate the reference orbit.

3. How to use
   - Select `propagate_mode = ENCKE` in the spacecraft's ini file.
   - Set the value `init_position` and `init_velocity` in the ini file.
     - The units are `m`(meter) and `m/s`.
     - The frame is inertial frame, and the center is defined in the `PlanetSelect`.
   - Set the value of `error_tolerance`, which decides the threshold for the rectification.

## 2. Explanation of Algorithm
1. `EnckeOrbitPropagation::Initialize` function
   1. Overview
      - This function generates the initial value of the reference orbit and the difference orbit.

   2. Inputs and outputs
      - Input
        - $`\mu`$ : The standard gravitational parameter of the central body
        - $`t`$ : Time in Julian day
        - $`\boldsymbol{r}_{i}`$ : Initial position in the inertial frame
        - $`\boldsymbol{v}_{i}`$ : Initial velocity in the inertial frame
      - Output
        - The reference orbit
        - The difference as zero

   3. Algorithm
      - The reference orbit is initialized as the Kepler Orbit with `OrbitalElements::CalcOeFromPosVel` function. The detail of the function is described in [Specification for Kepler Orbit Propagation](./Spec_KeplerOrbit.md)

2. `EnckeOrbitPropagation::Propagate` function
   1. Overview
      - This function is the main algorithm of the Encke's method and calculates the orbit of the spacecraft.
      - The method separate the orbit to the reference and the difference. The reference is calculated with the Kepler orbit method as a two-body problem, and the difference is calculated including the disturbances.
        - $`\boldsymbol{r}_{ref}`$ : Reference orbit
        - $`\boldsymbol{\delta}`$ : Difference
      - Please refer the references to learn the original idea of the Encke's method.

   2. Inputs and outputs
      - Input
        - $`\boldsymbol{a}_d`$ : Acceleration
        - $`t`$ : Current time
      - Output
        - $`\boldsymbol{r}_{i}`$ : Initial position in the inertial frame
        - $`\dot{\boldsymbol{r}}_{i}`$ : Initial velocity in the inertial frame
        
   3. Algorithm
      1. Rectification
         - If the norm of the difference is larger than a tolerance, we need to update the reference orbit as the latest orbit information.
      2. Update reference orbit
         - The reference orbit is calculated with the Kepler orbit calculation method.
      3. Propagate the difference
         - Propagate the following differential equation. At this moment, we use the 4th order Runge-Kutta method as a propagator.
         ```math
         \ddot{\boldsymbol{\delta}} = -\frac{\mu}{r_{ref}^3}(\boldsymbol{\delta}+f(q)\boldsymbol{r})+\boldsymbol{a}_d\\
         f(q) = q \frac{q^2 + 3q + 3}{(1+q)^{1.5} + 1}\\
         q = \frac{\boldsymbol{\delta}\cdot(\boldsymbol{\delta}-2\boldsymbol{r}_i)}{r_i}
         ```


## 3. Results of verifications
TBW

## 4. References
- David A. Vallado, "Fundamental of Astrodynamics and Applications, Third Edition: Chapter 8. Special Perturbation Techniques", 2007.
- Simon P. Shuster, "A Survey and Performance Analysis of Orbit Propagators for LEO, GEO, and Highly Elliptical Orbits", 2017.
