# How To Add Control Algorithms

## 1.  Overview
- In [How To Make New Components](./Tutorials/HowToMakeNewComponents.md) tutorial, we have newly made components emulating codes in [S2E_CORE_OSS](https://gitlab.com/ut_issl/s2e/s2e_core_oss) and add the new components into own simulation scenario.
- Now we can simulate the behavior of spacecraft **free motion** and emulate the behavior of sensors and actuators. 
- This tutorial explains how to add **Control Algorithm** into the simulation scenario. 
- For practical satellite project, we should implement the control algorithm as real flight software like [C2A](https://gitlab.com/ut_issl/c2a/c2a_core_oss) into the S2E. However, usually, using real flight software is overdoing for use cases as research, initial phase of satellite projects.
- So, we introduces the following three method, and users can choose the suitable method.
  - Direct: Directly control physical quantity without sensors, actuators, and their noises
    - For theoretical researches and preliminary analysis for satellite projects.
  - Component: Control using sensors and actuators without flight S/W frame work
    - For engineering researches and preliminary analysis for satellite projects. 
  - FlightSW: Control using sensors and actuators with flight S/W frame work
    - For actual satellite projects.
- Supported version of this document
  - S2E_CORE_OSS:c4c7cf6567c077f0918f07a9a82c2d7e4531ceb7

## 2. Direct method
- In this chapter, a simplest way to add control algorithm without sensors and actuators.
- This method directly measures satellite physical quantity, and directly generate torque and force acting on the satellite.
- To do that, users need to edit the `Update` function in the `UserSat.cpp`.
- The `UserSat` class already has satellite attitude, orbit, and local environment information since it inherits `Spacecraft` base class. So users can easily access these values.
- To measure physical quantities, users can use getter functions defined in `Attitude`, `Orbit`, and `LocalEnvironment` classes as `dynamics_->GetAttitude().GetOmega_b()`.
- To generate torque and force, users can use `dynamics_->AddTorque_b` and `dynamics_->AddForce_b`.
- The sample codes are in `SampleCodes/ControlAlgorithm/DirectMethod/`, and you can see very simple detumbling control with proportional control method.
- To use the sample code, you need to copy the `User_sat_with_control.cpp` and `User_sat_with_control.h` and build them instead of `User_sat.cpp`.
  - You need to edit `CMakeLists.txt` to add the copied `User_sat_with_control.cpp` to the `SOURCE_FILES`.
- By using the sample code, the following result is given.
    <img src="./figs/ControlAlgorithm_DirectControl_result1.png" alt="CA_DC_1" style="zoom: 80%;" />

## 3. Component method
- 


## 4. FlightSW method ~Control algorithm within C2A~
- TBW