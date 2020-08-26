# Specification for Magnetic field model

## 1.  Overview
1. Functions 
  + MagEnvironment class calculates geomagnetic filed at the position of the spacecraft.

2. Related files
  + `src/Environment/MagEnvironment.cpp, .h`
    + MagEnvironment class is defined.
  + `src/Environment/Environment.cpp, .h`
    + MagEnvironment class is used here as a member variable of Envir class.
  + `src/Environment/Init_Envinronment.cpp`
    + MagEnvironment class is instanced here based on the .ini file for environment.
  + `src/Library/igrf/igrf.cpp, .h`
    + A magnetic field in ECI and body-fixed coordinate is calculated by IGRF model.

3. How to use
  + Set a coefficient file path for IGRF and random walk / white noise in .ini file
    + Example
      ```
      [MAG_ENVIRONMENT]
      calculation = ENABLE
      logging = ENABLE
      coeff_file = ../../src/Library/igrf/igrf13.coef
      mag_rwdev = 0.0//10.0     //磁気ランダムウォーク速度[nT] Default(10.0)
      mag_rwlimit = 0.0//400.0  //磁気ランダムウォーク最大値[nT] Default(400.0)
      mag_wnvar = 0.0//50.0     //磁気ホワイトノイズ分散[nT] Default(50.0)
      ```
  + `CalcMag` : Update the magnetic field (nT)
  + `Addnoise` : Add noise to the result of `CalcMag`
  + `GetMag_i` : Return the magnetic field (nT) in ECI 
  + `GetMag_b` : Return the magnetic field (nT) in body-fixed coordinate


## 2. Explanation of Algorithm
+ IGRF calculates the magnetic field based on a spherical harmonic expansion of magnetic scalar potential $`V`$.
  + The coefficients of the spherical harmonic expansion of $`V`$ is updated by [IAGA](https://www.ngdc.noaa.gov/IAGA/vmod/index.html). The latest version is 13th generation, and S2E uses this version.
+ Please refer [this link](https://www.ngdc.noaa.gov/IAGA/vmod/igrf.html#:~:text=The%20International%20Association%20of%20Geomagnetism,interior%2C%20its%20crust%20and%20its) for the details of IGRF.

## 3. Verification
1. Overview
  + The  calculated magnetic field is compared with [Matlab's IGRF function](https://jp.mathworks.com/help/aerotbx/ug/igrfmagm.html) calculation in ECI.
2. Conditions for the verification
   1. input files
      - Default initialize files
   2. initial values
      - Default initialize files
   
        ```
        StartYMDHMS=2020/01/01 11:00:00.0
        EndTimeSec=9000
        StepTimeSec=5
        OrbitPropagateStepTimeSec=0.1
        LogPeriod = 5
        SimulationSpeed = 0
        ```
      - Especially, we chose following TLE for orbit calculation (ISS orbit).
   
        ```
        tle1=1 25544U 98067A   20076.51604214  .00016717  00000-0  10270-3 0  9005
        tle2=2 25544  51.6412  86.9962 0006063  30.9353 329.2153 15.49228202 17647
        ```

3. Results
   + Results of S2E
        <img src="./figs/Result_IGRF_S2E.png"  width="360" />

   + Error between S2E and MATLAB
     + The error is approximately 200―500 nT. This may be because the coefficients of S2E are 13th, but on the ohter hand, those of MATLAB are 12th. 
        <img src="./figs/Error_IGRF_S2E_MATLAB.png"  width="360" />

## 4. References
1. International Geomagnetic Reference Field, https://www.ngdc.noaa.gov/IAGA/vmod/igrf.html#:~:text=The%20International%20Association%20of%20Geomagnetism,interior%2C%20its%20crust%20and%20its
2. IAGA web page, https://www.ngdc.noaa.gov/IAGA/vmod/index.html
3. MATLAB igrfmagm, https://jp.mathworks.com/help/aerotbx/ug/igrfmagm.html