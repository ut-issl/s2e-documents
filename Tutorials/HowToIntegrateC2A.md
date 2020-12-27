# How to integrate C2A

## 1.  Overview
- [C2A](https://gitlab.com/ut_issl/c2a) (Command Centric Architecture) is an architecture for spacecraft flight software developed by [ISSL](https://www.space.t.u-tokyo.ac.jp/nlab/index.html).
- S2E can optionally execute [C2A](https://gitlab.com/ut_issl/c2a) as a flight software for flight software development and debugging.
- This document describes how to integrate the C2A.

## 2. How to set up C2A
- When users want to use C2A, complete the following steps
  - Make `FlightSW` directory at same directory with `s2e_core_oss` and `s2e_user`.
  - Make a `c2a_user_oss` directory in `FlighSW` and clone a [C2A_USER repository](https://gitlab.com/ut_issl/c2a/c2a_user_oss) you want to use
    ```
    ├─FlightSW  
    │  └─ c2a_user_oss
    ├─s2e_core_oss
    └─s2e_user  
  - Edit `s2e_user/CMakeLists.txt`
    - `set(USE_C2A OFF)` -> `set(USE_C2A ON)`
  - Build `s2e_user`
 
**Note:** When you add a new C source file in C2A, you have to modify the `c2a_user_oss/CMakeLists.txt` directory to compile it in S2E.

