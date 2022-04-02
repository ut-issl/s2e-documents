# How To Make New Components

## 1.  Overview

- In the [How To Add Components](./HowToAddComponents.md) tutorial, we have added existing components to the simulation scenario.
- This tutorial explains how to make a new component into the S2E_USER directory.
- **Note**: You can move the source files for the new component into the [s2e-core](https://github.com/ut-issl/s2e-core) repository if the component is useful for all S2E users.
- The Supported version of this document
  - s2e-core: [v4.0](https://github.com/ut-issl/s2e-core/releases/tag/v4.0)

## 2. Overview of S2E/Components

- Source codes emulating components are stored in the `S2E_CORE_OSS/src/Component` directory. 
- All components need to inherit the base class `ComponentBase` for general functions of components, and most of the components also inherit the base class `ILoggable` for the log output function.
- `ComponentBase` class
  - The base class has an important virtual function `MainRoutine`, and subclasses need to define it in their codes.
    - When an instance of the component class is created, the `MainRoutine` function is registered in the `TickToComponent`, and it will be automatically executed in the `UserSat` class.
    - The main features such as observation, generate force, noise addition, communication, etc... should be written in this function.
  - Power related functions
    - `SetPowerState`, `GetCurrent` are power related functions. If you want to emulate power consumption and switch control, you need to use the functions
- `ILoggable` class
  - This base class has two important virtual functions `GetLogHeader` and `GetLogValue`, for CSV log output.
  - These functions are registered into the log output list when the components are added in `UserComponents::CompoLogSetUp` 

## 3. Make a simple clock sensor

- This chapter explains how to make a simple clock sensor, which observes the simulation elapsed time with a bias noise.

1. Copy `ClockSensor.cpp` and `ClockSensor.h` to the directory `S2E_USER/src/Components` from `Documents_OSS/Tutorials/SampleCode/ClockSensor`

2. Edit `./S2E_USER/CMakeList.txt` to add target source files for the compiler. Please add the following description in `set(SOURCE_FILES)`

   ```
   src/Components/ClockSensor.cpp
   ```

3. Build `S2E_USER` and check there is no error.

4. Edit `User_component.h` and `User_component.cpp` as referring [How To Add Components](./HowToAddComponents.md)

   - The constructor of the `ClockSensor` requires arguments as `prescaler`, `clock_gen`, `sim_time`, and `bias_sec`.
   - `prescaler` and `bias_sec` are user setting parameters for the sensor, and you can set these value.
   - `clock_gen` is an argument for the `ComponentBase` class.
   - `sim_time` is a specific argument for the clock sensor to get time information. `SimTime` class is managed in the `GlobalEnvironment`, and the `GlobalEnvironment` is instantiated in the `SimulationCase` class.
   - You need to edit the `User_Components.cpp` as follows.
     - Instantiate the `ClockSensor` in the constructor.
     ```c++
     clock_sensor_ = new ClockSensor(10,clock_gen,&glo_env->GetSimTime(),0.001);
     ```
     - Delete the `clock_sensor_` in the destructor.
     ```c++
     delete clock_sensor_;
     ```
     - Add log set up into the `CompoLogSetUp` function.
     ```c++
     logger.AddLoggable(clock_sensor_);
     ```

5. Build `S2E_USER` and execute it

6. Check the log file to confirm the output of the `clock_sensor`
   - The output of the clock sensor has an offset error, and the update frequency is decided by the `prescaler` and the `CompoUpdateIntervalSec` in the base ini file.

## 4. Make an initialize file for the clock sensor

- Usually, we want to change the parameters of components without rebuild such as noise properties, mounting coordinates, and so on. So in the next step, we explain how to make an initialize file for the `ClockSensor`.

1. Copy `Init_ClockSensor.cpp` and `Initialize_UserComponent.h` into `S2E_USER/src/Components` from `Tutorial/SampleCodes/ClockSensor`

2. Edit `./S2E_USER/CMakeList.txt` to add target source files for the compiler. Please add the following description in `set(SOURCE_FILES)`

   ```
   src/Components/Init_ClockSensor.cpp
   ```

4. Edit the constructor of the `User_components.cpp` as follows

   ```c++
   std::string clock_sensor_ini_path = iniAccess.ReadString("COMPONENTS_FILE", "clock_sensor_file");
   clock_sensor_ = new ClockSensor(InitClockSensor(clock_gen, glo_env->GetSimTime(), clock_sensor_ini_path));
   ```

6. Copy `ClockSensor.ini` into `S2E_USER/data/ini/components` from `Tutorial/SampleCodes/ClockSensor`

7. Edit `UserSat.ini` to add the following line at the [COMPONENTS_FILE] section of the file

   ```c++
   clock_sensor_file = ../../data/ini/components/ClockSensor.ini
   ```

8. Build `S2E_USER` and execute it

9. Check the log file 

10. Edit the `ClockSensor.ini` and rerun the `S2E_USER` to confirm the initialize file can affect the result.
