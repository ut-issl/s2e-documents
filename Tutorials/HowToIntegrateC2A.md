# How to integrate C2A

## 1.  Overview
- [C2A](https://github.com/ut-issl/c2a-core) (Command Centric Architecture) is an architecture for spacecraft flight software developed by [ISSL](https://www.space.t.u-tokyo.ac.jp/nlab/index.html).
- S2E can execute [C2A](https://github.com/ut-issl/c2a-core) as a flight software for onboard algorithm development and debugging.
- This document describes how to integrate the C2A.
- Notes
  - C2A is written in C language, but S2E builds C2A as C++.
- Sample codes
  - A sample of s2e-user: [s2e-user-for-c2a-core](https://github.com/ut-issl/s2e-user-for-c2a-core)
  - A sample of c2a-user: [C2A minimum user](https://github.com/ut-issl/c2a-core/tree/develop/Examples/minimum_user_for_s2e)
- Preparation to use the sample codes
  - Clone the `s2e-core` v5.0.0.
    - Please set the environment for that the s2e-core can work without C2A.
  - Clone the sample codes in the `FlightSW` directory.
  - Execute `c2a-core/setup.sh` or `c2a-core/setup.bat`.


## 2. How to build C2A in S2E
- When users want to use C2A, complete the following steps
  - Make `FlightSW` directory at same directory with `s2e-core` and `s2e-user`.
  - Make a `c2a-user` directory in `FlightSW` and set the C2A source code you want to use.
    ```
    ├─ExtLibraries
    ├─FlightSW
    │  └─c2a-user
    │    └─src_user
    │    └─src_core
    ├─s2e-core
    └─s2e-user
    ```
  - Edit `s2e-user/CMakeLists.txt`
    - `set(C2A_NAME "c2a_sample")`
      - Edit the directory name according to your situation
      - If you use the sample codes, please edit here as `c2a-core/Examples/minimum_user_for_s2e`
    - `option(USE_C2A "Use C2A" OFF)`
      - Turn on the USE_C2A flag as `option(USE_C2A "Use C2A" ON)`
  - Build the `s2e_user`
  - **Note:** When you add new source files in the C2A, you need to modify the `c2a-user/CMakeLists.txt` directory to compile them in the S2E.
    - Users can choose the construction of CMake as users need.
    - For example, the sample codes have several `CMakeLists.txt` files in each directory to set the compile targets, so users need to modify them to add the target source codes.


## 3. How to execute C2A in S2E
- In the default setting of S2E, C2A is built but isn't executed. To execute the C2A, users need to add the `OBC`, which can execute the C2A.
- The `s2e-core` has the [OBC_C2A](https://github.com/ut-issl/s2e-core/blob/develop/src/Component/CDH/OBC_C2A.cpp) as a component, and users can use it to execute the C2A.
- Users can use the `OBC_C2A` class in the `User_components` class, the same as other components.
- The sample `s2e-user-for-c2a-core` already mounts the `OBC_C2A` as a component.


## 4. Communication between C2A and S2E
- Generally, communication between flight software and S2E is executed via `OBC` class.
- The `OBC` base class has communication ports and communication functions. Other components and flight software can use the communication functions to communicate.
- For C2A, the `OBC_C2A` has the following functions for C2A flight software. The driver functions in the flight software can use these functions. It is essential to use the same `port_id` with the component setting in S2E. The details are described in specification documents for each feature. 
  - Serial communication functions
    ```cpp
    int OBC_C2A_SendFromObc(int port_id, unsigned char* buffer, int offset, int count);
    int OBC_C2A_ReceivedByObc(int port_id, unsigned char* buffer, int offset, int count);
    ```
  - I2C communication functions
    ```cpp
    int OBC_C2A_I2cWriteCommand(int port_id, const unsigned char i2c_addr, const unsigned char* data, const unsigned char len);
    int OBC_C2A_I2cWriteRegister(int port_id, const unsigned char i2c_addr, const unsigned char* data, const unsigned char len);
    int OBC_C2A_I2cReadRegister(int port_id, const unsigned char i2c_addr, unsigned char* data, const unsigned char len);
    ```
  - GPIO
    ```cpp
    int OBC_C2A_GpioWrite(int port_id, const bool is_high);
    bool OBC_C2A_GpioRead(int port_id);
    ```
- Currently, the C2A uses the wrapper functions in [IfWrapper/Sils](https://github.com/ut-issl/c2a-core/tree/develop/Examples/minimum_user_for_s2e/src/src_user/IfWrapper/Sils). The functions automatically overload the normal IfWrapper functions when C2A is executed on the S2E.
- Other interfaces like SPI, etc., will be implemented.


# 5. Sample codes for S2E-C2A communication
- S2E side
  - Users can use the [EXP](https://gitlab.com/ut_issl/s2e/s2e_core_oss/-/blob/develop/src/Component/Abstract/EXP.h) class in `S2E_CORE_OSS` as a test component to communicate with C2A.
  - Add `EXP` as a component in `User_Component` with reference to the sample codes in `Tutorials/SampleCodes/C2A_Integration/S2E_src`.
  - Edit the following parameters in `User_SimBase.ini` since the C2A's time update frequency is 1msec.
    ```
    StepTimeSec=0.001 //sec
    CompoUpdateIntervalSec = 0.001 //sec 
    ```
- C2A side
  - Edit `AppRegistry.c,h`, `rs422_dummy.c,h`, and `driver_update.c` with reference to the sample codes.
    - `AppRegistry.h`: Add `AR_DI_RS422_DUMMY,` .
    - `AppRegistry.c`: Add `add_application_(AR_DI_RS422_DUMMY, RS422_create_dummy);`. 
    - `rs422_dummy.c,h`: Replace most of the codes.
    - `driver_update.c`: Add the `AR_DI_RS422_DUMMY` execution command in block commands.
      ```cpp
      CCP_form_app_cmd(&temp, 0, AR_DI_RS422_DUMMY);
      BCT_register_cmd(&temp); 
      ```
- Execution and Result
  - Please use the `breakpoint` feature to check that the communication between `EXP` and `RS422_dummy` works well.
    - The `RS422_dummy` sends capital alphabets from `A` to `Z` with the `SET` command for `EXP`.
    - The `EXP` receives the command, stores the received characters in the buffer, and sends the buffer data to `RS422_dummy`.
    - Users can check the `RS422_dummy`'s received data (test_rx_data_) at the following breakpoint.
    ```c
    // Receive
    RS422_RX(&rs422_dummy_ch_[test_ch], &test_rx_data_[0], 100);
    } //<- breakpoint
    ```

  <img src="./figs/C2aCommunicationConfirmation.png" alt="C2aCommunicationConfirmation" style="zoom: 100%;" />
