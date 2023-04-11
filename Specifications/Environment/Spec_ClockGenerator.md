# Specification for Clock Generator

## 1.  Overview
1. Functions 
  + The `ClockGenerator` generates clock for classes which inherit `ITickable`.
  + It is mainly used to manage update the component states since the `Component` class inherits `ITickable`
  + This class is not managed by `GlobalEnvironment` class. The `Spacecraft` class directly has the instance of this class and execute the update function.

2. Related files
  + `src/environment/global/clock_generator.cpp, .hpp`
  + `src/components/base/interface_tickable.hpp`

3. How to use
  + Make an instance of a class which inherit `ITickable`. Then, the instance is automatically registered to the component list `ClockGenerator::components_`.
  + The `Spacecraft` class calls the `UpdateComponents` function to update the states of the registered components.

## 3. Explanation of Algorithm
1. `UpdateComponents` function
   1. overview
      - Call `TickToComponents` when the component update timing flag is `true`.

1. `TickToComponents` function
   1. overview
      - Increment count and execute the `ITickable::Tick` or `ITickable::FastTick` function.
      - They call the `component::MainRoutine` and  `component::FastUpdate` functions, respectively.

## 4. Verification
- NA

## 5. References
- NA

