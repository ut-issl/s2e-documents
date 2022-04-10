# Specification for Kepler Orbit Propagation

## 1.  Overview

1. Functions
   - The `KeplerOrbit` class calculates the satellite position and velocity with the simple two-body problem. We ignored any disturbances and generated forces by the satellite.
   - This orbit propagation mode provides the simplest and fastest orbit calculation for any orbit(LEO, GEO, Deep Space, and so on.).

2. Files
   - src/Dynamics/Orbit/KeplerOrbitPropagation.cpp, hpp
   - src/Library/Orbit/KeplerOrbit.cpp, hpp
   - src/Library/Orbit/OrbitalElements.cpp, hpp
   - src/Interface/InitInput/Init_Orbit.cpp

3. How to use
   - Select `propagate_mode = KEPLER` in the spacecraft's ini file.
   - Choose a way to define the orbit.
     - Defined by initial position and velocity.
       - Select `init_mode_kepler = INIT_POSVEL`
       - Set the value `init_position` and `init_velocity` in the ini file.
         - The units are `m`(meter) and `m/s`.
         - The frame is inertial frame, and the center is defined in the `PlanetSelect`.
     - Defined by the orbital elements.
       - Select `init_mode_kepler = INIT_OE`
       - Set the value of following orbital elements
         - $`a`$ : Semi major axis [m]
         - $`e`$ : Eccentricity
         - $`i`$ : Inclination [rad]
         - $`\Omega`$ : Right Ascension of the Ascending Node (RAAN) [rad]
         - $`\omega`$ : Argument of Perigee [rad]
         - $`t_{epoch}`$ : Epoch [julian day]
   
## 2. Explanation of Algorithm

1. `KeplerOrbit::CalcConstKeplerMotion` function
   1. Overview
      - This function calculates the following constant values.
        - Mean motion
        - Frame conversion matrix from in-plane position to the inertial frame position

   2. Inputs and outputs
      - Input
        - Orbital Elements
        - $`\mu`$ : The standard gravitational parameter of the central body
      - Output
        - $`n`$ : Mean motion
        - $`R_{p2eci}`$ : Frame conversion matrix from in-plane position to the inertial frame position
          - We use the name ECI here, but `Earth center` is not essential. When users choose the center body as other than the earth, the origin of the frame is changed to the body.

   3. Algorithm
      - Mean motion
      ```math
      n = \sqrt{\frac{\mu}{a^3}}
      ```
      - Frame conversion matrix from in-plane position to ECI position
        ```math
        R_{p2eci} = R_z(-\Omega)R_x(-i)R_z(-\omega)
        ```
        ```math
        R_x(\theta) = \begin{pmatrix}
                      1 & 0 & 0 \\
                      0 &  \cos{\theta} & \sin{\theta} \\
                      0 & -\sin{\theta} & \cos{\theta}
                      \end{pmatrix}
        ```
        ```math
        R_z(\theta) = \begin{pmatrix}
                      \cos{\theta} & \sin{\theta} & 0 \\
                      \-\sin{\theta} & \cos{\theta} & 0 \\
                      0 & 0 & 1
                      \end{pmatrix}
        ```

2. `KeplerOrbit::CalcPosVel` function
   1. Overview
      - This function calculates the position and velocity of the spacecraft in the inertial frame at the designated time.

   2. Inputs and outputs
      - Input
        - $`t`$ : Time in Julian day
        - Orbital Elements
        - Constants
      - Output
        - $`r_{eci}`$ : Position in the inertial frame
        - $`v_{eci}`$ : Velocity in the inertial frame

   3. Algorithm
      - Calculate mean anomaly $`l`$[rad]
        ```math
        l = n * (t-t_{epoch})
        ```
      - Calculate eccentric anomaly $`u`$[rad] by solving the Kepler Equation
        - Details are described in the next sub section
      - Calculate two dimensional position $`x^*, y^*`$ and velocity $`\dot{x}^*, \dot{y}^*`$ in the orbital plane
        ```math
        x^* = a(\cos{u}-e)\\
        y^* = a\sqrt{1-e^2}\sin{u}\\
        \dot{x}^* = -an\frac{\sin{u}}{1^e\cos{u}}\\
        \dot{y}^* = an\sqrt{1-e^2}\frac{\cos{u}}{1^e\cos{u}}\\
        ```
      - Convert to the inertial frame
        ```math
        r_{eci} = R_{p2eci}\begin{bmatrix} x^* \\ y^* \\ 0 \end{bmatrix}\\
        v_{eci} = R_{p2eci}\begin{bmatrix} \dot{x}^* \\ \dot{y}^* \\ 0 \end{bmatrix}\\
        ```

3. `KeplerOrbit::SolveKeplerFirstOrder` function
   1. Overview
      - This function solves the Kepler Equation with the first order iterative method.
      - Note: This method is not suit to the high eccentricity orbit. It is better to use the Newton-Raphson method for such case.

   2. Inputs and outputs
      - Input
        - $`e`$ : eccentricity
        - $`l`$ : mean anomaly [rad]
        - $`\epsilon`$ : threshold for convergence [rad]
        - Limit of iteration
      - Output
        - $`u`$ : eccentric anomaly [rad]

   3. Algorithm
      - Set the initial value of eccentric anomaly as follows
        - $`u_0=l`$
      - Calculate $`u_{n+1}`$ with the following equation
        ```math
        u_{n+1} = l + e\sin{u_n}
        ```
      - Iterate the calculation until the following conditions are satisfied
        - $`|u_{n+1} - u_{n}| < \epsilon`$
        - The iteration number overs the limit of iteration

## 3. Results of verifications
TBW

## 4. References
- Hiroshi Kinoshita, "Celestial mechanisms and orbital dynamics", 1998 (written in Japanese)
