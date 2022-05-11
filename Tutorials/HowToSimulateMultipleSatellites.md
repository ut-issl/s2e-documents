# How to simulate multiple satellites

## 1.  Overview
- S2E can simulate multiple satellites.
- This document describes how to simulate multiple satellites.
- For the sample codes, please see `./Tutorials/SampleCodes/MultipleSatellites`
- The supported version of this document
  - Please confirm that the version of the documents and s2e-core is compatible.
 
 
## 2. How to add a new satellite
1. Edit `ini` files
   1. Add `ini` files for the new satellite.
      - `Sat.ini`, `Disturbance.ini`, `LocalEnvironment.ini`, `Structure.ini` are needed.
   2. Register the ini file for the new satellite in `Simbase.ini`
      - The arguments of `sat_file` are used as satellite ID in simulation.
        ```
        [SIM_SETTING]
        num_of_simulated_spacecraft = 2
        sat_file(0)   = ../../data/ini/UserSat1.ini
        sat_file(1)   = ../../data/ini/UserSat2.ini
        ```

2. Edit source code
   1. Add new `Satellite` instances to `Case` members in `UserCase.hpp`.
      ```c++
      UserSat* spacecraft0_;
      UserSat* spacecraft1_;
      ```

    2. Edit `UserCase.cpp` to copy the spacecraft related codes as the sample code.

3. Build and execute the `s2e-user`

4. You can see the log `omega_true_b(X)[rad/s]` twice. The first one is angular velocity of `spacecraft0_`, and the socond one is angular velocity of `spacecraft1_` in the log file.


## 3. Advanced usage
- In the sample, the `spacecraft0_` and the `spacecraft1_` are completely same, but users can change the setting of these satellites with editing the `ini` files.
  - Users can change the orbit, initial attitude, and so on.
- Users also can set the different component for the spacecraft-0 and -1, when users define different `UserSat` and `UserComponents` class.
- The document to use `relative information` will be written.
