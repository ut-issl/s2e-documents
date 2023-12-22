# Specification documents for Installed Components

## 1.  Overview

### 1. Functions
- The `InstalledComponents` class is the base class to define the following interface functions for component list.
  - Force and torque generation
  - Log setup
- Users can make user defined component list by inheriting this class.

### 2. Related files
- `src/simulation/spacecraft/installed_components.cpp, .hpp`
  - The `InstalledComponents` class is defined here.
- `src/simulation/spacecraft/spacecraft.cpp, .hpp`
  - The `InstalledComponents` class is used here.
- `src/simulation/spacecraft/sample_spacecraft/sample_components.cpp, .hpp`
  - An example to make user defined component list with the `InstalledComponents` class.

### 3. How to use
- See [Sample Components](./Spec_SampleComponents.md)

## 2. Explanation of Algorithm
NA

## 3. Results of verifications
NA

## 4. References
NA
