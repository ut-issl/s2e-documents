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
TBW

## 3. Results of verifications
TBW

## 4. References
NA
