# How To Add Components

## 1.  Overview

- In the [How To Make New Simulation Scenario](./HowToMakeNewSimulationScenario.md) tutorial, we have made an `s2e-user` directory for our simulation scenario.
- This tutorial explains how to add components to your scenario.
- A similar procedure is available for other components in the `s2e-core`.
- The Supported version of this document
  - s2e-core: [v5.0.0](https://github.com/ut-issl/s2e-core/releases/tag/v5.0.0)


## 2. Add a Gyro sensor

- This chapter explains how to add a gyro component to your `s2e-user` simulation case.

1. Open & edit `UserComponents.h`
   - Add the following descriptions at the one line below of `#include "OBC.h"`
     ```c++
     #include "InitGyro.hpp"
     ```
   - Add the following descriptions at the one line below of `OBC* obc_;`
     ```c++
     Gyro* gyro_;
     ```

4. Open and edit `UserComponents.cpp`
   - Edit the constructor function as follows to create an instance of the `GYRO` class at the one line below of `obc_ = new OBC(clock_gen);`.
     ``` c++
     // Initialize of GYRO class
     IniAccess iniAccess = IniAccess(config->sat_file_[0]);
     const double compo_step_sec = glo_env_->GetSimTime().GetCompoStepSec();
     std::string gyro_ini_path = iniAccess.ReadString("COMPONENTS_FILE", "gyro_file");
     gyro_ = new Gyro(InitGyro(clock_gen, 1, gyro_ini_path, compo_step_sec, dynamics));
     ```

   - Add the following descriptions at the one line up of `delete obc_;` in the destructor.
     ```c++
     delete gyro_;
     ```

   - Edit the `CompoLogSetUp` function as follows to register log output
     ``` c++
     void UserComponents::LogSetup(Logger & logger)
     {
       logger.AddLoggable(gyro_);
     }
     ```

8. Open `UserSat.ini` and edit `omega_b` to add initial angular velocity.
   - Users can select any value.

9. Add the following descriptions at the bottom line of `[COMPONENTS_FILE]` to set the initialize file for the gyro sensor.

   ```c++
   gyro_file = ../../data/ini/components/GyroXxx.ini
   ```

10. Build the `s2e-user` and execute it

11. Check the log output file to find `gyro_omega1_c`, the gyro sensor's output angular velocity value in the component frame.

    - Since the default initializing file is described as that the sensor has no noise, the value of `gyro_omega1_c` and `omega_t_b` is completely the same.

12. Edit the `data/ini/components/GyroXxx.ini` file to add several noises, and rerun the `s2e-user`

13. Check the log output file to find `gyro_omega1_c`. Now the sensor output has several errors you set in the initialize file like the following figure.

    - We edited the file as `Bias_c(0) = 0.001` and `nr_stddev_c(0) = 0.001` to get the following figure.

    <img src="./figs/AngularVelocityTrueVsGyro.png" alt="AngularVelocityTrueVsGyro" style="zoom: 67%;" />

## 3. Add another Gyro sensor

- You can add multiple components in your `s2e-user` simulation case similar to the above sequence.

1. Open `UserComponents.h`

2. Add the following descriptions at the one line below of `GYRO* gyro_;`

   ```c++
   Gyro* gyro2_;
   ```

3. Open `User_Components.cpp`

4. Edit the constructor function to add the following description to create the second instance of the GYRO class

   ``` c++
   std::string gyro_ini_path_2 = iniAccess.ReadString("COMPONENTS_FILE", "gyro_file_2");
   gyro2_ = new Gyro(InitGyro(clock_gen, 2, gyro_ini_path_2, compo_step_sec, dynamics));
   ```

5. Add the following descriptions at the one line below of `delete gyro_;` in the destructor

   ```c++
   delete gyro2_;
   ```

6. Edit the `CompoLogSetUp` function as follows to register log output

   ``` c++
   void UserComponents::CompoLogSetUp(Logger & logger)
   {
     logger.AddLoggable(gyro_);
     logger.AddLoggable(gyro2_);
   }
   ```

7. Open `UserSat.ini`

8. Add the following descriptions at the bottom line of `[COMPONENTS_FILE]` to set the initialize file for the gyro sensor

   ```c++
   gyro_file_2 = ../../data/ini/components/GyroYyy.ini
   ```

9. Copy the `data/ini/components/GyroXxx.ini` file and rename it as `GyroYyy.ini`

10. Edit `GyroYyy.ini` to custom the noise performance of the second gyro sensor

11. Build the `s2e-user` and execute it

12. Check the log output file to find `gyro_omega2_c`, the second gyro sensor's output angular velocity value in the component frame.
