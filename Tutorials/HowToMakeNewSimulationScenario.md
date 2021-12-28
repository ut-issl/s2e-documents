# How To Make New Simulation Scenario

## 1.  Overview

- In the [Getting Started](./Tutorials/GettingStarted.md) tutorial, we can directly build and execute S2E_CORE_OSS, but for **source code sharing** and practical usage of S2E, we **strongly recommend managing S2E_CORE_OSS and S2E_USER repository separately**.
  - [s2e-core](https://github.com/ut-issl/s2e-core) repository is shared with other users. Most of the source files are in this repository. The codes are used as a library by the S2E_USER repository.
  - S2E_USER repository is an independent repository  for **each spacecraft project or research project**. This repository includes the following parts:
    - Source codes for `simulation scenario` and the `main`
    - Source codes for `components` if you have components, which strongly depends on your project.
    - Initialize files
    - Compile setting files as [CMake files](https://cmake.org/), [Visual Studio Solution files](https://visualstudio.microsoft.com/downloads/), and others. 
- This tutorial explains an example of how to make S2E_USER repository and execute it.   
- The supported version of this document
  - s2e-core: [v4.0](https://github.com/ut-issl/s2e-core/releases/tag/v4.0)

## 2. Setup S2E_CORE

1. Clone [s2e-core](https://github.com/ut-issl/s2e-core) repository in the same directory with `s2e_user`.

2.  Execute script files to set up CSPICE and NRLMSISE-00 library.
    ```
    └─s2e-core  
    └─ExtLibraries  
      └─ cspice 
      └─ nrlmsise00
    ```

## 3. Setup & Compile S2E_USER

1. Make a new directory `s2e_user`. It will be a root directory of S2E_USER
    ```
    └─s2e_user  
    └─s2e-core  
    └─ExtLibraries  
    ```

2. Copy directories and files in  `s2e_user` directory in the `./Tutorials/SampleCodes/`

3. According to the [How to compile with Visual Studio](../General/HowToCompileWithVisualStudio.md), open the `s2e_user/CMakeList.txt` and compile the S2E_USER
   - You can also build it with Ubuntu in Docker. Please check [How to compile with Ubuntu in Docker](../General/HowToCompileWithUbuntuInDocker.md)

4. Execute and check the `s2e_user/data/logs`

5. Similar to [Getting Started](./GettingStarted.md), you can edit initialize files and check the log file 

**Note:** You can use other characters instead of `user` for a practical case.  For example, you can name it `s2e_equuleus` to indicate the EQUULEUS spacecraft project. 

## 4.  Overview of S2E_USER

- This chapter explains the overview of `s2e_user` in the `SampleCodes` directory. 
- The files in the directory are as follows. From here, the detail of each file is described.
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
   -  `CMakeLists.txt `  is a [CMake file](https://cmake.org/) for a compile setting.
     - Details of description rules for CMake files can be searched on the internet, so please refer to them.
     - Of course, when you add new source files, you have to edit the CMake file to compile them.
   - `CMakeSetting.json ` is a compile setting file for Visual Studio.
2. `data/ini` and `data/logs`
   - In the `ini` directory, there are several initialize files.
     - The most important initialize file is `User_SimBase.ini`.
     - Other initialize files are defined in this base initialize file. So you need to edit the file names in the base file when you modify the name of other initialize files.
       - When you change the name of the base file, you have to edit `S2E_USER.cpp`.
     - Details of the initialize files are described in `Specifications`.
       - Basic files are described in [Getting Started](./Tutorials/GettingStarted.md).
   - `logs`
     - CSV log files will be outputted here. The output directory is also defined in `User_SimBase.ini`, so that you can change it.
3. `src/S2E_USER.cpp`
   - This is the main file of this program.
   - In this code, `User_SimBase.ini` is defined as the base file for the simulation, and an instance of the `simulation case class` named `UserCase` is created and initialized. And finally, the main routine of the class is executed.
4.  `src/Simulation/Case`
   - `UserCase` class is defined here. `UserCase` class inherits the `SimulationCase` base class in the `S2E_CORE`. The `SimulationCase` class has a `SimulationConfig` and `GlobalEnvironment` class. The `UserCase` class has an instance of the `spacecraft` class named as `UserSat`.
5. `src/Simulation/Spacecraft/User_sat.cpp `
   - `UserSat` class is defined here. `UserSat` class inherits the `Spacecraft` class in the `S2E_CORE`. The `Spacecraft` base class has instances of `Dynamics`, `LocalEnvironment`, `Disturbance`, and `Structure`. And the `UserSat` class has an instance of `UserComponents`.
   - In the `UserSat`'s `Update` function, these four classes are updated to simulate the spacecraft behavior.
6. `src/Simulation/Spacecraft/User_Components.cpp`
   - The `UserComponents` class is defined here. Most users edit this code to custom the S2E for their satellite projects.
   - Users select components they want to use from the `s2e-core/src/Component`.
   - You can add new source codes in the `S2E_USER/Component` directory if you want to make original components.
