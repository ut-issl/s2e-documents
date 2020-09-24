# Getting Started with VS in Windows PC

## 1.  Overview

- This tutorial explains how to use the S2E simulator without any source code modification.   
- You can start this tutorial just after you clone the [S2E_CORE_OSS](https://gitlab.com/ut_issl/s2e/s2e_core_oss) repository 
- Supported version of this document
  - S2E_CORE_OSS:c4c7cf6567c077f0918f07a9a82c2d7e4531ceb7

## 2. Environment
- This tutorial supports an execution environment with Visual Studio 2017 or 2019 on a Windows PC.  
- However, the basic feature of S2E is executable for other environments with a small modification of the sequence. 
- For example, you can find a document like [How to compile with Ubuntu](../General/HowToCompileWithUbuntuInDocker.md) in the General directory.
- For these environments, I hope someone will write a new *Getting Started tutorial*.  

## 3. Clone & Compile
1. Clone  [S2E_CORE_OSS](https://gitlab.com/ut_issl/s2e/s2e_core_oss)   
2. Read `README.md` to check the overview of S2E  
3. Execute `./script/VisualStudio/dowload_cspice_VS32bit.bat` to set up CSPICE library  
  - **Note:** The script is not completely automatic. Users need to input several simple words.  
  - If you don't use Windows and Visual Studio 2017 or 2019, or the script doesn't work well in your environment, please see  [How to download CSPICE Library](./General/HowToDwnloadCSPCElibrary.md)  
4. Execute `./script/Common/download_nrlmsise00_src_and_table.sh` to download the atmosphere model table.
4. Execute `./script/VisualStudio/make_nrlmsise00_VS32bit.bat` to generate library files for the atmosphere model.
4. Compile and execute the S2E_CORE by referring [How to compile with Visual Studio](./General/HowToCompileWithVisualStudio.md)  

## 4. Check log output

1.  Check `./data/SampleSat/logs` to find CSV log output file  
   - The fine name includes executed time as `YYMMDD_HHMMSS_default.csv`  
2. Open the CSV log file  
3. You can see the simulation output  
4. The meaning of each value is described in the first row  
   - A general rule of the header descriptions  
     - `t` = true value   
     - `b` = body frame  
     - `i` = inertial frame  
     - `c` = component frame  
5. You can write a graph from the CSV file  
   
## 5. Edit Simulation Conditions

1.  Move to `./data/SampleSat/ini`  directory  
2.  You can find several **initialize** files. In these initialize files, simulation conditions are defined, and you can change the conditions without rebuild of S2E by editing the initialize files.
3.  Open `SampleSimBase.ini`, which is the base file of the initialize files.
    - In this base file, other initialize files are defined.
    - You can see simulation conditions as time definitions, randomize seed definitions, etc. 
4.  Open `SampleSat.ini`, which is the file for spacecraft related parameters.
4.  Edit the value of angular momentum `Omega_b(0-2)` in the `[Attitude]` section as you want.
5.  Rerun the S2E_CORE **without a rebuild**
6.  Check the new log file in `./data/SampleSat/logs` to confirm the initial angular velocity is changed as you want.
7.  Of course, you can change other values similarly.

## 6. Edit Simulation Conditions ~Disturbances~

1.  Move to `./data/SampleSat/ini`  directory  
2.  Open `SampleDisturbance.ini` which defines conditions to calculate orbital disturbance torques and forces
    - Currently, S2E supports the following disturbances
      - Gravity Gradient torque
      - Magnetic Disturbance torque
      - Air drag torque and force
      - Solar radiation pressure torque and force
      - Geo Potential acceleration
      - Third body gravity acceleration
3.  You can select `ENABLE` or `DISABLE` of calculation and log output for each disturbance
4.   Edit all `calculation` of each disturbance as `calculation = DISABLE`
5.  Rerun the S2E_CORE **without a rebuild**
6.  Check the new log file in `./data/SampleSat/logs` to confirm the spacecraft is not affected by any disturbance torque, and the angular velocity and quaternion are not changed.
7.  Edit  `calculation` of MAG_DISTURBANCE as `calculation = ENABLE`
8.  Rerun the S2E_CORE **without a rebuild**
9.  Edit the value `rmm_const_b(0-2)` of MAG_DISTURBANCE as you want (e.g., 0.1)
10.  Rerun the S2E_CORE **without a rebuild**
11.  Compare the value of `mag_dist_torque_b(X),(Y),(Z)` in the latest log file and previous log file to confirm the magnetic disturbance acting on the spacecraft is changed.
12.  Of course, you can change other values similarly.
     - Detail description of initializing values are written in `Specifications`

## 7. Edit Simulation Conditions ~Orbit~

1.  Move to `./data/SampleSat/ini`  directory  
2.  Open `SampleSat.ini` and see the `[Orbit]` section, which defines conditions to calculate orbit motion
    - Currently, S2E supports two types of orbit propagation:
      - SGP4 propagation with TLE
      - RK4 propagation with initial position and velocity
3.  The default setting is as follows
    - `propagate_mode = 1`: SGP4 Propagator is selected
    - TLE: ISS orbit
4.  Change TLE as you want
5.  Rerun the S2E_CORE **without a rebuild**
6.  Check the new log file in `./data/SampleSat/logs` to confirm the spacecraft position in ECI frame `sat_position_i` and spacecraft position in ECEF frame `lat,lon, alt ` are changed.

## 8. Edit Simulation Conditions ~Environment~

1.  Move to `./data/SampleSat/ini`  directory  
2.  Open `SampleLocalEnvironment.ini` which defines conditions to calculate the environment around the spacecraft
    - Currently, S2E supports the following environment models
      - Celestial informations: CSPICE
      - Geomagnetic field model: IGRF with random variation
      - Solar power model: Considering solar distance and eclipse
      - Air density: NRLMSISE-00 model with random variation
3.  Edit values of `mag_rwdev, mag_rwlimit, mag_wnvar` 
4.  Rerun the S2E_CORE **without a rebuild**
5.  Check the new log file in `./data/SampleSat/logs` to confirm the magnetic field at the spacecraft position in ECI frame `mag_i`, the magnetic field in body frame `mag_b`, and magnetic disturbance torque in body frame `mag_dist_torque_b` are changed.