# How To Make New Components

## 1.  Overview

- In the [How To Add Components](./Tutorials/HowToAddComponents.md) tutorial, we have added existing components to the simulation scenario.
- This tutorial explains how to make a new component into the S2E_USER directory.
- **Note**: You can move the source files for the new component into the [S2E_CORE_OSS](https://gitlab.com/ut_issl/s2e/s2e_core_oss) repository if the component is useful for all S2E users.
- Supported version of this document
  - S2E_CORE_OSS:c4c7cf6567c077f0918f07a9a82c2d7e4531ceb7
  - Documents_OSS:80af890e5615fbc0f2b49d591118bd46f14a40c8

## 2. Overview of S2E/Components

- Components emulating source codes are stored in the `S2E_CORE_OSS/src/Component` directory. 
- All components need to inherit the base class `ComponentBase` for general functions of components, and most of the components also inherit the base class `ILoggable` for the log output function.
- `ComponentBase` class
  - The base class has an important virtual function `MainRoutine`, and subclasses need to define it in their codes
    - When an instance of the component class is created, the `MainRoutine` function is registered in `TickToComponent` and it will be automatically executed in `UserSat` class.
    - The main features such as observation, generate force, noise addition, communication, etc... should be written in this function
  - Power related functions
    - `SetPowerState`, `GetCurrent` are power related functions. If you want to emulate power consumption and switch control, you need to use the functions
- `ILoggable` class
  - This base class has two important virtual functions `GetLogHeader` and `GetLogValue` for CSV log output.
  - These functions are registered into the log output list when the components are added in `UserComponents::CompoLogSetUp` 

## 3. Make a simple clock sensor

- This chapter explains how to make a simple clock sensor, which observes the simulation elapsed time with bias noise.

1. Copy `ClockSensor.cpp` and `ClockSensor.h` to the directory `S2E_USER/src/Components` from `Documents_OSS/Tutorials/SampleCode/ClockSensor`

2. Edit `./S2E_USER/CMakeList.txt` to add target source files for the compiler. Please add the following description in `set(SOURCE_FILES)`

   ```
   src/Components/ClockSensor.cpp
   ```

3. Compile `S2E_USER` and check there is no error.

4. Edit `User_component.h` and `User_component.cpp` as referring [How To Add Components](./Tutorials/HowToAddComponents.md)

   - The constructor of the `ClockSensor` requires arguments as `prescaler`, `clock_gen`, `sim_time`, and `bias_sec`.
   - `prescaler` and `bias_sec` are user setting parameters for the sensor, and you can choose their value.
   - `clock_gen` is an argument for the `ComponentBase` class.
   - `sim_time` is a specific argument for the clock sensor to get time information. `SimTime` class is managed in the `GlobalEnvironment`, and the `GlobalEnvironment` is instantiated in the `SimulationCase` class.
   - To access the `SimTime`, the following edits are required.  
      **Note:** You can find the edited codes in `SampleCodes/ClockSensor/edited codes`
   - `User_Components.h` and `User_Components.cpp`
     - Add the argument `const GlobalEnvironment* glo_env` in the constructor
     ```c++
     UserComponents(const Dynamics* dynamics, const GlobalEnvironment* glo_env, const SimulationConfig* config, ClockGenerator* clock_gen, const int sat_id);
     ```
     - Instantiate the `ClockSensor` in the constructor
     ```c++
     clock_sensor_ = new ClockSensor(10,clock_gen,&glo_env->GetSimTime(),0.001);
     ```
     - Delete the `clock_sensor_` in the destructor
     ```c++
     delete clock_sensor_;
     ```
   - `User_sat.h` and `User_sat.cpp`
     - Add the argument `const GlobalEnvironment* glo_env` in the constructor and `Initialize` function
     ```c++
     UserSat(SimulationConfig* sim_config, const GlobalEnvironment* glo_env, const int sat_id);
     virtual void Initialize(SimulationConfig* sim_config, const GlobalEnvironment* glo_env, const int sat_id);
     ```
     - Insert the argument `glo_env` to the arguments of `Initialize` in the constructor
     ```c++
       Initialize(sim_config, glo_env, sat_id);
     ```
     - Insert the argument `glo_env` to the arguments of `UserComponent` in the `Initialize` function
     ```c++
     void UserSat::Initialize(SimulationConfig* sim_config, const GlobalEnvironment* glo_env, const int sat_id)
     {
       components_ = new UserComponents(dynamics_, glo_env, sim_config, &clock_gen_, sat_id);
     }
     ```
  - The modified codes for this tutorial are stored in the `./Tutorial/SampleCodes/ClockSensor/`
5. Compile `S2E_USER` and execute it

6. Check the log file to confirm the output of the `clock_sensor`
   - The output of the clock sensor has an offset error.

## 4. Make an initialize file for the clock sensor

- Usually, we want to change the parameters of components such as noise properties, mounting coordinates, and so on. So next step, how to make an initialize file for the `ClockSensor` is explained.

1. Copy `Init_ClockSensor.cpp` and `Initialize_UserComponent.h` into `S2E_USER/src/Components` from `Tutorial/SampleCodes/ClockSensor`

2. Edit `./S2E_USER/CMakeList.txt` to add target source files for the compiler. Please add the following description in `set(SOURCE_FILES)`

   ```
   src/Components/Init_ClockSensor.cpp
   ```

4. Edit the constructor of the `User_components.cpp` as follows

   ```c++
   UserComponents::UserComponents(const Dynamics *dynamics, const GlobalEnvironment* glo_env, const SimulationConfig *config, ClockGenerator *clock_gen, const int sat_id)
   {
     IniAccess iniAccess = IniAccess(config->sat_file_[0]);
     obc_ = new OBC(clock_gen);
     string clock_sensor_ini_path = iniAccess.ReadString("COMPONENTS_FILE", "clock_sensor_file");
     clock_sensor_ = new ClockSensor(InitClockSensor(clock_gen,&glo_env->GetSimTime(),clock_sensor_ini_path));
     }
   ```

6. Copy `ClockSensor.ini` into `S2E_USER/data/ini/components` from `Tutorial/SampleCodes/ClockSensor`

7. Edit `UserSat.ini` to add the following line at the [COMPONENTS_FILE] section of the file

   ```c++
   clock_sensor_file = ../../data/ini/components/ClockSensor.ini
   ```

8. Compile `S2E_USER` and execute it

9. Check the log file 

10. Edit the `ClockSensor.ini` and rerun the `S2E_USER` to confirm the initialize file can affect to the result

