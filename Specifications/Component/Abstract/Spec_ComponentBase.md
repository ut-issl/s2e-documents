# Specification of ComponentBase class

## 1.  Overview
1. Functions
    - The `ComponentBase` class is an abstract class to handle the electrical power and the update timing of components.
    -  This class has two virtual functions: `MainRoutine` and `FastUpdate`. Both are called periodically. Users can select the functions according to the required calling period.
        + The `MainRoutine` function is the components' main function. Most of the processing is handled in this function.
        + The `FastUpdate` function handles the processes that need to be computed in a particularly fast cycle. So, you will use this function only when high-frequency disturbances need to be calculated (e.g., RW jitter).

2. Related Files
    - Main file: `ComponentBase.h`, `ComponentBase.cpp`

3. How to use
    - Inherit this class by your component class.
    -  The `RWModel` in `S2E_CORE_OSS` is useful as a usage example of fast update.

## 2. Explanation of Algorithm
1. Constructor
    1. overview
        - Users can set component update prescaler and power port. 
    2. inputs
        - prescaler
            + parameter to divide the execution cycle of the component
            + This determines the execution cycle of `MainRoutine`.
            + The period of `MainRoutine` equals to `SimTime::compo_update_interval_sec` $`\times`$ `prescaler`.
        - clock generator
            + an instance that simulates the clock of a component
            + Basically, users don't need to care about this.
        - power port
            + an instance that simulates the power supply
        - fast prescaler
            + parameter to divide the execution cycle of the component
            + This determines the execution cycle of `FastUpdate`.
            + The period of `FastUpdate` equals to `SimTime::compo_update_interval_sec` $`\times`$ `fast_prescaler`.
            + If you don't need to use `FastUpdate`, you don't need to specify this (it is set to 1 by default).
    3. algorithm
        - N/A
    4. note
        - N/A

2. `MainRoutine`
    1. overview
        - components' main function
    2. inputs
        - timer count
            + value that incremented each time the `Tick` function is called
            + Not currently in use
    3. algorithm
      - N/A 
   4. note
      - All the components have to override the `MainRoutine` function.

3. `FastUpdate`
    1. overview
        - function to handles the processes that need to be computed in a particularly fast cycle
    2. inputs
        - N/A
    3. algorithm
        - N/A 
    4. note
        - `FastUpdate` function is not an pure virtual function, so components without fast calculation don't need to override the `FastUpdate` function.
        - As explained in the `FastTick` section, `ITickable::needs_fast_update_` flag must be true to call `FastUpdate`. So, if you want to use `FastUpdate`, call `ITickable::SetNeedsFastUpdate(true)` in the construstor of each component.

4. `Tick`
    1. overview
        - function to execute `MainRoutine`
        - `ClockGenerator` class call this function.
    2. inputs
        - timer count
            + value that incremented each time the `Tick` function is called
    3. algorithm
        - Execute `MainRoutine` only if `count` is divisible by `prescaler`. By this mechanism, the execution period of `MainRoutine` is divided.
    4. note
        - N/A

4. `FastTick`
    1. overview
        - function to execute `FastUpdate`
        - `ClockGenerator` class call this function.
    2. inputs
        - timer count
            + the value that incremented each time the `Tick` function is called
    3. algorithm
        - Execute `FastUpdate` only if `count` is divisible by `fast_prescaler`. By this mechanism, the execution period of `FastUpdate` is divided.
    4. note
        - `ITickable::needs_fast_update_` flag must be true to call `FastUpdate`. So, if you want to use `FastUpdate`, call `ITickable::SetNeedsFastUpdate(true)` in the construstor of each component.

## 3. Results of verifications
- N/A

## 4. References
- N/A
