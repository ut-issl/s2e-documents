# Specification of Component class

## 1.  Overview
1. Functions
  - The `Component` class is an abstract class to handle the electrical power and the update timing of components.
  - This class has two virtual functions: `MainRoutine` and `FastUpdate`. Both are called periodically. Users can select the functions according to the required calling period.
    + The `MainRoutine` function is the components' main function. Most of the processing is handled in this function.
    + The `FastUpdate` function handles the processes that need to be computed in a high-speed cycle. So, users will use this function only when high-frequency disturbances need to be calculated (e.g., RW jitter).

2. Related Files
  - Main file: `component.hpp`, `component.cpp`

3. How to use
  - Inherit this class by the user's component class.
  - The `ReactionWheel` in `S2E_CORE` is useful as a usage example of the `FastUpdate`.

## 2. Explanation of Algorithm
1. Constructor
    1. overview
       - Users can set component update `prescaler` and power port. 
    2. inputs
       - `prescaler`
         + `prescaler` determines the execution cycle of the `MainRoutine` function.
         + The period of `MainRoutine` equals to `SimTime::compo_update_interval_sec` $\times$ `prescaler`.
       - `clock_gen`
         + `clock_gen` is an instance that simulates the clock of a component.
         + Users do not need to care about this.
       - `power_port`
         + `power_port` is an instance that simulates the power supply
       - `fast_prescaler`
         + `fast_prescaler` determines the execution cycle of the `FastUpdate` function.
         + The period of `FastUpdate` equals to `SimTime::compo_update_interval_sec` $\times$ `fast_prescaler`.
         + If you don't need to use `FastUpdate`, you don't need to specify this (it is set to 1 by default).
    3. algorithm
       - N/A
    4. note
       - N/A

2. `MainRoutine`
    1. overview
       - Components' main function
    2. inputs
       - `time_count`
         + `time_count` is incremented each time the `Tick` function is called.
         + Users can use this timing information when they need for their components.
    3. algorithm
       - N/A 
   4. note
       - All the components have to override the `MainRoutine` function.

3. `FastUpdate`
    1. overview
       - This function handles the processes that need to be computed in a high-speed cycle.
    2. inputs
       - N/A
    3. algorithm
       - N/A 
    4. note
       - `FastUpdate` function is not a pure virtual function, so components without fast calculation do not need to override this function.
       - As explained in the `FastTick` section, `ITickable::needs_fast_update_` flag must be true to call `FastUpdate`. So, if users want to use `FastUpdate`, call `ITickable::SetNeedsFastUpdate(true)` in the constructor of each component.

4. `Tick`
    1. overview
       - This function executes `MainRoutine`.
       - `ClockGenerator` class calls this function.
    2. inputs
       - `count`
         + `count` is incremented each time the `Tick` function is called.
    3. algorithm
       - Execute `MainRoutine` when the `count` is divisible by the `prescaler`. By this mechanism, the execution period of `MainRoutine` is divided.
    4. note
       - N/A

4. `FastTick`
    1. overview
       - This function executes `FastUpdate`.
       - `ClockGenerator` class calls this function.
    2. inputs
       - `count`
         + `count` is incremented each time the `FastTick` function is called.
    3. algorithm
       - Execute `FastUpdate` when the `count` is divisible by the `fast_prescaler`. By this mechanism, the execution period of `FastUpdate` is divided.
    4. note
       - `ITickable::needs_fast_update_` flag must be true to call `FastUpdate`. So, if you want to use `FastUpdate`, call `ITickable::SetNeedsFastUpdate(true)` in the constructor of each component.

## 3. Results of verifications
- N/A

## 4. References
- N/A
