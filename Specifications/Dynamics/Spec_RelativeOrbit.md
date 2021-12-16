 # Specification for Relative Orbit propagation

## 1. Overview

1. functions

    - The RelativeOrbit class calculates the position of a satellite with respect to a reference satellite. This class calculates the position both in the LVLH frame and inertial frame. Users can choose the update method between:
        + relative dynamics propagation using RK4
        + update using STM(State Transition Matrix)

2. Related files
   
   - `RelativeOrbit.cpp`
   - `RelativeOrbit.h`
        + Definition of the class
   - `RelativeOrbitModels.cpp`
   - `RelativeOrbitModels.h`
        + Library to store equations for various relative dynamics
   - `orbit.h`
        + Definition of the parent class
   - `Init_Orbit.cpp`
        + Initialize function
   - `Sat.ini`
        + Initialization file for `RelativeOrbit`
3. How to use
   
   - Relative orbit propagation is available only when multiple satellites are simulated.
        + The sample case in S2E_CORE_OSS simulates a single satellite. For an example of simulating multiple satellites, please refer to the [tutorial](../../Tutorials/HowToSimulateMultipleSatellites.md). 
   - Confirm the instance of `RelativeInformation` is the member of each satellite.
   - Set up the configuration of the `[ORBIT]` section in the `Sat.ini`.
        + Set `propagate_mode =2` to use relatibe orbit propagation
        + Choose `update_method`.
            * `update_method = 0` means the orbit is updated with the propagation of the relative dynamics equation($`\dot{\bm{x}}=\bm{Ax}+\bm{Bu}`$, i.e., Hill equation).
            * `update_method = 1` means the orbit is updated with the STM($`\bm{x}(t)=\bm{\Phi}(t,t_0)\bm{x}(t_0)`$, i.e., Clohessy-Wiltshire solution).
        + When you choose `update_method = 0`, set `relative_dynamics_model_type`.
        + When you choose `update_method = 1`, set `stm_model_type`.
        + Set the initial relative position of the satellite in the LVLH frame. LVLH frame definition is:
            * $`\bm{x}`$ is a direction vector from the reference satellite ("chief" in the figure) radially outward.
            * The direction of $`\bm{z}`$ corresponds to the angular momentum vector of the reference satellite orbit.
            * The direction of $`\bm{y}`$ is determined by $`\bm{z}\times\bm{x}`$.
        <figure>
        <div align="center">
        <img src="./figs/RelativeOrbit_LVLHdefinition.JPG" width=70% alt="">
        <figcaption>Definition of LVLH frame [1]</figcaption>
        </div>
        </figure>

        + Set the ID and ini file name of the reference satellite.
            * NOTE: Confirm the `propagate_mode` of the reference satellite is not 2. The orbit of the reference satellite must be propagated by the methods other than the relative orbit propagation.

4. How to add a new relative dynamics model

    1. New Relative Dynamics equation

        + Add the name of the dynamics model to the `RelativeDynamicsModel` enum.
        + Add the function to calculate the system matrix like `CalculateHillSystemMatrix`.
        + Edit the `CalculateSystemMatrix` function.

    2. New STM

        + Add the name of the dynamics model to `STMModel` enum.
        + Add the function to calculate the system matrix as `CalculateHCWSTM`.
        + Edit the `CalculateSTM` function.

## 2. Explanation of Algorithm

1. `InitializeState`

   1. overview
        + The `InitializeState` function initializes the orbit of the satellite.

   2. inputs and outputs
        + input
            *  `initial_relative_position_lvlh`, `initial_relative_velocity_lvlh`
                - The initial state of the satellite
            * `reference_sat_initial_orbit`
                - The initial orbit of the reference satellite
                - NOTE: This is used only for the initialization.
            * `current_jd`
                - The initial Julian day
            * `mu`
                - The gravity constant of the reference celestial body $`\mu`$
            * `timestep`
                - RK4 propagation timestep
            * `wgs`
                - Type of the World Geometric System
            * `init_time`
                - Initial simulation time (default value is 0)
        + output
            * none 

   3. algorithm

   4. note

1. `CalculateSystemMatrix`

   1. overview
        + The `CalculateSystemMatrix` function is used only inside the `RelativeOrbit` class. This function calls the system matrix calculation function according to `relative_dynamics_model_type`.

   2. inputs and outputs
        + input
            * `relative_dynamics_model_type`
                - The type of relative dynamics model
            * `reference_sat_orbit`
                - The orbit of the reference satellite
            * `mu` 
                - The gravity constant $`\mu`$
        + output
            * none 

   3. algorithm

   4. note

1. `CalculateSTM`

   1. overview
        + The `CalculateSTM` function is used only inside the `RelativeOrbit` class. This function calls the system matrix calculation function according to `stm_model_type`.

   2. inputs and outputs
        + input
            * `stm_model_type`
                - The type of relative dynamics model
            * `reference_sat_orbit`
                - The orbit of the reference satellite
            * `mu` 
                - The gravity constant $`\mu`$
            * `elapsed_sec`
                - Elapsed simulation time
        + output
            * none 

   3. algorithm

   4. note

1. `CalculateHillSystemMatrix`

   1. overview
        + The `CalculateHillSystemMatrix` function calculates the system matrix of the Hill equation. 
        + This function is declared in `RelativeOrbitModels.h` and is used by the

   2. inputs and outputs
        + input
            * `orbit_radius`
                - Radius of the reference satellite orbit $`R`$
            * `mu` 
                - The gravity constant $`\mu`$
        + output
            * `system_matrix`
                - system matrix

   3. algorithm
        + The mean motion of the reference orbit ($`n`$) is calculated as follows:

        ```math
        n=\sqrt{\frac{\mu}{R^3}}
        ```

        + Then, the system matrix ($`\bm{A}`$) is calulated as follows:

        ```math
        \bm{A}=
        \begin{pmatrix}
        0 & 0 & 0 & 1 & 0 & 0 \\
        0 & 0 & 0 & 0 & 1 & 0 \\
        0 & 0 & 0 & 0 & 0 & 1 \\
        3n^2 & 0 & 0 & 0 & 2n & 0 \\
        0 & 0 & 0 & -2n & 0 & 0 \\
        0 & 0 & -n^2 & 0 & 0 & 0 \\
        \end{pmatrix}
        ```

   4. note

1. `CalculateHCWSTM`

   1. overview
        + The `CalculateHCWSTM` function calculates the Hill-Clohessy-Wiltshire STM. 
        + This function is declared in `RelativeOrbitModels.h` and is used by the

   2. inputs and outputs
        + input
            * `orbit_radius`
                - Radius of the reference satellite orbit $`R`$
            * `mu` 
                - The gravity constant $`\mu`$
            * `elapsed_sec`
                - Elapsed simulation time
        + output
            * `system_matrix`
                - system matrix

   3. algorithm
        + The mean motion of the reference orbit ($`n`$) is calculated as follows:

        ```math
        n=\sqrt{\frac{\mu}{R^3}}
        ```

        + Then, the system matrix ($`\bm{A}`$) is calulated as follows:

        ```math
        \bm{\Phi}(t,t0)=
        \begin{pmatrix}
        4-3\cos(nt) & 0 & 0 & \frac{\sin(nt)}{n} & \frac{2}{n}-\frac{2\cos(nt)}{n} & 0 \\
        -6nt+6\sin(nt) & 1 & 0 & -\frac{2}{n}+\frac{2\cos(nt)}{n} & \frac{4\sin(nt)}{n}-3t & 0 \\
        0 & 0 & \cos(nt) & 0 & 0 & \frac{\sin(nt)}{n} \\
        3n\sin(nt) & 0 & 0 & cos(nt) & 2\sin(nt) & 0 \\
        -6n+6n\cos(nt) & 0 & 0 & -2\sin(nt) & -3+4\cos(nt) & 0 \\
        0 & 0 & -n\sin(nt) & 0 & 0 & \cos(nt) \\
        \end{pmatrix}
        ```

   4. note

## 3. Results of verifications

1. Relative Orbit Propagation
   1. overview
      
      - Make sure the relative orbit is correctly propagated using a simple orbit
       
   2. conditions for the verification
      1. input files
            - Initialization files for the two satellites were prepared.
                - `Sat0.ini`
                - `Sat1.ini`
      2. initial values
            - The orbit of the reference satellite (Sat0) is GEO. The initial position of the satellite (Sat1) is $`(0\mathrm{m}, 100\mathrm{m}, 0\mathrm{m})^\mathrm{T}`$ in LVLH frame. The orbit was propagated for 86400 sec (the period of GEO).  
            - `Sat0.ini`

            ```
            propagate_mode = 0
            
            //Information used for orbital propagation by the Runge-Kutta method///////////
            //initial satellite position[m] 
            //＊The coordinate system is defined in PlanetSelect.ini
            init_position(0) = 4.2164140100E+07  //radius of GEO
            init_position(1) = 0
            init_position(2) = 0
            //initial satellite velocity[m/s]
            //＊The coordinate system is defined in PlanetSelect.ini
            init_velocity(0) = 0
            init_velocity(1) = 3.074661E+03  //Speed of a spacecraft in GEO
            init_velocity(2) = 0
            ///////////////////////////////////////////////////////////////////////////////
            ```

            - `Sat1.ini`

            ```
            propagate_mode = 2

            //Information used for relative orbit propagation//////////////////////////////
            //Relative Orbit Update Method (0 means RK4, 1 means STM)
            update_method = 0
            //RK4 Relative Dynamics model type (only valid for RK4 update)
            //0: Hill
            relative_dynamics_model_type = 0
            //STM Relative Dynamics model type (only valid for STM update)
            //0: HCW
            stm_model_type = 0
            //initial satellite position relative to the reference satellite in LVLH frame[m]
            //＊The coordinate system is defined in PlanetSelect.ini
            init_relative_position_lvlh(0) = 0.0
            init_relative_position_lvlh(1) = 100.0
            init_relative_position_lvlh(2) = 0.0
            //initial satellite velocity relative to the reference satellite in LVLH frame[m/s]
            //＊The coordinate system is defined in PlanetSelect.ini
            init_relative_velocity_lvlh(0) = 0.0
            init_relative_velocity_lvlh(1) = 0.0
            init_relative_velocity_lvlh(2) = 0.0
            //information of reference satellite
            reference_sat_id = 0
            reference_sat_ini_file = ../../data/ini/Sat0.ini
            ///////////////////////////////////////////////////////////////////////////////
            ```

   3. results

      - The position of Sat1 seen from Sat0 in the inertia frame was calculated.

        <div align="center">
        <img src="./figs/RelativeOrbit_verification_i_x.jpg" width=80% alt="">
        </div>
         <div align="center">
        <img src="./figs/RelativeOrbit_verification_i_y.jpg" width=80% alt="">
        </div>

      - They correctly move periodically.
      - In this example of verification, the RK4 method is used to propagate relative orbits, but the results were the same when using STM.
      
        

## 4. References

1. Kapila, V., Sparks, A. G., Buffington, J. M., & Yan, Q. (2000). Spacecraft formation flying: Dynamics and control. Journal of Guidance, Control, and Dynamics, 23(3), 561-564.