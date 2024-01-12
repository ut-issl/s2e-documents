# Specification documents for Ground Station

## 1.  Overview

### 1. Functions
- The `GroundStation` class is the base class to define the following basic feature of ground stations.
  - Position of the ground station
  - Minimum elevation angle
  - Visible flag for each spacecraft
- Users can make user defined ground station by inheriting this class.

### 2. Related files
- `src/simulation/ground_station/ground_station.cpp, .hpp`
  - The `GroundStation` class is defined here.
- `src/simulation/ground_station/sample_ground_station/sample_ground_station.cpp, .hpp`
  - An example to make user defined ground station with the `GroundStation` class.

### 3. How to use
- See [Sample Ground Station](./Spec_SampleGroundStation.md)


## 2. Explanation of Algorithm
NA

## 3. Results of verifications
NA

## 4. References
NA
