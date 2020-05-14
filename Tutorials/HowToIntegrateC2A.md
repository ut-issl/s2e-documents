# How to integrate C2A

## 1.  Overview

- [C2A](https://gitlab.com/ut_issl/c2a) (Command Centric Architecture) is an architecture for spacecraft flight software developed by [ISSL](https://www.space.t.u-tokyo.ac.jp/nlab/index.html).
- S2E can optionally execute [C2A](https://gitlab.com/ut_issl/c2a) as a flight software.
- This document describes how to integrate the C2A


## 2. How to set up C2A

- If users want to use C2A, complete the following steps
  - Make `FlightSW` directory at same directory with `S2E_CORE`

  - Make `C2A` directory in `FlighSW` and clone a [C2A repository](https://gitlab.com/ut_issl/c2a) you want to use

    ├─FlightSW  
    │  └─C2A  
    └─S2E_CORE  

  - Edit `S2E_CORE/CMakeLists.txt`
    
    - `set(USE_C2A OFF)` -> `set(USE_C2A ON)`
    
  - Build `S2E_CORE` with Visual studio

    - See [How to make VS project from CMake.md](./How to make VS project from CMake.md)
    - Currently, C2A integration is confirmed with only Visual Studio Compiler.


**Note:** When you add new C source file in C2A, you have to modify `C2A/CMakeLists.txt` directory to compile it in S2E.

