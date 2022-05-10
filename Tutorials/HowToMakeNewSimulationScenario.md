# How To Make New Simulation Scenario

## 1.  Overview

- In the [Getting Started](./GettingStarted.md) tutorial, we can directly build and execute `s2e-core`, but for **source code sharing** and practical usage of S2E, we **strongly recommend managing s2e-core and s2e-user repository separately**.
  - [s2e-core](https://github.com/ut-issl/s2e-core) repository is shared with other users. Most of the source files are in this core repository. The codes are used as a library by the `s2e-user` repository.
  - `s2e-user` repository is an independent repository  for **each spacecraft project or research project**. This repository includes the following parts:
    - Source codes for the `main`
    - Source codes for `simulation scenario`
    - Source codes for `components` if the target spacecraft has components, which strongly depends on your project.
    - Initialize files
    - Compile setting files as [CMake files](https://cmake.org/), [Visual Studio Solution files](https://visualstudio.microsoft.com/downloads/), or others. 
- This tutorial explains an example of how to make `s2e-user` repository and execute it.   
- The Supported version of this document
  - Please confirm that the version of the documents and s2e-core is compatible.


## 2. Setup S2E_CORE

1. Clone [s2e-core](https://github.com/ut-issl/s2e-core) repository in a working directory.

2. Download mandatory `ExtLibraries` (CSPICE and NRLMSISE-00).
   - Please see a `How To Compile` document suit wity your platform.
     ```
     └─s2e-core  
     └─ExtLibraries  
       └─ cspice 
       └─ nrlmsise00
     ```


## 3. Setup & Compile S2E_USER

1. Make a new directory `s2e-user`. It will be a root directory of s2e-user.
   ```
   └─s2e-user  
   └─s2e-core  
   └─ExtLibraries  
   ```

2. Copy directories and files in the `./Tutorials/SampleCodes/s2e-user`.

3. According to the `How to compile` document, open the `s2e-user/CMakeList.txt` and build the s2e-user.

4. Execute and check the `s2e-user/data/logs`.

5. Similar to [Getting Started](./GettingStarted.md), you can edit initialize files and check the log file .

**Note:** You can use other characters instead of `user` for a practical case.  For example, you can name it `s2e_equuleus` to indicate the EQUULEUS spacecraft project. 


## 4.  Overview of S2E_USER

- This chapter explains the overview of `s2e-user` in the `SampleCodes` directory.
- The files in the directory are as follows. From here, the detail of each file is described.
  ```
  └─s2e-user 
    └─CMakeLists.txt  
    └─CMakeSetting.json  
    └─data  
      └─ini  
        └─initialize files
      └─logs
    └─src  
      └─Simulation
        └─Case
          └─UserCase.cpp
          └─UserCase.h
        └─Spacecraft
          └─UserComponents.cpp  
          └─UserComponents.h  
          └─UserSat.cpp  
          └─UserSat.h  
      └─S2eUser.cpp  
  ```
1. `CMakeLists.txt` and `CMakeSetting.json`
   - `CMakeLists.txt` is a [CMake file](https://cmake.org/) for a compile setting.
     - Details of description rules for CMake files can be searched on the internet, so please refer to them.
     - Of course, when you add new source files, you have to edit the CMake file to compile them.
   - `CMakeSetting.json ` is a compile setting file for Visual Studio.
2. `data/ini` and `data/logs`
   - In the `ini` directory, there are several initialize files.
     - The most important initialize file is `UserSimBase.ini`.
     - Other initialize files are defined in this base initialize file. So you need to edit the file names in the base file when you modify the name of other initialize files.
       - When you change the name of the base file, you have to edit `S2eUser.cpp`.
     - Details of the initialize files are described in `Specifications`.
       - Basic files are described in [Getting Started](./GettingStarted.md).
   - `logs`
     - CSV log files will be outputted here. The output directory is also defined in `UserSimBase.ini`, so that you can change it.
3. `src/S2eUser.cpp`
   - This is the main file of this program.
   - In this code, `UserSimBase.ini` is defined as the base file for the simulation, and an instance of the `simulation case class` named `UserCase` is created and initialized. And finally, the main routine of the class is executed.
4. `src/Simulation/Case`
   - `UserCase` class is defined here. `UserCase` class inherits the `SimulationCase` base class in the `s2e-core`. The `SimulationCase` class has a `SimulationConfig` and `GlobalEnvironment` class. The `UserCase` class has an instance of the `spacecraft` class named as `UserSat`.
5. `src/Simulation/Spacecraft/User_sat.cpp `
   - `UserSat` class is defined here. `UserSat` class inherits the `Spacecraft` class in the `s2e-core`. The `Spacecraft` base class has instances of `Dynamics`, `LocalEnvironment`, `Disturbance`, and `Structure`. And the `UserSat` class has an instance of `UserComponents`.
   - In the `UserSat`'s `Update` function, these four classes are updated to simulate the spacecraft behavior.
6. `src/Simulation/Spacecraft/UserComponents.cpp`
   - The `UserComponents` class is defined here. Most users edit this code to custom the S2E for their satellite projects.
   - Users select components they want to use from the `s2e-core/src/Component`.
   - You can add new source codes in the `s2e-user/Component` directory if you want to make original components.
