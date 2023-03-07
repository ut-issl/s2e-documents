# Specification for Geomagnetic field model

## 1.  Overview
1. Functions 
   + `GeomagneticField` class calculates the geomagnetic field at the spacecraft's position from the IGRF model and adds noise to emulate the difference between the IGRF model and the real world.

2. Related files
   + `src/environment/local/geomagnetic_field.cpp, .hpp`
     + `GeomagneticField` class is defined.
  + `src/environment/local/local_environment.cpp, .hpp`
     + `GeomagneticField` class is used here as a member variable of `LocalEnvironment` class.
  + `src/environment/local/initialize_local_environment.cpp, .hpp`
     + `GeomagneticField` class is instanced here based on the `.ini` file for environment.
   + `src/library/external/igrf/igrf.cpp, h`
     + A magnetic field in the ECI frame is calculated by the IGRF model.

3. How to use
   + Set a coefficient file path for the IGRF and random walk / white noise in .ini file
     - coefficient_file: File path to the IGRF coefficients table.
     - magnetic_field_random_walk_standard_deviation_nT: Standard deviation of the random walk noise
     - magnetic_field_random_walk_limit_nT: Limit of the random walk noise
     - magnetic_field_white_noise_standard_deviation_nT: Standard deviation of the normal random noise
   + Public functions
     + `CalcMagneticField`  : Update the magnetic field
     + `GetGeomagneticField_i_nT` : Return the magnetic field (nT) in the ECI 
     + `GetGeomagneticField_b_nT` : Return the magnetic field (nT) in the body-fixed coordinate


## 2. Explanation of Algorithm
+ IGRF calculates the magnetic field based on a spherical harmonic expansion of magnetic scalar potential $V$.
  + The coefficients of the spherical harmonic expansion of $V$ is updated by [IAGA](https://www.ngdc.noaa.gov/IAGA/vmod/index.html). The latest version is the 13th generation, and S2E uses this version.
+ Please refer [here](https://www.ngdc.noaa.gov/IAGA/vmod/igrf.html#:~:text=The%20International%20Association%20of%20Geomagnetism,interior%2C%20its%20crust%20and%20its) for the details of IGRF.

## 3. Verification
1. Overview
  + The  calculated magnetic field is compared with [Matlab's IGRF function](https://jp.mathworks.com/help/aerotbx/ug/igrfmagm.html) calculation in the ECI frame.

2. Conditions for the verification
   1. input files
      - Default initialize files

   2. initial values
      - To check the result in an example orbit, the EndTime was changed to 9000 s.
        ```
        StartYMDHMS=2020/01/01 11:00:00.0
        EndTimeSec=9000
        StepTimeSec=5
        OrbitPropagateStepTimeSec=0.1
        LogPeriod = 5
        SimulationSpeed = 0
        ```
      - Especially, we chose the following TLE for orbit calculation (ISS orbit).
        ```
        tle1=1 25544U 98067A   20076.51604214  .00016717  00000-0  10270-3 0  9005
        tle2=2 25544  51.6412  86.9962 0006063  30.9353 329.2153 15.49228202 17647
        ```

3. Results
   + Results of S2E
     <img src="./figs/Result_IGRF_S2E.png"  width="360" />

   + Error between S2E and MATLAB
     + The error is approximately 200―500 nT. This may be because the coefficients of S2E are 13th, but on the other hand, those of MATLAB are 12th. 
        <img src="./figs/Error_IGRF_S2E_MATLAB.png"  width="360" />

## 4. References
1. International Geomagnetic Reference Field, https://www.ngdc.noaa.gov/IAGA/vmod/igrf.html#:~:text=The%20International%20Association%20of%20Geomagnetism,interior%2C%20its%20crust%20and%20its
2. IAGA web page, https://www.ngdc.noaa.gov/IAGA/vmod/index.html
3. MATLAB `igrfmagm`, https://jp.mathworks.com/help/aerotbx/ug/igrfmagm.html
