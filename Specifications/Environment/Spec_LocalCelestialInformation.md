# Specification for Local Celestial Information

## 1.  Overview
1. Functions 
   - `LocalCelestialInformation` calculates the celestial bodies position and velocity on the spacecraft body-fixed frame.

2. Related files
   - `src/environment/local/local_celestial_information.cpp, .hpp`
     - `LocalCelestialInformation` class is defined. 
   - `src/environment/local/local_environment.cpp, .hpp`
     - `LocalCelestialInformation` class is used here as a member variable of `LocalEnvironment` class.
   - `src/environment/local/initialize_local_environment.cpp, .hpp`
     - `LocalCelestialInformation` class is instanced here based on the `.ini` file for the environment.
3. How to use
   - Call ` UpdateAllObjectsInformation` function to calculates the celestial bodies position and velocity.
   - Users can get calculated values by using the following functions:
     - Get celestial body position vector from the spacecraft position. Users need to set the body name as an argument.
       - `GetPositionFromSpacecraft_i_m`
       - `GetPositionFromSpacecraft_b_m`
     - Get center body position vector from the spacecraft position without any arguments.
       - `GetCenterBodyPositionFromSpacecraft_i_m`
       - `GetCenterBodyPositionFromSpacecraft_b_m`
   - To access the celestial body position in the inertial frame, users can use `GetGlobalInformation`
  
## 3. Explanation of Algorithm
1. `UpdateAllObjectsInformation` function
   1. overview
      - Convert the celestial bodies positions to the body frame from the inertial frame.

## 4. Verification
- NA

## 5. References
- NA

