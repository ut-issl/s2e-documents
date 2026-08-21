# Specification documents for Sample Spacecraft

## 1.  Overview

### 1. Functions
- The `SampleSpacecraft` class is is an example of making the user defined spacecraft with the `Spacecraft` class.

### 2. Related files
- `src/simulation_sample/spacecraft/sample_spacecraft.cpp, .hpp`
  - The `SampleSpacecraft` class is defined here.
- `src/simulation/spacecraft/spacecraft.cpp, .hpp`
  - The `Spacecraft` class is defined here.
- `src/simulation_sample/case/sample_case.cpp, .hpp`
  - The instance of the `SampleSpacecraft` class is made in this class.


## 2. How to make user defined spacecraft
- `sample_spacecraft.hpp`
  - Define user defined ground station class. We use `SampleSpacecraft` class here.
    - Users can name freely like `Equuleus`, `UtSpacecraft`, and others.
  - Inherit the `Spacecraft` class.
    - You need to define override functions for all pure virtual functions of the `Spacecraft` class.
  - Add components for spacecraft if need.

- `sample_spacecraft.cpp`
  - Write detailed process of the override functions
  - Constructor
    - Initialize `Spacecraft` and make an instance of `SampleComponents` as installed components.
  - Other functions
    - Usually users don't need to care other functions for normal case.

## 3. Results of verifications
NA

## 4. References
NA
