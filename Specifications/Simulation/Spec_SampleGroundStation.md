# Specification documents for Sample Ground Station

## 1.  Overview

### 1. Functions
- The `SampleGroundStation` class is is an example of making the user defined ground station with the `GroundStation` class.

### 2. Related files
- `src/simulation_sample_/ground_station/sample_ground_station.cpp, .hpp`
  - The `SampleGroundStation` class is defined here.
- `src/simulation/ground_station/ground_station.cpp, .hpp`
  - The `GroundStation` class is defined here.
- `src/simulation_sample/case/sample_case.cpp, .hpp`
  - The instance of the `SampleGroundStation` class is made in this class.

## 2. How to make user defined ground station
- `sample_ground_station.hpp`
- Define user defined ground station class. We use `SampleGroundStation` class here.
- Users can name freely like `UtGroundStation`, `DsnGroundStation`, and others.
- Inherit the `GroundStation` class.
- You need to define override functions for all pure virtual functions of the `GroundStation` class.
- Add components for ground station if need.

- `sample_ground_station.cpp`
- Write detailed process of the override functions
- Constructor
- Initialize `GroundStation` and call the `SampleGroundStation::Initialize` function.
- Destructor
- Delete components.
- `LogSetup` function
- Set log you need.
- `Update` function
- Call the `GroundStation::Update` function.
- Call the ground station component's `Update` functions.

## 3. Results of verifications
NA

## 4. References
NA
