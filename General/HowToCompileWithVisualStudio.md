# How to compile with Visual Studio

## 1.  Overview
This document explains how to build and execute the Visual Studio environment with CMake. Currently, we recommend using `VS2022`, but users can use `VS2019` and `VS2017` with minor modifications.

- Related files
  - ./CmakeLists.txt
    - Base file for CMake
  - ./CMakeSettings.json
    - Setting file for VS to use CMake
  - Other CMakeLists.txt in subdirectories

## 2. Environment Construction of Visual Studio
- Install [Visual Studio Community 2022](https://visualstudio.microsoft.com/free-developer-offers/)
  - Select the following `Workloads`
    - `Desktop development with C++`
- Check the `ExtLibraries` directory is in **the same directory** with the `s2e-core` like below.
  <pre>
  ├─ExtLibraries
  └─s2e-core
  </pre>
  - If not the following procedure should be done to make `ExtLibraries`
    - Launch VS 2022
    - Open the CMake file for the `ExtLibraries`
      - Click `Files/Open/CMake`.
      - Select the following `s2e-core/ExtLibraries/CMakeLists.txt`.
        <pre>
        └─s2e-core
           └─ExtLibraries
              └─CMakeLists.txt
        </pre>
      - Wait a moment until the `CMake generation` is finished.
    - Install the `ExtLibraries`
      - Select `CMakeLists.txt` with right-clicking in the VS's `Solution Explorer`.
      - Click `Install` command.
      - Wait a moment untile the installe is successfully finished.
    - Check the `ExtLibraries` directory is in **the same directory** with the `s2e-core`, and there are `cspice` and `nrlmsise00` directories in the `ExtLibraries` like below.
      <pre>
      ├─ExtLibraries
      │  └─cspice
      │  └─nrlmsise00 
      └─s2e-core
      </pre>

## 3. The flow of building and execution in Visual Studio 2022
1. Launch VS 2022

2. Open the S2E project
   - Click `Files/Open/CMake`.
   - Select `s2e-core/CMakeLists.txt` at the top directory of the cloned S2E.
   - Wait a moment until the `CMake generation` is finished.

3. Build the S2E
   - Select `CMakeLists.txt` with right-clicking in the VS's `Solution Explorer`.
   - Click `Build` command.
   - Wait a moment untile the build is successfully finished.

4. Check errors
   - When users edit the codes, please check the error and fix them.

5. Run the program
   - Select `S2E.exe` like the red circle of the following figure.
     ![](./figs/CMake_run.png)
   - Click the `green play button` in the red circle to run the S2E.
   - A console window is opened, and uses can see the S2E's running status.

6. Check log files
   - Open the `./data/***/logs/logs_***` directory.
   - Open the CSV file to check the log output of the S2E.

## 4. Note
- For VS2019 users
  - Please edit compiler setting in `CMakeSetting.json` as `"generator": "Visual Studio 16 2019"`.
- For VS2017 users
  - Please edit compiler setting in `CMakeSetting.json` as `"generator": "Visual Studio 15 2017"`.
  - You also need to edit the `cmake_minimum_required` version from 3.13 to 3.10 in all CMakeList, including the files in subdirectories. The VS 2017 does not support version 3.13, and you may see many `warnings` when you use CMake Version 3.10. 
