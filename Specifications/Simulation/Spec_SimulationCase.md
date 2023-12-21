# Specification documents for Simulation Case

## 1.  Overview

### 1. Functions
- The `SimulationCase` class is the base class to define the simulation scenario.
- Users can make user defined simulation scenario by inheriting this class.

### 2. Related files
- `src/simulation/case/simulation_case.cpp, .hpp`
  - The `SimulationCase` class is defined here.
- `src/simulation/case/sample_case.cpp, .hpp`
  - An example to make user defined scenario with the `SimulationCase` class.
- `src/s2e.cpp`
  - The instance of the `SimulationCase` class is made in this main function.

### 3. How to use
- See the following documents
  - [How To Make New Simulation Scenario](../../Tutorials/HowToMakeNewSimulationScenario.md)
  - [Sample Case](./Spec_SampleCase.md.md)


## 2. Explanation of Algorithm
NA

## 3. Results of verifications
NA

## 4. References
NA
