# Specification for Simulation Time

## 1.  Overview
1. Functions 
  + The `SimulationTime` class manages simulation time related information as follows.
    - Start time of the simulation scenario
    - Elapsed time of the simulation scenario
    - Current time of the simulation scenario
    - Update timing of calculations
      - Attitude update, orbit update, thermal update, component update
    - Update timing of log output and display output


2. Related files
  + `src/environment/global/simulation_time.cpp, .hpp`
    - `SimulationTime` class is defined. 
  - `src/environment/global/global_environment.cpp, .hpp`
    - `SimulationTime` class is used here as a member variable of `GlobalEnvironment` class.
  - `src/environment/global/initialize_global_environment.cpp, .hpp`
    - `SimulationTime` class is instanced here based on the `simulation_base.ini` file.


3. How to use
   - Call ` UpdateTime` function to increment time of the simulation scenario.
   - Users can get time related information by using the getter functions.

## 3. Explanation of Algorithm
- NA

## 4. Verification
- NA

## 5. References
- NA

