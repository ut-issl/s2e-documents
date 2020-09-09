# Specification for Attitude Dynamics

## 1.  Overview

1. functions
   
   - A class with the function to propagate the attitude motion equation that forms the basis of the attitude simulator.
   - Use the 4th Runge-Kutta equation for the propagation or set the attitude as determined values.
   - This class also calculates the angular momentum.

2. files
   
   - Attitude.cpp, Attitude.h : Definitions and declarations of the class
   - ControlledAttitude.h, .cpp : `ControlledAttitude` class is defined. The detail is described in `Spec_ControlledAttitude.md`
   - AttitudeRK4.h, .cpp : Normal free motion dynamics propagator `AttitudeRK4` class is defined here.
   - Init_Attitude.cpp : Interface functions for the initizalization of `Attitude` class
   - ControlledAttitude.ini:  Interface functions for the initizalization of `ControlledAttitude` class.
   - SimBase.ini : Initialization file

3. how to use
   
   - Set the parameters in `SimBase.ini`
        - If you want to use RK4 as attitude dynamics, please set  `propagate_mode = 0` at the ATTITUDE section in the `SimBase.ini` file.
        -  If you want to apply the pre-determined condition to attitude dynamics, please set  `propagate_mode = 1` at the ATTITUDE section in the `SimBase.ini` file.
   - Create instance by using initialization function `InitAttitude`
   - Execute attitude propagation by `Propagate` function
   - Use `Get*` function to get attitude information
     

## 2. Explanation of RK4 Algorithm 

1. `Propagate` function

   1. overview

      - This function manages the timings of `RungeOneStep` function, which calculates the attitude dynamics and kinematics by 4th Runge-Kutta method.

   2. inputs and outputs
      - input
         - (double) endtime: Time incremented in the main function
      - output
         - (void)

   3. algorithm

      There are two time steps related to the attitude propagation.
         1. Time incremented in the main function
            - The step to calculate the values of disturbance and component control.
            - The step is defined as the variable `prop_step_` in `sim_time` class.
         2. Time incremented in Propagate function
            - The step is much shorter than the time step in the main function. 
            - The step determines the accuracy of the attitude propagation.
            - The step is defined as the variable `prop_step_` in `attitude` class.

There is a while loop in `Propagate` function, in which Runge-Kutta integration is performed. In addition, there is only one Runge-Kutta integration function outside the while loop, but this is for adjusting the time lapse.

2. `RungeOneStep` function

   1. overview

      Calculate the attitude propagation by 4th Runge-Kutta integration.

   2. inputs and outputs
      - input
         - (double) t: Elapsed time from the time when the `Propagate` function is called.
         - (double) dt: The duration for the attitude propagation

   3. algorithm

      If the differential equation (1) is given, the state quantity in $`n+1`$ step can be calculated as (2).

       ```math
         \hat{\boldsymbol{x}} = \boldsymbol{f}(\boldsymbol{x},t)

         \tag{1}
       ```
       ```math
         \boldsymbol{x_{n+1}} = \boldsymbol{x_{n}} + \cfrac{\Delta t}{6}(\boldsymbol{k_1}+2\boldsymbol{k_2}
         +2\boldsymbol{k_3}+\boldsymbol{k_4})

         \tag{2}
       ```
      where $`\Delta t`$ is a time step, which meets the equation (3).

       ```math
         t_{n+1} = t_{n} + \Delta t

         \tag{3}
       ```

      $`k_i \, (i=1,2,3,4)`$, which has the same number of elements, can be calculated as the equations (4).

       ```math
         \boldsymbol{k_{1}} = \boldsymbol{f}(\boldsymbol{x_n},t_n) \\
         \boldsymbol{k_{2}} = \boldsymbol{f}\left(\boldsymbol{x_n}+\frac{\Delta t}{2} \boldsymbol{k_1},t_n+\frac{\Delta t}{2} \right) \\
         \boldsymbol{k_{3}} = \boldsymbol{f}\left(\boldsymbol{x_n}+\frac{\Delta t}{2} \boldsymbol{k_2},t_n+\frac{\Delta t}{2} \right)  \\
         \boldsymbol{k_{4}} = \boldsymbol{f}\left(\boldsymbol{x_n} + \Delta t \boldsymbol{k_3},t_n+\Delta t \right)

         \tag{4}
       ```

      In this attitude propagation, the quantity of state $`\boldsymbol{x}`$ consists of 7 elements, including `Quaternion_i2b` and angular velocity $`\boldsymbol{\omega}_b`$.

       ```math
         \boldsymbol{\omega}_b = [\omega_{bx} \, \omega_{by} \, \omega_{bz}]^T \\
         \boldsymbol{q}_{i2b} = [q_x \, q_y \, q_z \, q_w]^T \\
         \boldsymbol{x} = [\boldsymbol{\omega}_b, \boldsymbol{q}_{i2b}]^T

         \tag{5}
       ```


   4. note

      The one that solves the upper differential equation is implemented in Library, and it is said that it is used in random walk etc. I feel that it should be integrated there. (2016/5/25)

3. `DynamicsKinematics` function

   1. overview

      Equation of attitude motion is described in this function.

   2. inputs and outputs
      - input
         - (Vector<7>) x: Quantity of state
         - (double) t: Elapsed time from the time when the `Propagate` starts
      - output
         - (Vector<7>) dxdt: Differentiation of quantity of state.

   3. algorithm

      Equation of attitude motion is calculated as the equation (6), which is written in Chapter 6 of Reference 1,

       ```math
         \dot{\boldsymbol{\omega}}_b = \boldsymbol{I}_b^{-1}(\boldsymbol{T}_b - \boldsymbol{\omega}_b \times \boldsymbol{h}_b)

         \tag{6}
       ```

      where $`\boldsymbol{\omega}_b`$[rad/s] is angular velocity in the body-fixed coordinate, $`\boldsymbol{I}_b`$[kgm$`^2`$] is inertia tensor of the satellite, $`\boldsymbol{T}_b`$[Nm] is torque in the body-fixed coordinate, $`\boldsymbol{h}_b`$[Nms] is angular momentum of the satellite in the body-fixed coordinate.
      Quarternion_i2b is calculated from the kinematics equation (7). This equation is executed in `Omega4Kinematics` function.

       ```math
         \dot{\boldsymbol{q}}_{i2b} = \cfrac{1}{2}
         \begin{bmatrix}
            0 & \omega_{bz} & -\omega_{by} & \omega_{bx} \\
            -\omega_{bz} & 0 & \omega_{bx} & \omega_{by} \\
            \omega_{by} & -\omega_{bx} &0 & \omega_{bz} \\
            - \omega_{bx} & -\omega_{by} & -\omega_{bz} & 0
         \end{bmatrix}\boldsymbol{q}_{i2b}

         \tag{7}
       ```

## 3. Results of verifications

1. verification of kinematics equation
   1. overview
      
      - Check that the integral propagation of kinematics equations is performed correctly

   2. conditions for the verification
      - PropStepSec: 0.001
      - StepTimeSec: 0.1
      - EndTimeSec: 300
      - Inertia tensor: diag [0.17, 0.1, 0.25]
      - Initial Quaternion_i2b: [0,0,0,1]
      - Initial torque: [0,0,0]
      - Initial angular velocity: Set by each case
      - Disturbance torque: All Disable
   3. results
      - Initial angular velocity = [0,0,0]
  
         ![](./figs/test_kinematics_0.png)

      - Initial angular velocity = [0.314, 0, 0] rad/s
      
         ![](./figs/test_kinematics_px.png)
      
      - Initial angular velocity = [0, 0.314, 0] rad/s
      
         ![](./figs/test_kinematics_py.png)
      
      - Initial angular velocity = [0, 0, 0.314] rad/s
    
         ![](./figs/test_kinematics_pz.png)
      
      - Initial angular velocity = [0, 0, -0.314] rad/s
      
        ![](./figs/test_kinematics_mz.png)

2. verification of dynamics equation
   1. overview

      Confirm that the integral propagation of the dynamics equation is performed correctly

   2. conditions of the verification
      - PropStepSec: 0.001
      - StepTimeSec: 0.1
      - EndTimeSec: 300
      - Inertia tensor: diag[0.17, 0.1, 0.25]
      - Initial Quaternion_i2b: [0,0,0,1]
      - Initial torque: Set by each case
      - Initial angular velocity: [0,0,0]
      - Disturbance torque: All Disable

   3. results
      - Initial torque: [0,0,0] Nm
         - body frame
         ![](./figs/test_dynamics_0_b.png)

         - inertial frame
         ![](./figs/test_dynamics_0_i.png)


      - Initial torque = [0.1,0,0] Nm
         - Fail to output as fixed torque even when input in ini file. At the end of Dynamics-> Update (), torqie_b is updated to (0,0,0) every time, but it may still be reflected as 0sec torque.
         - Interim solution: change the value in NatakuComponents-> GenerateTorque ().
         - X axis is constant at inertial coordinates and aircraft fixed coordinates  
           -  body frame
               ![](./figs/test_dynamics_px_b.png)

           - inertial frame
               ![](./figs/test_dynamics_px_i.png)
      - Initial torque = [0,0.1,0] Nm
        -  body frame
         ![](./figs/test_dynamics_py_b.png)

        - inertial frame
         ![](./figs/test_dynamics_py_i.png)

      - Initial torque = [0,0,0.1] Nm
        - body frame
         ![](./figs/test_dynamics_pz_b.png)

        - inertial frame
         ![](./figs/test_dynamics_pz_i.png)

3. validation of attitude dynamics propagation time step
   1. overview

      Validate the time step of the attitude dynamics propagation

   2. conditions of the verification
      - PropStepSec: 0.001 / 0.01
      - StepTimeSec: 0.1
      - EndTimeSec: 300
      - Inertia tensor: diag[0.17, 0.1, 0.25]
      - Initial Quaternion_i2b: [0,0,0,1]
      - Initial torque: [0,0,0]
      - Initial angular velocity: [0,0,0]
      - Disturbance torque: All Disable

   3. results
      - No difference between two results in PropStepSec = 0.001 / 0.01 sec. 
        

## 4. References

1. 嘉. 狼, 信. 冨田, 真. 中須賀 , 三. 松永, 宇宙ステーション入門第二版, 文京区: 東京大学出版会, 2008. 
