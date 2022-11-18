# Specification for Orbit

## 1.  Overview

1. functions
   - The Rk4OrbitPropagation class calculates the position and velocity of satellites with 4th Order Runge-Kutta method(RK4)

2. files
   - `src/Dynamics/Orbit/Orbit.h`
	   -  Definition of Orbit base class
   - `src/Interface/InitInput/Init_Orbit.cpp`
	   - Make an instance of orbit class.	
   - `src/Dynamics/Orbit/Rk4OrbitPropagation.cpp`
   - `src/Dynamics/Orbit/Rk4OrbitPropagation.h`

3. How to use
   - Select `propagate_mode = RK4` in the spacecraft's ini file.
   - Set the initial position [m] and velocity [m/s] in the inertial frame like the following example
     ```
     init_position(0) = 4.2164140100E+07  // radius of GEO
     init_position(1) = 0
     init_position(2) = 0
     init_velocity(0) = 0
     init_velocity(1) = 3.074661E+03  // Speed of a spacecraft in GEO
     init_velocity(2) = 0
     ```
   
## 2. Explanation of Algorithm

1. `Propagate` function  
   - The position and velocity of the satellite are updated by using RK4. As the input of RK4, the six-state variables are set. These state variables are the three-dimensional position [$x$, $y$ ,$z$] and three-dimensional velocity [$v_x$, $v_y$, $v_z$] at the inertial coordinate. Here, the inertial coordinate is decided by the `PlanetSelect.ini`
   - As the force which works to the satellite motion is the external acceleration [$a_x$,$a_y$,$a_z$] calculated from the disturbance class or thruster class and the gravity force from the center planet, which is defined in `PlanetSelect.ini`. As a summary, the orbit is calculated as the following equation.
   ```math
   \begin{align}
     \dot{x} &= v_x\\
     \dot{y} &= v_y\\
     \dot{z} &= v_z\\
     \dot{v}_x &= a_x-\mu\frac{x}{r^3}\\
     \dot{v}_y &= a_y-\mu\frac{y}{r^3}\\
     \dot{v}_z &= a_z-\mu\frac{z}{r^3}\\
     r &= \sqrt{x^2+y^2+z^2}
   \end{align}
   ```

## 3. Results of verifications

1. Verification of the error of Fourth Order Runge-Kutta method (RK4)
   1. Overview
      - Verify the numerical integration error of the RK4 method.
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
      - This is a circular orbit, which period is about 20040(sec). The center of the orbit is Earth.
      - As a reference, the analytical solution was used. The solution is as follows:
      ```math
      x=R\cos(\omega t),y=R\sin(\omega t)\quad when~R=1.5944017672\times10^7, \omega=0.000313597243985794
      ```
      - All of the effects of disturbance and environment were disabled.
      - The simulation time is 60120(sec), which is approximately three-period. In addition, for a long-term test, the case in which simulation time is 200400(about 10 periods) was tested. The `OrbitPropagateStepTimeSec` of this case is 1(sec).
    
   3. results
      <div align="center">
        <img src="./figs/orbit_steptimesec_01.jpg" width = 400 alt="orbit_steptimesec_01">
        <img src="./figs/orbit_steptimesec_1.jpg" width = 400 alt="orbit_steptimesec_1">
        <img src="./figs/orbit_steptimesec_10.jpg" width = 400 alt="orbit_steptimesec_10">
        </figure>
      </div>

      - In the cases of `OrbitPropagateStepTimeSec=0.1` and `OrbitPropagateStepTimeSec=1`, the error is kept within $10^{-6}$ order. However, once the error grows, it will get bigger and bigger.
      - In the case of `OrbitPropagateStepTimeSec=10`, the error quickly grows up to $10^{-4}$ order. 
      
      <div align="center">
        <img src="./figs/orbit_steptimesec_1_longterm.jpg" width = 400 alt="orbit_steptimesec_1_longterm">
        </figure>
      </div>

      - In the long-term test result, it is clear that the error magnitude grows proportionally to the time.

   4. Others
      - At first, the output of STK would be used for reference. However, it did not work well. Data were input as follows:
      <div align="center">
        <img src="./figs/orbit_STKsettings.JPG" alt="orbit_STKsettings">
        </figure>
      </div>
      
      - However, the result is as follows:
      <div align="center">
        <img src="./figs/orbit_STKresult.JPG" alt="orbit_STKresult">
        </figure>
      </div>

      - As this figure shows, the initial values in the result are slightly different from the input.
         + In the .sa files, the initial values of $x, y, z, v_x, v_y, v_z$ are converted into elements of orbit and stored. The error might occur in the process of this conversion.
        

## 4. References
NA

