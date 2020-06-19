# Specification for Orbit

## 1.  Overview

1. functions
   
   - TBW

2. files
   
   - TBW
2. how to use
   
   - TBW
   
     

## 2. Explanation of Algorithm

- TBW
## 3. Results of verifications

1. verification of the error of Fourth Order Runge-Kutta method (RK4)
   1. overview
      
      - Verify the error of the numerical integration using Fourth Order Runge-Kutta method (RK4).
      - The output of the simulation was compared with the analytical solution.
      
   2. conditions for the verification

      - The Verifications were conducted in the case of `StepTimeSec` and `OrbitPropagateStepTimeSec` were 0.1(sec), 1(sec), and 10(sec).
      - The initial values of the propagation are as follows:
        ```
        init_position(0) = 1.5944017672e7
        init_position(1) = 0.0
        init_position(2) = 0.0

        init_velocity(0) = 0.0
        init_velocity(1) = 5000.0
        init_velocity(2) = 0.0
        ```
      - This is an circular orbit, which period is about 20040(sec). The center of the orbit is Earth.
      - As a reference, the analytical solution was used. The solution is as follows:
      ```math
      x=R\cos(\omega t),y=R\sin(\omega t)\quad when~R=1.5944017672\times10^7, \omega=0.000313597243985794
      ```
      - All of the effects of disturbance and environment were disabled.
      - The simulation time is 60120(sec), which is approximately three-period.
    

   3. results
      <div align="center">
        <figure id="angle_celes1">
        <img src="./figs/orbit_steptimesec_01.jpg" width = 400 alt="orbit_steptimesec_01">
        <img src="./figs/orbit_steptimesec_1.jpg" width = 400 alt="orbit_steptimesec_1">
        <img src="./figs/orbit_steptimesec_10.jpg" width = 400 alt="orbit_steptimesec_10">
        </figure>
      </div>

      - In the cases of `OrbitPropagateStepTimeSec=0.1` and `OrbitPropagateStepTimeSec=1`, the error is kept within $`10^{-6}`$ order. However, once the error grows, it will get bigger and bigger periodically.
      - In the case of `OrbitPropagateStepTimeSec=10`, the error quickly grows up to $`10^{-4}`$ order. 
      


        

## 4. References
