# How To Make New Components

## 1.  Overview

- In the [How To Add Components](./HowToAddComponents.md) tutorial, we have added existing components to the simulation scenario.
- This tutorial explains how to make a new component into the s2e-user directory.
  - **Note**: You can move the source files for the new component into the [s2e-core](https://github.com/ut-issl/s2e-core) repository if the component is useful for all S2E users.
- The supported version of this document
  - Please confirm that the version of the documents and s2e-core is compatible.


## 2. Overview of component expression in S2E

- Source codes emulating components are stored in the `s2e-core/src/components` directory.
- All components need to inherit the base class `Component` for general functions of components, and most of the components also inherit the base class `ILoggable` for the log output function.
- `Component` class
  - The base class has an important virtual function `MainRoutine`, and subclasses need to define it in their codes.
    - When an instance of the component class is created, the `MainRoutine` function is registered in the `TickToComponent`, and it will be automatically executed in the `Spacecraft` class.
    - The main features of the components such as observation, generate force, noise addition, communication, etc... should be written in this function.
  - `PowerOffRoutine` is also important especially for actuators. This function is called when the component power line is turned off. Users can stop force and torque generation and initialize the component states.
- Power related functions
  - `SetPowerState` and `GetCurrent` are power related functions. If you want to emulate power consumption and switch control, you need to use the functions.
- `ILoggable` class
  - This base class has two important virtual functions `GetLogHeader` and `GetLogValue`, for CSV log output.
  - These functions are registered into the log output list when the components are added in `UserComponents::LogSetUp` 
- Communication with OBC
  - If users want to emulate the communication(telemetry and command) between the components and the OBC, they can use the base class `UartCommunicationWithObc` or `I2cTargetCommunicationWithObc`.
  - These base classes also support a feature to execute HILS function.


## 3. Make a simple clock sensor without initialize file

- This chapter explains how to make a simple clock sensor, which observes the simulation elapsed time with a bias noise.
- Users can find the sample codes in [s2e-user-example/sample/how-to-make-new-components](https://github.com/ut-issl/s2e-user-example/tree/sample/how-to-make-new-components).
  - The sample codes already including the initialize file for the `ClockSensor`. Please edit the code a bit to learn the procedure step by step.

1. The `clock_sensor.cpp, .hpp` are created in the `components` directory. 
   - The `ClockSensor` class counts clock with a constant bias noise.
   - The class inherits the `Component` and the `ILoggable` base classes as explained above.

1. The `user_components.hpp` and `user_components.cpp` are edit similar procedure with the [How To Add Components](./HowToAddComponents.md)

   - The constructor of the `ClockSensor` requires arguments as `prescaler`, `clock_generator`, `simulation_time`, and `bias_s`.
   - `prescaler` and `bias_s` are user setting parameters for the sensor, and you can freely set these values.
   - `clock_generator` is an argument for the `Component` base class.
   - `simulation_time` is a specific argument for the `ClockSensor` to get true time information. The `SimulationTime` class is managed in the `GlobalEnvironment`, and the `GlobalEnvironment` is instantiated in the `SimulationCase` class.
   - We need to add the following codes to `user_components.cpp`.
     - Instantiate the `ClockSensor` in the constructor.
     ```c++
     clock_sensor_ = new ClockSensor(10, clock_generator, global_environment->GetSimulationTime(), 0.001);
     ```
     - Delete the `clock_sensor_` in the destructor.
     ```c++
     delete clock_sensor_;
     ```
     - Add log set up into the `LogSetUp` function.
     ```c++
     logger.AddLogList(clock_sensor_);
     ```

1. Build `s2e-user` and execute it

1. Check the log file to confirm the output of the `clock_sensor_observed_time[sec]`
   - The output of the clock sensor has an offset error defined by the `bias_s` value, and the update frequency is decided by the `prescaler` and the `component_update_period_s` in the base ini file.

## 4. Make an initialize file for the clock sensor

- Usually, we want to change the parameters of components such as noise properties, mounting coordinates, and others without rebuilding. So this section explains how to make an initialize file for the `ClockSensor`.

1. The initialize function `InitClockSensor` is defined in the `clock_sensor.hpp`.
   - The initialize function requires arguments as `clock_generator`, `simulation_time`, and `file_name`.
   - `clock_generator` and `simulation_time` are same argument with the constructor of the `ClockGenerator`.
   - `file_name` is the file path to the initialize file for the `ClockSensor`. 
   
1. Edit the `user_components.hpp` and `user_components.cpp` as follows
   - `user_components.cpp`
     - Edit making instance of the `clock_sensor` at the constructor
       ```c++
       // Clock Sensor
       std::string file_name = iniAccess.ReadString("COMPONENT_FILES", "clock_sensor_file");
       configuration_->main_logger_->CopyFileToLogDirectory(file_name);
       clock_sensor_ = new ClockSensor(InitClockSensor(clock_generator, global_environment->GetSimulationTime(), file_name));
       ```
       - The first line get the file path of the initialize file of the clock sensor.
       - The second line copy the initialize file to the log output directory to save the simulation setting.
       - The third line make the instance of the `ClockSensor`.

1. Make `clock_sensor.ini` into `s2e-user/data/initialize_files/components` from `./Tutorial/SampleCodes/clock_sensor`

1. Edit `user_satellite.ini` to add the following line at the [COMPONENT_FILES] section of the file

   ```c++
   clock_sensor_file = INI_FILE_DIR_FROM_EXE/components/clock_sensor.ini
   ```
   - The keyword `INI_FILE_DIR_FROM_EXE` is defined in the `CMakeList.txt` to handle the relative path to the initialize files.

1. Build `s2e-user` and execute it

1. Check the log file 

1. Edit the `clock_sensor.ini` and rerun the `s2e-user` to confirm the initialize file can affect the result.
