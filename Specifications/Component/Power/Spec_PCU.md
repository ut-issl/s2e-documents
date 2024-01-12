# Specification of PowerControlUnit class

## 1.  Overview
### 1. Functions
- `PowerControlUnit` class is a base class of power control units and manages multiple `PowerPorts`.

### 2. Related files
- Main file: `power_control_unit.cpp, .hpp`
- Related file: `power_port.cpp, .hpp`

### 3. How to use
- **Example**: The `sample_components` in the `s2e-core/simulation_sample/spacecraft` is useful to know how to use this class.
- Users can make their original `PowerControlUnit` class by inheriting this base class.
- Users need to override the `MainRoutine`, `GetLogHeader`, and `GetLogValue` functions to define the behavior of their PCUs. 

## 2. Explanation of Algorithm
### 1. ConnectPort
#### 1. overview
- This function makes a new `PowerPort`.

#### 2. inputs and outputs
- Inputs: the port ID and the arguments for `PowerPort`
- Outputs: the error code (0 is a success, -1 is an error)

#### 3. algorithm
- Make a new `PowerPort` when the port ID is not used.

#### 4. note: N/A

### 2. ClosePort
#### 1. overview
- This function deletes the designated `PowerPort`.

#### 2. inputs and outputs
- Inputs: the port ID.
- Outputs: the error code (0 is a success, -1 is an error).

#### 3. algorithm
- Delete the designated `PowerPort` when the port still exists.

#### 4. note: N/A

## 3. Results of verifications
N/A

## 4. References
N/A
