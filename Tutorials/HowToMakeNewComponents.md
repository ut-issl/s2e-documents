# How To Make New Components

## 1.  Overview

- In [How To Add Components](./Tutorials/HowToAddComponents.md) tutorial, we have added existing components to own simulation scenario.
- This tutorial explains how to make new components into [S2E_CORE_OSS](https://gitlab.com/ut_issl/s2e/s2e_core_oss) .

## 2. Overview of S2E/Components

- Components emulating source codes are stored in `S2E_CORE_OSS/src/Component` directory. 
- All components need to inherit a base class `ComponentBase` for general function of components, and most of the components also inherit a base class `ILoggable` for a log output function.
- `ComponentBase` class
  - The base class has an important virtual function `MainRoutine`, and subclass need to define it
    - When an instance of the component class is created, the `MainRoutine` is registered in `TickToComponent` and it will be automatically executed in `UserSat` class.
    - The main features such as observation, generate force, noise addition, communication, etc... should be written in this function
  - Power related functions
    - `SetPowerState`, `GetCurrent` are power related functions. If you want to emulate power consumption and switch control, you need to used the functions
- `ILoggable` class
  - The base class has two important virtual functions `GetLogHeader` and `GetLogValue` for CSV log output.
  - These functions are registered into log output list when the components is added in `UserComponents::CompoLogSetUp` 

## 3. Make a simple clock sensor

- This chapter explains how to make a simple clock sensor, which observe the simulation elapsed time with bias noise.

1. Copy `ClockSensor.cpp` and `ClockSensor.h` to the directory `S2E_CORE_OSS/src/Components/Abstract` from `Documents_OSS/Tutorials/SampleCode/ClockSensor`

2. Edit `CMakeList.txt` in the directory `S2E_CORE_OSS/src/Components`

   - Add a new line `Abstract/ClockSensor.cpp` the bottom line of `Abstract/StateMachine.h`

3. Compile `S2E_USER` and check there is no error.

4. Edit `User_component.h` and `User_component.cpp` as referring [How To Add Components](./Tutorials/HowToAddComponents.md)

   - The constructor of the `ClockSensor` requires the argument of `SimTime` class, so following description is needed.

     ```c++
     clock_sensor_ = new ClockSensor(config_->simTime);
     ```

5. Compile `S2E_USER` and execute it

6. Check the log file to confirm the output of the `clock_sensor`

## 4. Make an initialize file for the clock sensor

- Usually, we want to change parameters of components such as noise properties, mounting coordinate, and so on. So next step, how to make an initialize file for the `ClockSensor` is explained.

1. Edit `ClockSensor.cpp` and `ClockSensor.h` to add a new constructor

   - Add following line at the bottom of `ClockSensor(SimTime* sim_time_);` in `ClockSensor.h` 

     ```c++
     ClockSensor(SimTime* sim_time_, const double bias_sec_);
     ```

   - Add following description at the bottom of the old constructor in `ClockSensor.cpp` 

     ```c++
     ClockSensor::ClockSensor(SimTime* sim_time_, const double bias_sec_) : ComponentBase(), sim_time(sim_time_)
     {
       time_output_sec = 0.0;
       bias_sec = bias_sec_;
     }
     ```

2. Copy `Init_ClockSensor.cpp` into `S2E_CORE_OSS/src/InitInput/InitComponent` from `Tutorial/SampleCodes/ClockSensor`

3. Edit ``S2E_CORE_OSS/src/InitInput/CMakeList.txt` to compile the `InitClockSensor.cpp`

   - Add following line at the bottom of `InitComponent/InitUWBSensor.cpp` in the `CMakeList.txt`

     ```C++
     InitComponent/Init_ClockSensor.cpp
     ```

4. Edit `initialize.h` to add the following description at the bottom of the file

   ```c++
   class ClockSensor;
   ClockSensor InitClockSensor(SimTime* sim_time_, string file_name);
   ```

5. Edit `UserComponents` function in  `User_components.cpp` as follows

   ```c++
   UserComponents::UserComponents(const Dynamics* dynamics, const SimulationConfig* config)
     :dynamics_(dynamics), config_(config)
   {
     IniAccess iniAccess = IniAccess(config_->mainIniPath);
     obc_ = new OBC();
   
     string clock_sensor_ini_path = iniAccess.ReadString("COMPONENTS_FILE", "clock_sensor_file");
     clock_sensor_ = new ClockSensor(InitClockSensor(config_->simTime, clock_sensor_ini_path));
   }
   ```

6. Copy `ClockSensor.ini` into `S2E_USER/data/ini/components` from `Tutorial/SampleCodes/ClockSensor`

7. Edit `User_SimBase.ini` to add following line at the bottom of the file

   ```c++
   clock_sensor_file = ../../data/ini/components/ClockSensor.ini
   ```

8. Compile `S2E_USER` and execute it

9. Check the log file 

10. Edit the `ClockSensor.ini` and rerun the `S2E_USER` to confirm the initialize file can affect to the result

