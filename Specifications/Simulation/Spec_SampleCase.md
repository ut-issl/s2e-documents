# Specification documents for Sample Case

## 1.  Overview

1. Functions
   - The `SampleCase` class is an example to make user own scenario with the `SimulationCase` class.

2. Related files
   - `src/simulation/case/sample_case.cpp, .hpp`
     - The `SampleCase` class is defined here.
   - `src/simulation/case/simulation_case.cpp, .hpp`
     - The `SimulationCase` class is defined here.
   - `src/s2e.cpp`
     - The instance of the `SampleCase` class is made in this main function.

## 2. How to make own simulation scenario
- `SampleCase.hpp`
  - Define your own simulation case class. We use `SampleCase` class here.
  - Inherit the `SimulationCase` class.
    - You need to define override functions for all pure virtual functions of the `SimulationCase` class.
  - Add spacecraft and/or ground station as you need into the member variables.
    - If you simulate multiple spacecraft, you can add several spacecraft here.
      - Multiple spacecraft case, you can refer the [s2e-ff](https://github.com/ut-issl/s2e-ff)

- `SampleCase.cpp`
  - Write detailed process of the override functions
  - Constructor
    - Usually, you just need to initialize the constructor of `SimulationCase`.
  - Destructor
    - You need to `delete` your defined member `spacecraft` and `ground_station`.
  - `Initialize` function
    - You have to make instances of your `spacecraft` and `ground_station` class here.
    - You also need to register log out put by `LogSetup` function.
    - After the initial settings, you need to execute `WriteHeaders` function to write header information to the CSV output file.
    - In final, you can output the message to show the simulation starts.
  - `Main` function
    - The `Main` function has the while loop until the simulation end time is coming.
    - Before the loop, you need to reset the all states. This process is needed for the Monte-Carlo simulation mode.
    - In the loop, firstly, you need to write log information to the CSV output file.
    - After that, the `global_environment` update is needed.
    - Then, users can update their own spacecraft class and ground station class.
    - Finally, you can write debug message if need.
  - `GetLogHeader` and `GetLogValue` functions
    - These functions are used in the Monte-Carlo simulation mode. For the normal mode, you don't need to care.
    - The log definition written here is saved at the start and end timing of every simulation case of the Monte-Carlo simulation.

## 3. Results of verifications
NA

## 4. References
NA
