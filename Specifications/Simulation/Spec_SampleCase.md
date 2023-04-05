# Specification documents for Sample Case

## 1.  Overview

1. Functions
   - The `SampleCase` class is an example of making the user defined scenario with the `SimulationCase` class.

2. Related files
   - `src/simulation_sample/case/sample_case.cpp, .hpp`
     - The `SampleCase` class is defined here.
   - `src/simulation/case/simulation_case.cpp, .hpp`
     - The `SimulationCase` class is defined here.
   - `src/s2e.cpp`
     - The instance of the `SampleCase` class is made in this main function.

## 2. How to make user defined simulation scenario
- `sample_case.hpp`
  - Define user defined simulation case class. We use `SampleCase` class here.
  - Inherit the `SimulationCase` class.
    - Users need to define override functions for all pure virtual functions of the `SimulationCase` class.
  - Add spacecraft and/or ground station as users need into the member variables.
    - If users simulate multiple spacecraft, users can add several spacecraft here.
      - Multiple spacecraft case, you can refer the [s2e-ff](https://github.com/ut-issl/s2e-ff)

- `sample_case.cpp`
  - Write detailed process of the override functions
  - Constructor
    - Usually, users just need to initialize the constructor of `SimulationCase`.
  - Destructor
    - Users need to `delete` your defined members `spacecraft` and `ground_station`.
  - `InitializeTargetObjects` function
    - You have to make instances of your `spacecraft` and `ground_station` class here.
    - You also need to register log output by `LogSetup` function.
  - `UpdateTargetObjects` function
    - This function is called in the `SimulationCase::Main` function.
    - Users can update their spacecraft and ground station classes here.
  - `GetLogHeader` and `GetLogValue` functions
    - These functions are used in the Monte-Carlo simulation mode. For the normal mode, you don't need to care.
    - The log definition written here is saved at the start and end timing of every simulation case of the Monte-Carlo simulation.

## 3. Results of verifications
NA

## 4. References
NA
