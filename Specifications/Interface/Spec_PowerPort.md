# Specification of Power Port

## 1.  Overview
1. Functions
   - `PowerPort` class provides features of an electrical power connection.
   - Users can use the class to control the electrical power switching of components and calculate the component's consumed electrical current.
2. Related files
   - Main files: `PowerPort.cpp, .h`
   - Referenced files: `ComponentBase.cpp, .h` and `PCU.cpp, .h`
3. How to use
   - **Example**: The `SampleComponents` in the `S2E_CORE_OSS/Simulation/Spacecraft/SampleSpacecraft` is helpful to know how to use the feature.
   - Make a component class that inherits the `ComponentBase` class.
     - The `ComponentBase` class has the `PowerPort` class as a member and controls the component's action according to the electrical power switches.
   - Make an instance of `PCU` and connect the power port.
     - The `PCU` base class has a member of the `map` of the `PowerPort` class and manages the port id and connection of the `PowerPort`.
     - Users can make their PCU by inheriting the `PCU` base class and can control the power switching in the `MainRoutine` function.
     ```cpp
     pcu_ = new PCU(clock_gen);
     pcu_->ConnectPort(0, 0.5, 3.3, 0.3);
     ```
   - Make an instance of the components with the connected `PowerPort`.
     ```cpp
     obc_ = new OBC(1, clock_gen, pcu_->GetPowerPort(0));
     ```
   - Control the power switches by using the `PCU`.
     - The default setting of the power switch is `off`, so users need to power on the port to execute the `MainRoutine` of the components.
     ```cpp
     pcu_->GetPowerPort(0)->SetVoltage(3.3);
     ```
   - **Note**: The virtual power port is created when users make an instance of the `ComponentBase` class and its subclasses without the `PowerPort` information. The virtual port has a minus value port ID, and the switch state is originally `ON`, but the consumed power is zero.

## 2. Explanation of Algorithm
1. SetVoltage
   1. overview
      - This function is a setter function of the supply voltage to the power port.
      - Users can control the power switch by using this function.

   2. inputs and outputs
      - input: supply voltage to the port
      - output: switch state of the port

   3. algorithm
      - After the voltage is set, the `Update` function is called to check that the supply voltage is enough to turn on the component.

   4. note: N/A

1. Update
   1. overview
      - This is an update function of the switch state and the consumed current.
      - This function also has an over-current protection feature.

   2. inputs and outputs
      - input: N/A (members of the class)
      - output: switch state of the port

   3. algorithm
      - When the supply voltage is larger than the `kMinimumVoltage` of the component, the switch state becomes `true`, and the consumed current is calculated as the following equation.
      ```math
      I = P/V
      ```
      - The `P` is the `assumed_power_consumption`, and users can set the value with the `SetAssumedPowerConsumption` function.
      - If the calculated current consumption is larger than the `kCurrentLimit`, the over-current protection feature is executed and turning the switch off.

   4. note: N/A

## 3. Results of verifications
N/A

## 4. References
N/A