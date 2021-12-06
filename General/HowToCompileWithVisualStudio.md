# How to compile with Visual Studio

## 1.  Overview
This document explains how to build and execute the Visual Studio environment with CMake. Currently, we recommend using VS2019, but users can use VS2017 with minor modifications.

- Related files
  - ./CmakeLists.txt
    - Base file for CMake
  - ./CMakeSettings.json
    - Setting file for VS to use CMake
  - Other CMakeLists.txt in subdirectories

## 2. The flow of building and execution in Visual Studio
1. Launch VS 2019

2. Select `./CMakeLists.txt` for the S2E
   - Files/Open/CMake

3. Build the CMake file
   - Select `CMakeLists.txt` with right-clicking, and build

4. Check errors

5. Run the program
   - Users can use a `breakpoint` similar to normal `sln` file based projects.
   ![](./figs/CMake_run.jpg)

6. Check log files

## 3. Note
- For VS2017 users
  - Please edit compiler setting in `CMakeSetting.json` as `"generator": "Visual Studio 15 2017"`.
  - You also need to edit the `cmake_minimum_required` version from 3.13 to 3.10 in all CMakeList, including the files in subdirectories. The VS 2017 does not support version 3.13, and you may see many `warnings` when you use CMake Version 3.10. 

