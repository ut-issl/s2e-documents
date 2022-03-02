# How to use serial port communication

## 1.  Overview
- Using the [SerialPort Class](https://docs.microsoft.com/en-us/dotnet/api/system.io.ports.serialport?view=dotnet-plat-ext-5.0) in System.IO.Ports Namespace, you can perform serial communication from the COM port of your computer.
- The HILS test can be performed by replacing satellite components with simulated components in S2E.
- This document describes how to use serial port communication.

## 2. How to build files for the HILS test
- **Currently, the HILS test is only available for Visual Studio users on Windows.**
- Serial port operations are written in `Interface/HilsInOut/Ports/HilsUartPort.cpp` in c++/cli language.
- When users want to execute the HILS test, complete the following steps.
  - Edit `s2e-core/CMakeLists.txt`
  - `set(USE_HILS OFF)` -> `set(USE_HILS ON)`
  - build `s2e-core`
- **Note**: Currently, breakpoints do not work if you build c++/cli and c++ files simultaneously.

## 3. Sample codes for UART communication
- The supported version of this section
  - s2e-core: [v4.0](https://github.com/ut-issl/s2e-core/releases/tag/v4.0)
- Hardware Settings
  - Set loopback connection of two USB-UART converters using two USB ports of your computer.
  - Check the COM port number for each connection.
- Software Settings
   - `s2e-core/src/Component/Abstract/ExpHils.cpp` is an example of a simulation component for serial port communication.
   - `ExpHils` is instantiated in `s2e-core/src/Simulation/Spacecraft/SampleComponents.cpp`.
   ```c++
  // Examples of HILS
  exp_hils_responder_ = new ExpHils(clock_gen, 1, obc_, 3, 9600, hils_port_manager_, 1);
  exp_hils_sender_ = new ExpHils(clock_gen, 0, obc_, 4, 9600, hils_port_manager_, 0);
   ```
   - Edit the constructor's argument based on the COM port number checked above.
   - For the HILS test, edit the setting of simulation speed in `s2e-core/data/SampleSat/ini/SampleSimBase.ini`.
   ```ini
   // Simulation speed. 0: as fast as possible, 1: real-time, >1: faster than real-time, <1: slower than real-time
   SimulationSpeed = 1
   ```

- Execution and Result
  - There are two ExpHils components, a sender component and a responder component.
    - The sender component sends out a new message like `ABC`, `BCD`, ....
    - The responder component returns the message as received.
    - Data returned from the responder to the sender is output.<img src="./figs/SerialPortCommunicationConfirmation.png" alt="SerialPortCommunicationConfirmation" style="zoom: 100%;" />
    - If the comment `Error: the specified step_sec is too small for this computer.` appears, comment out it in `s2e-core/src/Environment/Global/SimTime.cpp`.

## 4. Sample codes for I2C communication
- The SerialPort class can also be used to perform HILS tests on simulated I2C components. It is assumed that I2C-USB converters will be used and that serial communication will be performed between the COM port and the converter.
- The supported version of this section
  - s2e-core: TBD
- Hardware Settings
  - Set loopback connection of a I2C-USB controller converter and a I2C-USB target converter using two USB ports of your computer.<img src="./figs/SerialPortCommunication_I2CLoopback.png" alt="SerialPortCommunicationConfirmation" style="zoom: 30%;" />
  - Check the COM port number for each connection.
  - **Note** Loopback is not always necessary. Only one of the I2C controller or I2C target can be simulated in S2E.
- Software Settings
   - `s2e-core/src/Component/Abstract/ExpHilsI2cController.cpp` and `s2e-core/src/Component/Abstract/ExpHilsI2cTarget.cpp` are examples of simulation components for I2c communication.
   - `ExpHilsI2cController` and `ExpHilsI2cTarget` are instantiated in `s2e-core/src/Simulation/Spacecraft/SampleComponents.cpp`.
   ```c++
  exp_hils_i2c_controller_ = new ExpHilsI2cController(clock_gen, 5, 115200, hils_port_manager_);
  exp_hils_i2c_target_ = new ExpHilsI2cTarget(clock_gen, 0, 0x44, obc_, 6, hils_port_manager_);
   ```
   - Edit the constructor's argument based on the COM port number checked above.
   - Edit the baud rate and I2C address according to the converter and simulation conditions.
   - For the HILS test, edit the setting of simulation speed in `s2e-core/data/SampleSat/ini/SampleSimBase.ini`.
   ```ini
   // Simulation speed. 0: as fast as possible, 1: real-time, >1: faster than real-time, <1: slower than real-time
   SimulationSpeed = 1
   ```

- Execution and Result
  - There are two components, an I2C controller component and an I2C target component.
  - controller
    - Send a command to the target.
      - Send a command to request a telemetry. 1 byte register address is sent to specify the first address of the data to be read from the controller.
      - Send a command to read a telemetry from the I2C-USB converter (target).
  - target
    - Receive commands from controller and send telemetry to controller.
      - After receiving the telemetry request command, send the telemetry (like ABCDE, BCDEF, ...) to the I2C-USB converter (target).
  - **Note** Currently, the latency from the time the I2C-USB converter receives the data via I2C communication to the time it is sent to the I2c target component via serial communication is large, making it impossible to immediately respond to telemetry request commands.
    - Three frames of telemetry is stored in the I2C-USB converter (target) in advance.
    - Each time the telemetry stored in converter is read by the I2C read commnad, the telemetry is added from the target component.
  -  The data sent by the target and the data received by the controller are the outputs. Since there are three frames accumulated in the converter,  the controller is receiving telemetry that was sent three cycles before from target.<img src="./figs/SerialPortCommunication_Confirmation2.png" alt="SerialPortCommunicationConfirmation" style="zoom: 50%;" />
  - If the comment `Error: the specified step_sec is too small for this computer.` appears, comment out it in `s2e-core/src/Environment/Global/SimTime.cpp`.
