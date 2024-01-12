# Specification documents for Spacecraft

## 1.  Overview

### 1. Functions
- The `Spacecraft` class is the base class to define the following basic features of spacecraft.
  - Component information
    - Clock Generator
    - The base class of components (`InstalledComponents`)
  - Dynamics information
    - Attitude
    - Orbit
    - Thermal
    - Relative Information
  - Local environment
  - Disturbance
  - Structure
- Users can make user defined spacecraft by inheriting this class.

### 2. Related files
- `src/simulation/spacecraft/spacecraft.cpp, .hpp`
  - The `Spacecraft` class is defined here.
- `src/simulation/spacecraft/sample_spacecraft/sample_spacecraft.cpp, .hpp`
  - An example to make user defined spacecraft with the `Spacecraft` class.

### 3. How to use
- See [Sample Spacecraft](./Spec_SampleSpacecraft.md)
- Usually, users just need to consider the user defined components. The disturbance, dynamics of the spacecraft, and etc are already considered in this base class.

## 2. Explanation of Algorithm
### 1. `Initialize` function
#### 1. overview
- Initialize all members
- There are two functions with same name
  - One is for single satellite case
  - The other is for multiple satellite case to consider relative information

### 1. `Update` function
#### 1. overview
- Update states or calculations for spacecraft

#### 2. inputs and outputs
- Input
  - Simulation time
- Output
  - NA

#### 3. algorithm
1. Clear the force and torque acting on the spacecraft to zero.
1. Update the local environment around the spacecraft
    - The previous spacecraft position and attitude are used.
1. Update the disturbance acting on the spacecraft
    - The local environment information and the previous spacecraft position and attitude are used.
1. Update the components behavior mounted on the spacecraft
    - The components measure the state or generate force/torque.
1. Add force and torque acting on the spacecraft
    - The force and torque from the disturbances
    - The force and torque from the components
1. Propagate the dynamics of the spacecraft
    - Attitude and Orbit

## 3. Results of verifications
NA

## 4. References
NA
