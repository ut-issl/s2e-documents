# Specification of PCU

## 1.  Overview
1. Functions
   - This is a base class of power control units and manages multiple `PowerPorts`.
2. Related files
   - Main file: `PCU.cpp, .h`
   - Related file: `PowerPort.cpp, .h`
3. How to use
   - **Example**: The `SampleComponents` in the `S2E_CORE_OSS/Simulation/Spacecraft/SampleSpacecraft` is useful to know how to use this class.
   - Users can make their original `PCU` class by inheriting this base class.
   - Users need to override the `MainRoutine`, `GetLogHeader`, and `GetLogValue` functions to define the behavior of their PCUs. 
## 2. Explanation of Algorithm
1. ConnectPort
   1. overview
      - This function makes a new `PowerPort`.
   2. inputs and outputs
      - Inputs: the port ID and the arguments for `PowerPort`
      - Outputs: the error code (0 is a success, -1 is an error)
   3. algorithm
      - Make a new `PowerPort` when the port ID is not used.
   4. note: N/A
1. ClosePort
   1. overview
      - This function deletes the designated `PowerPort`.
   2. inputs and outputs
      - Inputs: the port ID.
      - Outputs: the error code (0 is a success, -1 is an error).
   3. algorithm
      - Delete the designated `PowerPort` when the port still exists.
   4. note: N/A

## 3. Results of verifications
N/A

## 4. References
N/A
