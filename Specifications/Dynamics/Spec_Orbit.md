# Specification for Orbit

## 1.  Overview

### 1. functions
- The `Orbit` class calculates the position and velocity of satellites with the following propagation mode.
  - `KEPLER`   : Kepler orbit propagation without disturbances and thruster maneuver
  - `SGP4`     : SGP4 propagation using TLE without thruster maneuver
  - `RK4`      : RK4 propagation with disturbances and thruster maneuver
  - `ENCKE`    : Encke's orbit propagation with disturbances and thruster maneuver
  - `RELATIVE` : Relative dynamics (for formation flying simulation)
- The `KEPLER` mode is the simplest and general for all users.
- The `SGP4` mode is useful for LEO satellites users without orbit control.
- When users need to analyze the orbit disturbance force effect or the orbit control algorithm, the users should choose `RK4` or `ENCKE` mode.
- For multiple satellite operation, `RELATIVE` mode is useful.`

### 2. files
- `src/dynamics/orbit/orbit.hpp, cpp`
  - Definition of `Orbit` base class
- `src/dynamics/orbit/initialize_orbit.hpp, .cpp`
  - Make an instance of orbit class.	

### 3. How to use
- Make an instance of the orbit class in `Initialize` function in `dynamics.cpp`
- Select `propagate_mode` in the spacecraft's ini file(eg. `sample_spacecraft.ini`).
- Select `initialize_mode` in the spacecraft's ini file(eg. `sample_spacecraft.ini`).
  - This setting works only for `RK4`, `KEPLER`, and `ENCKE` mode.
- Set the orbit information in the ini file
  - You can see the details in the documents for each orbit propagation mode.
- The definition of the coordinate system is decided at `[CELESTIAL_INFORMATION]` section in `sample_simulation_base.ini`.
   
## 2. Explanation of Algorithm
In the Orbit base class provides the following common functions for every propagator.

### 1. `UpdateByAttitude` function  
- The `UpdateByAttitude` function simply converts the velocity vector of the spacecraft (in ECI coordinate system) to body coordinate system notation using the argument: `quaternion_i2b`.

### 2. `SetAcceleration_i_m_s2`, `AddAcceleration_i_m_s2`, `AddForce_i_N`, `AddForce_b_N` function  
- These functions provides the interface to include orbital disturbance or control forces.

### 2. `TransformEcefToGeodetic` function  
- The `TransformEcefToGeodetic` function calculates latitude[rad], longitude[rad], and altitude[m]. Currently, we use the `Geodetic` class to calculate the information.   

### 3. `TransformEciToEcef` function  
- The `TransformEciToEcef` function can convert the position and the velocity of the satellite from the ECI frame to the ECEF frame, which considers the earth's rotation.

## 3. Results of verifications
- The verification results are described in the document of each propagation method.

## 4. References
NA
