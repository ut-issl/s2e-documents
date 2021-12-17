# How to use serial port communication

## 1.  Overview
- Using the [SerialPort Class](https://docs.microsoft.com/en-us/dotnet/api/system.io.ports.serialport?view=dotnet-plat-ext-5.0) in System.IO.Ports Namespace, you can perform serial communication from the COM port of your computer.
- The HILS test can be performed by replacing satellite components with simulated components in S2E.
- This document describes how to use serial port communication.
- The supported version of this document
  - S2E_CORE_OSS: [c3ba](https://gitlab.com/ut_issl/s2e/s2e_core_oss/-/commit/c3ba6d93418998b91efc0a8ca57ff63e350d2636)

## 2. How to build files for the HILS test
- **Currently, the HILS test is only available for Visual Studio users on Windows.**
- Serial port operations are written in `Interface/HilsInOut/Ports/HilsUartPort.cpp` in c++/cli language.
- When users want to execute the HILS test, complete the following steps.
  - Edit `s2e_core_oss/CMakeLists.txt`
  - `set(USE_HILS OFF)` -> `set(USE_HILS ON)`
  - build `s2e_core_oss`
- **Note**: Currently, breakpoints do not work if you build c++/cli and c++ files simultaneously.

## 3. Sample codes for UART communication
- Hardware Settings
  - Set loopback connection of two USB-UART converters using two USB ports of your computer.
  - Check the COM port number for each connection.
- Software Settings
   - `s2e_core_oss/src/Component/Abstract/ExpHils.cpp` is an example of a simulation component for serial port communication.
   - `ExpHils` is instantiated in `s2e_core_oss/src/Simulation/Spacecraft/SampleComponents.cpp`.
   ```c++
  // Examples of HILS
  exp_hils_responder_ = new ExpHils(clock_gen, 1, obc_, 3, 9600, hils_port_manager_, 1);
  exp_hils_sender_ = new ExpHils(clock_gen, 0, obc_, 4, 9600, hils_port_manager_, 0);
   ```
   - Edit the constructor's argument based on the COM port number checked above.
   - For the HILS test, edit the setting of simulation speed in `s2e_core_oss/data/SampleSat/ini/SampleSimBase.ini`.
   ```ini
   // Simulation speed. 0: as fast as possible, 1: real-time, >1: faster than real-time, <1: slower than real-time
   SimulationSpeed = 1
   ```

- Execution and Result
  - There are two ExpHils components, a sender component and a responder component.
    - The sender component sends out a new message like `ABC`, `BCD`, ....
    - The responder component returns the message as received.
    - Data returned from the responder to the sender is output.<img src="./figs/SerialPortCommunicationConfirmation.png" alt="SerialPortCommunicationConfirmation" style="zoom: 100%;" />
    - If the comment `Error: the specified step_sec is too small for this computer.` appears, comment out it in `s2e_core_oss/src/Environment/Global/SimTime.cpp`.
