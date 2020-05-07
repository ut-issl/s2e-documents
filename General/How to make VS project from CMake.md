# How to make VS project from CMake

## 1.  Overview

1. Functions

   - CMake can support multi-platform compiling
   
2. Related files

   - ./CmakeLists.txt

     - Base file for CMake
   - ./CMakeSettings.json
     - Setting file for VS to use CMake
   - Other CMakeLists.txt in subdirectories


## 2. Flow of compiling in VS

1. Launch VS 2017

2. Select CMakeLists.txt you want to use

   - Files/Open/CMake

3. Build the CMake file

   - CMake/Build All

   ![](./figs/CMake_build.jpg)

4. Check errors

5. Run the program

   - Users can use break point similar with normal sln file based projects.

   ![](./figs/CMake_run.jpg)

6. Check log files

