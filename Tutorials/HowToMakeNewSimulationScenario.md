# How To Make New Simulation Scenario

## 1.  Overview

- In [Getting Started](./Tutorials/GettingStarted.md) tutorial, we can directory build and execute S2E_CORE, but for **source code sharing** and practical usage of S2E, we **strongly recommend to manage S2E_CORE and S2E_USER repository separately**.
  - [S2E_CORE](https://gitlab.com/ut_issl/s2e/s2e_core_oss) repository is shared with other ISSL_OSS users. Most of the sources are in this repository. The codes are used as a library by the S2E_USER repository.
    - If you don't want to be affected by updates from other users, please use `fork` function of Git. If you have some updates in the forked repository, we recommend to merge original S2E_CORE repository.
  - S2E_USER repository is an independent repository  for **each spacecraft project or research project**. This repository includes following parts:
    - Source codes for simulation scenario and main
    - Initialize files
    - Compile setting files as [CMake files](https://cmake.org/), [Visual Studio Solution files](https://visualstudio.microsoft.com/downloads/), and others. 
- This tutorial explains how to make S2E_USER repository and execute it.   

**Note:** For ISSL members, [S2E_6U](https://gitlab.com/ut_issl/s2e/s2e_6u) and [S2E_EQUULEUS](https://gitlab.com/ut_issl/s2e/s2e_equuleus) are good examples to make S2E_USER repository, so please check them.

## 2. Setup S2E_CORE

1. Clone [S2E_CORE_OSS](https://gitlab.com/ut_issl/s2e/s2e_core_oss) repository in the same directory with `s2e_user`.
2.  Execute `./script/dowload_cspice_VS32bit.bat` to set up CSPICE library.
    ```
    └─s2e_core_oss  
    └─ExtLibraries  
      └─ cspice 
    ```
## 3. Setup & Compile S2E_USER

1. Make a new directory `s2e_user`. It will be a root directory of S2E_USER
    ```
    └─s2e_user  
    └─s2e_core_oss  
    └─ExtLibraries  
    ```

2. Copy directories and files in  `s2e_user` directory in the `SampleCodes`

3. According to the [How to compile with Visual Studio](./General/HowToCompileWithVisualStudio.md), open the `s2e_user/CMakeList.txt` and compile the S2E_USER

4. Execute and check the `s2e_user/data/logs`

5. Similar with [Getting Started](./Tutorials/GettingStarted.md), you can edit initialize files and check the log file 

**Note:** You can use other characters instead of `user` for a practical case.  For example, you can name it as `s2e_equuleus` to indicate EQUULEUS spacecraft project. 

## 4.  Overview of S2E_USER

- This chapter explains overview of `s2e_user` in `SampleCodes`. 
- The files in the directory are follow. From here, the detail of each file is described.
  ```
    └─s2e_user 
      └─CMakeLists.txt  
      └─CMakeSetting.json  
      └─data  
        └─ini  
          └─initialize files  
        └─logs  
      └─src  
        └─Simulation  
          └─Case  
            └─User_case.cpp  
            └─User_case.h  
          └─Spacecraft  
            └─User_Components.cpp  
            └─User_Components.h  
            └─User_sat.cpp  
            └─User_sat.h  
        └─S2E_USER.cpp  
  ```
1. `CMakeLists.txt ` and `CMakeSetting.json `
   -  `CMakeLists.txt `  is a [CMake file](https://cmake.org/) for compile setting.
     - Details of description rules for CMake files can be search in the internet, so please refer them.
     - Of course, when you add new source files, you have to edit the CMake file to compile them.
   - `CMakeSetting.json ` is a compile setting file for Visual Studio.
2. `data/ini` and `data/logs`
   - In `ini` directory, there are several initialize files.
     - The most important initialize file is `User_SimBase.ini`.
     - Other initialize files are defined in this base initialize file. So you should edit the file names in the base file when you modify the name of other initialize file.
       - When you changed the name of the base file, you have to edit `S2E_USER.cpp`
     - Details of the initialize files are described in `Specifications`
       - Basic files are described in [Getting Started](./Tutorials/GettingStarted.md).
   - `logs`
     - CSV log files will be outputted here. The output directory is also defined in `User_SimBase.ini`, so you can change it.
3. `src/S2E_USER.cpp`
   - The main file of this program.
   - In this code, `User_SimBase.ini` is defined as base file for the simulation, and an instance of `simulation case class` named as `UserCase` is created and initialized. And finally, the main routine of the class is executed.
4.  `src/Simulation/Case`
   - `UserCase` class is defined here. `UserCase` class has a simulation settings as `time`, `log`, and `simulation configs`. The class also has an instance of `spacecraft` class named as `UserSat`.
5. `src/Simulation/Spacecraft/User_sat.cpp `
   - `UserSat` class is defined here. `UserSat` class has instances of `Dynamics`, `Environment`, `Disturbance`, and `UserComponents`.
     - `Dynamics` is called in the base class `Spacecraft` .
   - In the `UserSat`'s `Update` function, these four classes are updated to simulate the spacecraft behavior.
6. `src/Simulation/Spacecraft/User_Components.cpp`
   - `UserComponents` class is defined here. Most of the users edit this code to custom the S2E for their satellite projects.
   - Users select components they want to use from the `S2E_CORE_OSS/src/Component`.

