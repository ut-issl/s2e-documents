# Specification of Geo Potential Calculation

## 1.  Overview

1. Functions
   - `Disturbance` is a base class for all disturbance classes.

2. Related files
   - `src/disturbances/disturbance.hpp`

3. How to use   
   - When you want to make a new disturbance class, you need to inherit this.
   - Users need to define the `Update` function according to the target disturbance calculation. And update the members `force_b_N`, `torque_b_Nm`, `acceleration_b_m_s2_`, and/or `acceleration_i_m_s2_` in the function.
   - If the disturbance does not depend on the spacecraft attitude, please set `is_attitude_dependent_ = false` to avoid unnecessary disturbance update.


## 2. Explanation of Algorithm

No algorithm.

## 4. References






