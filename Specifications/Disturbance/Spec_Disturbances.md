# Specification of Disturbances class

## 1.  Overview

1. Functions
   - This class integrates all disturbances calculation.
   - All disturbances are initialized in this class.
   - Their update calculations are called in this class.

2. Related files
   - `src/disturbances/disturbances.hpp`
   - `src/disturbances/disturbances.cpp`

3. How to use
   - When you make a new disturbance class, you need to register the new disturbance class in the `InitializeInstances` function.
   - If you register your disturbance class correctly, the update function is automatically updated in the `Disturbances::Update` class, and the disturbance force and/or torque is added for dynamics propagation.


## 2. Explanation of Algorithm
1. `Update` function
   1. overview  
      - This function calls the `Disturbance::Update` functions defined by each disturbance class.
      - Generally, orbital disturbances depend on spacecraft position. Some disturbances depend on spacecraft attitude with respect to the disturbance sources. Therefore, there are two update timing in this function.
        - When the spacecraft position is updated, all disturbances are updated.
        - When the spacecraft attitude is updated, disturbances which depend on attitude are updated.

1. `InitializeInstances` function
   1. overview
      - The instances of all disturbance classes are made and registered to the disturbance list in this function.
      - The Earth only disturbances are registered when the selected center object is the Earth.

## 4. References






