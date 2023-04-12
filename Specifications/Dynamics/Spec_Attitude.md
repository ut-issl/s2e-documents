# Specification for Attitude

## 1.  Overview

1. functions
   - The `Attitude` class calculates the attitude and angular velocity of a satellite with the following propagation modes.
     - RK4        : 4th order Runge-Kutta propagation with disturbances and actuators output torque. Users use this mode to consider attitude control algorithm.
     - CONTROLLED : Satellite attitude is perfectly controlled to the setting direction. This mode doesn't consider the disturbances and actuators output torque. Users use this mode when they focus on orbit dynamics or mission analysis.

2. files
   - `src/dynamics/attitude/attitude.hpp, .cpp`
	   - Definition of `Attitude` base class
   - `src/dynamics/attitude/initialize_attitude.hpp, .cpp`
	   - Make an instance of `Attitude` class.	
   
3. How to use
   - Make an instance of the attitude class in `Initialize` function in `dynamics.cpp`
     - Usually, users don't care this process.
   - Select `propagate_mode` in the spacecraft's `ini` file.
     - `RK4` or `CONTROLLED` described above.
   - Select `initialize_mode` in the spacecraft's `ini` file.
     - When users select `propagate_mode = CONTROLLED`, `initialize_mode` is not used, and the attitude is initialized with [CONTROLLED_ATTITUDE] settings.
     - When users select `propagate_mode = RK4`, `initialize_mode` is used.
       - `initialize_mode = MANUAL`
         - Initial attitude is defined by `initial_quaternion_i2b` and `initial_angular_velocity_b_rad_s`.
       - `initialize_mode = CONTROLLED`
         - Initial attitude is defined by [CONTROLLED_ATTITUDE] settings. By using this mode, users can easily choose the required initial quaternion without complicated calculation.
   
## 2. Explanation of Algorithm
In the `Attitude` base class provides the following common functions for every propagator.

- Getter functions
  - The base class has several getter functions for the member variables.

- `CalcAngularMomentum`
  - This function calculates angular momentum of spacecraft including internal actuators such as reaction wheels.

## 3. Results of verifications
- The verification results are described in the document of each propagation method.

## 4. References
NA

