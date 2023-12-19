# How to simulate multiple satellites

## 1.  Overview
- S2E can simulate multiple satellites.
- This document describes how to simulate multiple satellites.
- For the sample codes, please see [s2e-user-example/sample/how-to-simulate-multiple-satellites](https://github.com/ut-issl/s2e-user-example/tree/sample/how-to-simulate-multiple-satellites).
- The supported version of this document
  - Please confirm that the version of the documents and s2e-core are compatible.
 
 
## 2. How to add a new satellite
1. Edit `ini` files
   1. Add `ini` files for the new satellite.
      - `satellite.ini`, `disturbance.ini`, `local_environment.ini`, `structure.ini` are needed.
   2. Register the `ini` file for the new satellite in `simulation_base.ini`
      - The arguments of `satellite_file` are used as satellite ID in simulation.
        ```
        [SIMULATION_SETTINGS]
        number_of_simulated_spacecraft = 2
        spacecraft_file(0) = INI_FILE_DIR_FROM_EXE/user_satellite.ini
        spacecraft_file(1) = INI_FILE_DIR_FROM_EXE/user_satellite2.ini
        ```

2. Edit source code
   1. Add new `UserSatellite` instances to `Case` members in `user_case.hpp`.
      ```c++
      UserSatellite *spacecraft0_;  //!< Instance of spacecraft
      UserSatellite *spacecraft1_;  //!< Instance of spacecraft
      ```

    2. Edit `user_case.cpp` to copy the spacecraft related codes as the sample code.
       - Please see the sample code for more details.

3. Build and execute the `s2e-user`

4. You can see the log `spacecraft_angular_velocity_b_x[rad/s]` twice. The first one is the angular velocity of `satellite 0`, and the second one is the angular velocity of `satellite 1` in the log file.


## 3. Advanced usage
- In the sample, the `satellite0_` and the `satellite1_` are completely the same, but users can change the settings of these satellites with editing the `ini` files.
  - Users can change the orbit, initial attitude, satellite structure and so on.
- Users also can set the different components for the `satellite` 0 and 1, when users define different `UserSatellite` and `UserComponents` classes.
- The document to use `relative information` will be written.
- Users can also refer the [S2E-FF](https://github.com/ut-issl/s2e-ff) repository.
