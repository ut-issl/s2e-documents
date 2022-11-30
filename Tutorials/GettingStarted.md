# Getting Started

## 1.  Overview

- This tutorial explains how to use the S2E simulator without any source code modification.   
- Users can start this tutorial just after users clone the [s2e-core](https://github.com/ut-issl/s2e-core) repository. 
- The supported version of this document
  - Please confirm that the version of the documents and s2e-core is compatible.
  
## 2. Clone, Build, and Execute 

1. Clone [s2e-core](https://github.com/ut-issl/s2e-core).
2. Read `README.md` to check the overview of S2E.
3. Build and execute the `s2e-core` by referring following documents depends on your development environment.
   - [How to compile with Visual Studio](../General/HowToCompileWithVisualStudio.md)
   - [How to compile with Ubuntu](../General/HowToCompileWithUbuntuInDocker.md)


## 3. Check log output 

1. Check `./data/SampleSat/logs` to find CSV log output file  
   - The file name includes executed time as `YYMMDD_HHMMSS_default.csv`  
2. Open the CSV log file
3. You can see the simulation output
4. The meaning of each value is described in the first row
   - A general rule of the header descriptions  
     - `t` = true value
     - `b` = body frame
     - `i` = inertial frame
     - `c` = component frame
5. You can write a graph from the CSV file as you need.
   - You can find plot examples written in Python in the `scripts/Plot` directory.
   - Please see [How to Visualize Simulation Results](../General/HowToVisualizeSimulationResults.md) for mroe detailes.
   
## 4. Edit Simulation Conditions

1. Move to `./data/SampleSat/ini`  directory  
2. You can find the several **initialize** files (ini files). In these initialize files, simulation conditions are defined, and you can change the conditions without rebuild of S2E by editing the initialize files.
3. Open `SampleSimBase.ini`, which is the base file of the initialize files.
   - In this base file, other initialize files are defined.
   - You can see simulation conditions as time definitions, randomize seed definitions, etc. 
4. Open `SampleSat.ini`, which is the file to set the spacecraft parameters.
4. Edit the value of angular momentum `Omega_b(0-2)` in the `[Attitude]` section as you want.
5. Rerun the `s2e-core` **without a rebuild**
6. Check the new log file in `./data/SampleSat/logs` to confirm the initial angular velocity is changed as you want.
7. Of course, you can change other values similarly.

## 5. Edit Simulation Conditions: Disturbances

1. Move to `./data/SampleSat/ini`  directory again  
2. Open `SampleDisturbance.ini`, which defines conditions to calculate orbital disturbance torques and forces
   - Currently, S2E supports the following disturbances:
     - Gravity Gradient torque
     - Magnetic Disturbance torque
     - Air drag torque and force
     - Solar radiation pressure torque and force
     - Geo Potential acceleration
     - Third body gravity acceleration
3. You can select `ENABLE` or `DISABLE` of calculation and log output for each disturbance
4. Edit all `calculation` parameters of each disturbance as `calculation = DISABLE`
5. Rerun the `s2e-core` **without a rebuild**
6. Check the new log file in `./data/SampleSat/logs` to confirm the spacecraft is not affected by any disturbance torque and the angular velocity and quaternion are not changed.
7. Edit  `calculation` of MAG_DISTURBANCE as `calculation = ENABLE`
8. Rerun the S2E_CORE **without a rebuild**
9. Edit the value `rmm_const_b(0-2)` of MAG_DISTURBANCE as you want (e.g., 0.1)
10. Rerun the S2E_CORE **without a rebuild**
11. Compare the value of `mag_dist_torque_b(X),(Y),(Z)` in the latest log file and previous log file to confirm the magnetic disturbance acting on the spacecraft is changed.
12. Of course, you can change other values similarly.
    - Detail description of initializing values are written in `Specifications`.


## 6. Edit Simulation Conditions: Orbit

1. Move to `./data/SampleSat/ini`  directory  
1. Open `SampleSat.ini` and see the `[Orbit]` section, which defines conditions to calculate orbit motion
   - Currently, S2E supports several types of orbit propagation. Please see [Orbit](./Specifications/Dynamics/Spec_Orbit.md) specification documents for more details.
1. The default setting is as follows:
   - `propagate_mode = SGP4`: SGP4 Propagator is selected
   - TLE: ISS orbit
1. To get a long-term orbit simulation data, edit the following simulation time settings in `SampleSimBase.ini`
   - `EndTimeSec = 6000`
   - `LogOutPutIntervalSec = 10` (to decrease the output file size)
1. To visualize the orbit result, execute the `plot_satellite_orbit_on_miller.py` and `plot_orbit_eci.py`. You can see the plots as follows.  
   ![](./figs/GettingStarted_PlotIssOrbitInMiller.JPG)
   ![](./figs/GettingStarted_PlotIssOrbit3d.JPG)

1. Change TLE as you want
   - Example: PRISM (Hitomi)
     ```
     tle1=1 33493U 09002B   22331.71920614  .00003745  00000-0  29350-3 0  9995
     tle2=2 33493  98.2516 327.9413 0016885   9.3461 350.8072 15.01563916753462
     ```
1. Rerun the `s2e-core` **without a rebuild**
1. Check the new log file in `./data/SampleSat/logs` to confirm the spacecraft position in ECI frame `sat_position_i` and spacecraft position in ECEF frame `lat, lon, alt` are changed.
1. To visualize the orbit result, execute the `plot_satellite_orbit_on_miller.py` and `plot_orbit_eci.py`. You can see the different plots as follows.  
  ![](./figs/GettingStarted_PlotPrismOrbitInMiller.JPG)
  ![](./figs/GettingStarted_PlotPrismOrbit3d.JPG)

## 7. Edit Simulation Conditions: Environment

1. Move to `./data/SampleSat/ini`  directory  
2. Open `SampleLocalEnvironment.ini`, which defines conditions to calculate the environment around the spacecraft
   - Currently, S2E supports the following environment models:
     - Celestial information: CSPICE
     - Geomagnetic field model: IGRF with random variation
     - Solar power model: Considering solar distance and eclipse
     - Air density: NRLMSISE-00 model with random variation
3. Edit values of `mag_rwdev, mag_rwlimit, mag_wnvar` 
4. Rerun the `s2e-core` **without a rebuild**
5. Check the new log file in `./data/SampleSat/logs` to confirm the magnetic field at the spacecraft position in ECI frame `mag_i`, the magnetic field in body frame `mag_b`, and magnetic disturbance torque in body frame `mag_dist_torque_b` are changed.
