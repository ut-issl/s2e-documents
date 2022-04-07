# Specification for Orbit Propagation with Encke's Method

## 1.  Overview

1. functions
   - The `EnckeOrbitPropagation` class calculates the satellite position and velocity with Encke's method including disturbances and controlled accelerations by the satellite.

2. files
   - src/Dynamics/Orbit/EnckeOrbitPropagation.cpp, .h

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
