# Specification for Celestial Information

## 1.  Overview
1. Functions 
   - `CelestialInformation` manages the celestial bodies position and velocity on the inertial frame.
   - This class also manages the celestial body information like the gravity constant, the radius, and the rotation.
   - The actual calculations are executed by CSPICE or `CelestialRotation`, and this class just calls their functions.

2. Related files
   - `src/environment/global/celestial_information.cpp, .hpp`
     - `CelestialInformation` class is defined. 
   - `src/environment/global/global_environment.cpp, .hpp`
     - `CelestialInformation` class is used here as a member variable of `GlobalEnvironment` class.

3. How to use
   - Call ` UpdateAllObjectsInformation` function to calculates the celestial bodies position and velocity.
   - Users can get calculated values by using the following functions:
     - `GetPositionFromCenter_i_m`
       - You can select celestial ID or name for the arguments
     - `GetVelocityFromCenter_i_m_s`
       - You can select celestial ID or name for the arguments
     - `GetGravityConstant_m3_s2`
       - argument is celestial body name
     - `GetCenterBodyGravityConstant_m3_s2`
     - `GetRadii_m` or `GetRadiiFromName_m`
       - You can select celestial ID or name for the arguments
     - `GetMeanRadiusFromName_m`
       - argument is celestial body name
  
## 3. Explanation of Algorithm
1. `UpdateAllObjectsInformation` function
   1. overview
      - Actual calculation is executed by the CSPICE library. This function just calls the CSPICE functions.

## 4. Verification
- NA

## 5. References
- NA

