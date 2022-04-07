# Specification for Kepler Orbit Propagation

## 1.  Overview

1. functions
   - The `KeplerOrbit` class calculates the satellite position and velocity with the simple two-body problem. We ignored any disturbances and generated forces by the satellite.
   - This orbit propagation mode provides the simplest and fastest orbit calculation for any orbit(LEO, GEO, Deep Space, and so on.).

2. files
   - src/Dynamics/Orbit/KeplerOrbitPropagation.cpp, hpp
   - src/Library/Orbit/KeplerOrbit.cpp, hpp
   - src/Library/Orbit/OrbitalElements.cpp, hpp
   - src/Interface/InitInput/Init_Orbit.cpp

3. How to use
   - Select `propagate_mode = KEPLER` in the spacecraft's ini file.
   - Choose a way to define the orbit.
     - Defined by initial position and velocity.
       - Select `init_mode_kepler = INIT_POSVEL`
       - Set the value `init_position` and `init_velocity` in the ini file.
         - The units are `m`(meter) and `m/s`.
         - The frame is inertial frame, and the center is defined in the `PlanetSelect`.
     - Defined by the orbital elements.
       - Select `init_mode_kepler = INIT_OE`
       - Set the value of following orbital elements
         ```
         semi_major_axis_m
         eccentricity
         inclination_rad
         raan_rad (Right Ascension of the Ascending Node)
         arg_perigee_rad (Argument of Perigee)
         epoch_jday
         ```
   
## 2. Explanation of Algorithm
TBW

## 3. Results of verifications
TBW

## 4. References
NA
