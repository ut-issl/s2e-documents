# SRP Environment

## 1.  Overview

1. Functions

   - SRP Environment calculates solar power flux at the position of the spacecraft including the earth eclipse effect.
   - Solar power flux 

2. Related files

   - SRPEnvironment.cpp, .h
     - `SRPEnvironment` class is defined 
   - Environment.cpp, .h
     - `SRPEnvironment` class is used here as a member variable of `Envir` class
   - Init_Environment.cpp
     - Instance of `Envir` class is made by using the initialize file for environment setting

3. How to use

   - `UpdateAllStates` function calculates solar power flux and updates eclipse flag.
   - Users can get calculated values by using following functions
     - `CalcTruePressure` : Return solar pressure (N/m2) with eclipse effect for SRP disturbance calculation.
     - `CalcPowerDensity`: Return solar power density (W/m2) with eclipse effect for EPS calculation.
     - `GetPressure`: Return solar pressure (N/m2) without eclipse effect.
     - `GetEclipsed`: Return eclipse flag (Boolean)

   

## 2. Explanation of Algorithm

  Write important algorithm for the class, the library, or the each function. Please use equations, figures, reference papers for easy understanding.

1. Pressure calculation in `UpdateAllStates` function

   1. overview

      - Solar radiation pressure at the position of the spacecraft is calculated by using the inverse square law

   2. inputs and outputs

      - Constants
        - Solar constant: $`P_{\odot} = 1366`$ W/m2
        - Speed of light: $`c = 299792458`$ m/s
        - Astronomical Unit: $`AU = 149597870700`$ m
      - Input variables
        -  The sun position in the body-fixed frame of the spacecraft: $`\bm{r}_{\odot-sc}`$ m
           -  Unbold $`r_{\odot-sc}`$ is the norm of $`\bm{r}_{\odot-sc}`$
      - Output
     - Solar radiation pressure: $`P_{sc}`$ N/m2

3. algorithm
   
      ```math
      P_{sc}=\frac{P_{sun}}{c}\left(\frac{AU}{r_{\odot-sc}}\right)^{2}
      ```
      
   4. note
   
      - It is known that the solar constant value varies between 1365 and 1367 W/m2, but it is handled as a constant value in S2E. 
   
3. Eclipse detection in `UpdateAllStates` function

   1. overview
   2. inputs and outputs
      - Constants
        - Radius of the earth: $`r_{\oplus}=6378137`$ m
        - Radius of the sun: $`r_{\odot}=6.96\times10^{8}`$ m
      - Input variables
        - The sun position in the body-fixed frame of the spacecraft: $`\bm{r}_{\odot-sc}`$ m
          
        - The earth position in the body-fixed frame of the spacecraft: $`\bm{r}_{\oplus-sc}`$ m

      - Output
        
        - Eclipse flag: $`eclipse`$
   3. algorithm

   ```math
   A_{\odot} = \sin^{-1}\left(\frac{r_{\odot}}{r_{\odot-sc}}\right)\\
   A_{\oplus} = \sin^{-1}\left(\frac{r_{\oplus}}{r_{\oplus-sc}}\right)\\
   \delta = \cos^{-1}\left(\frac{r_{\odot-sc}}{r_{\oplus-sc}}\cdot \bm{r}_{\oplus-sc}\cdot(\bm{r}_{\odot-sc}-\bm{r}_{\oplus-sc})\right)\\
   eclipse =\left\{
   \begin{matrix}
   1 & ((A_{\oplus}>A_{\odot}) and ((A_{\oplus}-A_{\odot}-\delta)>0))\\
   0 & (otherwise)
   \end{matrix}
   \right.
   ```

   4. note
      - Currently, the penumbra effect is ignored.


## 3. Results of verifications

1. Verification of pressure calculation in `UpdateAllStates` function
   1. overview
      
      - The pressure calculation above is verified.
      
   2. conditions for the verification
      - A test code written in the `SRPEnvironment.cpp` is used.
      - The sun position and the earth position are fixed, and the spacecraft position varies as following values
        - Sun-spacecraft distance: 149604270700m - 153797870700m
        - Earth-spacecraft distance: 6400000m - 4200000000m

   3. results

      - The pressure calculation is verified.

      <img src="./figs/Result_SRP_calculation.jpg" alt="SummaryCalculationTime" style="zoom: 50%;" />

2. Verification of eclipse calculation in `UpdateAllStates` function

   1. overview

      - The eclipse calculation above is verified.

   2. conditions for the verification

      - A test code written in the `SRPEnvironment.cpp` is used.
      - The sun position and the spacecraft position are fixed, and the earth is rotated around the spacecraft.
        - Sun-spacecraft distance: 153797870700m
        - Earth-spacecraft distance: 6400000

   3. results

      - The eclipse calculation is verified.

      <img src="./figs/Result_eclipse_calculation.jpg" alt="SummaryCalculationTime" style="zoom: 50%;" />

## 4. References

1. 