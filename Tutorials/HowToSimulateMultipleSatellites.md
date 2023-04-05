# How to simulate multiple satellites

## 1.  Overview
- S2E can simulate multiple satellites.
- This document describes how to simulate multiple satellites.
- For the sample codes, please see `./Tutorials/SampleCodes/multiple_satellites`
- The supported version of this document
  - Please confirm that the version of the documents and s2e-core is compatible.
 
 
## 2. How to add a new satellite
1. Edit `ini` files
   1. Add `ini` files for the new satellite.
      - `satellite.ini`, `disturbance.ini`, `local_environment.ini`, `structure.ini` are needed.
   2. Register the ini file for the new satellite in `simulation_base.ini`
      - The arguments of `satellite_file` are used as satellite ID in simulation.
        ```
        [SIMULATION_SETTINGS]
        number_of_simulated_spacecraft = 2
        spacecraft_file(0) = ../../data/initialize_files/user_satellite1.ini
        spacecraft_file(1) = ../../data/initialize_files/user_satellite2.ini
        ```

2. Edit source code
   1. Add new `UserSatellite` instances to `Case` members in `user_case.hpp`.
      ```c++
      UserSatellite* satellite0_;
      UserSatellite* satellite1_;
      ```

    2. Edit `user_case.cpp` to copy the spacecraft related codes as the sample code.

3. Build and execute the `s2e-user`

4. You can see the log `spacecraft_angular_velocity_b_x[rad/s]` twice. The first one is angular velocity of `satellite0_`, and the second one is angular velocity of `satellite1_` in the log file.


## 3. Advanced usage
- In the sample, the `satellite0_` and the `satellite1_` are completely same, but users can change the setting of these satellites with editing the `ini` files.
  - Users can change the orbit, initial attitude, satellite structure and so on.
- Users also can set the different component for the `satellite` 0 and 1, when users define different `UserSatellite` and `UserComponents` class.
- The document to use `relative information` will be written.
- Users can also refer the [S2E-FF](https://github.com/ut-issl/s2e-ff) repository.
