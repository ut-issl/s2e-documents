# Specification for Orbit

## 1.  Overview

1. functions
   - The Orbit class calculates the position and velocity of satellites with the follwoing propagation mode.
     - KEPLER   : Kepler orbit propagation without disturbances and thruster maneuver
     - SGP4     : SGP4 propagation using TLE without thruster maneuver
     - RK4      : RK4 propagation with disturbances and thruster maneuver
     - ENCKE    : Encke orbit propagation with disturbances and thruster maneuver
     - RELATIVE : Relative dynamics (for formation flying simulation)
   - The KEPLER mode is the simplest and general for all users.
   - The SGP4 mode is useful for LEO satellites users without orbit control.
   - When users need to analyze the orbit disturbance force effect or the orbit control algorithm, the users should coose RK4 or ENCKE mode.
   - For multiple satellite operation, RELATIVE mode is useful.

2. files
   - `src/Dynamics/Orbit/Orbit.h`
	   - Definition of Orbit base class
   - `src/Interface/InitInput/Init_Orbit.cpp`
	   - Make an instance of orbit class.	

3. How to use
   - Make an instance of the orbit class in `Initialize` function in `Dynamics.cpp`
   - Select `propagate_mode` in the spacecraft's ini file
   - Set the orbit information in the ini file
     - You can see the details in the documents for each orbit propagation mode.
   - The definition of the coordinate system is decided in `PlanetSelect.ini`
   
## 2. Explanation of Algorithm
In the Orbit base class provides the following common functions for every propagator.

1. `UpdateAtt` function  
   The `UpdateAtt` function simply converts the velocity vector of the spacecraft (in ECI coordinate system) to body coordinate system notation using the argument: `Quaternion_i2b`.

2. `SetAcceleration_i`, `AddAcceleration_i`, `AddForce_i`, `AddForce_b` function  
   These functions provides the interface to include orbital disturbance or control forces.

2. `TransECIToGeo` function  
   The `TransECIGeo` function calculates latitude[rad], longitude[rad], and altitude[m] using the arguments: the current Julian day and the position vector of the spacecraft (in the ECI coordinate system). In the computation process, we use the SGP4 function `getwgsconst` to read the earth's radius and squareness for the calculation.  
   The latitude is calculated from the South Pole to the equator from -π/2 to 0[rad] and from the equator to the North Pole from 0 to π/2[rad], and the longitude is from 0 to 2π[rad] east of the Greenwich meridian. The altitude is in meters.

3. `TransECIToECEF` function  
   The `TransECIToECEF` function can convert the position and the velocity of the satellite from the ECI frame to the ECEF frame, which considers the earth's rotation.

## 3. Results of verifications
- The verification results are described in the document of each propagation method.

## 4. References
NA

