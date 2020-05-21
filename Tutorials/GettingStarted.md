# Getting Started with VS in Windows PC

## 1.  Overview

- This tutorial explains how to use the S2E simulator without any source code modification.   
- You can start this tutorial just after you clone the [S2E_CORE_OSS](https://gitlab.com/ut_issl/s2e/s2e_core_oss) repository 

## 2. Environment
- This tutorial supports an execution environment with Visual Studio 2017 or 2019 on a Windows PC.  
- However, basic features of S2E is executable for other environment with a small modification of the sequence. 
- For these environments, I hope someone will write a new *Getting Started tutorial*.  

## 3. Clone & Compile
1. Clone  [S2E_CORE_OSS](https://gitlab.com/ut_issl/s2e/s2e_core_oss)   
2. Read `README.md` to check overview of S2E  
3. Execute `./script/dowload_cspice_VS32bit.bat` to set up CSPICE library  
  - **Note:** The script is not completely automatic. Users need to input several simple words.  
  - If you don't use Windows and Visual Studio 2017 or 2019, or the script doesn't work well in your environment, please see  [How to download CSPICE Library](./General/HowToDwnloadCSPCElibrary.md)  
4. Compile and execute the S2E_CORE by referring [How to compile with Visual Studio](./General/HowToCompileWithVisualStudio.md)  

## 4. Check log output

1.  Check `./data/SampleSat/logs` to find CSV log output file  
   - The fine name includes executed time as `YYMMDD_HHMMSS_default.csv`  
2. Open the CSV log file  
3. You can see the simulation output  
4. The meaning of each value is described in first row  
   - General rule of the header descriptions  
     - `t` = true value   
     - `b` = body frame  
     - `i` = inertial frame  
     - `c` = component frame  
5. You can write graph from the CSV file  
   
## 5. Edit Simulation Conditions

1.  Move to `./data/SampleSat/ini`  directory  
2.  You can find several **initialize** files. In these initialize files, simulation conditions are defined, and you can change the conditions without rebuild of S2E by editing the initialize files.
3.  Open `SampleSimBase.ini`, which is the base file of the initialize files.
    - In this base file, other initialize files are defined.
    - You can see simulation conditions as time definitions, randomize seed definitions, initial quaternions, angular velocities, and torques, inertia tensor, and mass of the spacecraft. 
4.  Edit the value of angular momentum `Omega_b(0-2)` as you want.
5.  Rerun the S2E_CORE **without rebuild**
6.  Check new log file in `./data/SampleSat/logs` to confirm the initial angular velocity is changed as you want.
7.  Of course, you can change other values similarly.

## 6. Edit Simulation Conditions ~Disturbances~

1.  Move to `./data/SampleSat/ini`  directory  
2.  Open `SampleDisturbance.ini` which defines conditions to calculate orbital disturbance torques and forces
    - Currently, S2E supports Gravity Gradient torque, Magnetic Disturbance torque, air drag torque and force, and solar radiation pressure torque and force.
3.  You can select `ENABLE` or `DISABLE` of calculation and log output for each disturbance
4.   Edit all `calculation` of each disturbance as `calculation = DISABLE`
5.  Rerun the S2E_CORE **without rebuild**
6.  Check new log file in `./data/SampleSat/logs` to confirm the spacecraft is not affected by any disturbance torque, and the angular velocity and quaternion is not changed.
7.  Edit  `calculation` of MAG_DISTURBANCE as `calculation = ENABLE`
8.  Rerun the S2E_CORE **without rebuild**
9.  Edit the value `rmm_const_b(0-2)` of MAG_DISTURBANCE as you want (e.g., 0.1)
10.  Rerun the S2E_CORE **without rebuild**
11.  Compare the value of `mag_dist_torque_b(X),(Y),(Z)` in latest log file and previous log file to confirm the magnetic disturbance acting on the spacecraft is changed.
12.  Of course, you can change other values similarly.
     - Detail description of initialize values are written in `Specifications`

## 7. Edit Simulation Conditions ~Orbit~

1.  Move to `./data/SampleSat/ini`  directory  
2.  Open `SampleOrbit.ini` which defines conditions to calculate orbit motion
    - Currently, S2E supports two types of orbit propagation: SGP4 propagation with TLE and RK4 propagation with initial position and velocity
    - **Note**: RK4 propagation for earth rotating orbit has a bug. It will be fixed soon
3.  The default setting is as follows
    - `propagate_mode = 1`: SGP4 Propagator is selected
    - TLE: NJ orbit (*a*=883km, *i* =98.6deg, &Omega; = 315.41deg, &omega; =300 deg)
4.  Switch TLE from NJ orbit to ISS orbit by editing the comment out `//`
    - You can choose other TLEs as you want
5.  Rerun the S2E_CORE **without rebuild**
6.  Check new log file in `./data/SampleSat/logs` to confirm the spacecraft position in ECI frame `sat_position_i` and spacecraft position in ECEF frame `lat,lon, alt ` are changed.

## 8. Edit Simulation Conditions ~Environment~

1.  Move to `./data/SampleSat/ini`  directory  
2.  Open `SampleEnvironment.ini` which defines conditions to calculate environment around the spacecraft
    - Currently, S2E supports geomagnetic field, solar power, and air density calculation
      - Geomagnetic field model: IGRF with random variation
      - Solar power model: Considering solar distance and eclipse
      - Air density: Simple altitude depending model with random variation
3.  Edit values of `mag_rwdev, mag_rwlimit, mag_wnvar` 
4.  Rerun the S2E_CORE **without rebuild**
5.  Check new log file in `./data/SampleSat/logs` to confirm the magnetic field at the spacecraft position in ECI frame `mag_i`, the magnetic field in body frame `mag_b`, and magnetic disturbance torque in body frame `mag_dist_torque_b` are changed.