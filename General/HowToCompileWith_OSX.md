# How to compile with OSX Environment

## 1.  Overview

1. Functions

   - CMake can support multi-platform compiling
   
2. Related files

   - ./CmakeLists.txt

     - Base file for CMake

   - Other CMakeLists.txt in subdirectories

3. CLION
   - CLION is a cross-platform C and C++ IDE for Linux, MAC OS, and Windows integrated with the CMake build system. 
   - Could be downloaded from [here](https://www.jetbrains.com/ja-jp/clion/)
     - requires a toolbox subscription for normal users
     - Students and teacheres can get professional Jetbrain account for free 
       - https://blog.jetbrains.com/jp/2019/08/22/2105


## 2. Flow of compiling in CLION

1. Launch CLION. Select "Open" and select the directory where S2E_CORE_OSS, ExtLibraries, (FlightSW), and S2E_(project name) is included.

2. Open CMakeLists.txt you want to use in CLION. Load CMakeLists.txt file. 
   - CMakeFiles could be reloaded by selecting reloading botton at left side of the CMake tab in the bottom window. 

3. Build the CMake file

   - Build/Build Project
   - Apple Clang compiler in Xcode will be choosed as the default compiler. If you want to use other compilers, edit the following file. 
  ```
  S2E_(project name)/cmake-build-debug/out/S2E_CORE/CMakeCache.txt
  ```
   - Output files will be created in the following directory
  ```
  S2E_(project name)/cmake-build-debug/out
  ```

4. Check errors

5. Run the program (^R = control + R)

   - Users can use debug mode for debug. (Run/Debug or Control+Option+D)

6. Check log files

## 3. Note

1. In current version of the software (2020/6/6), set your cspice directory name as "cspoice_unix" in apple environment. See "HowToDownloadCSPICElibrary.md" for details. 
2. Apple uses clang in XCode as the default compiler. If you want to use the latest clang compiler instead of XCode, you have to be aware of conflicts between XCode clang and your local clang. See [here](https://students-tech.blog/post/install-clang.html#%E3%83%91%E3%82%B9%E3%82%92%E9%80%9A%E3%81%99)
   - you can check your current default compiler for c++ by the following command. 
```
C++ --version
```

## 4. Configured Environement
Build and run test was conducted in the following environment. 
- OS: macOS Catalina Version 10.15.5
- Compiler: Apple clang version 11.0.3 (clang-1103.0.32.62)
- SourceCode: 
  - S2E_CORE: e3e51448a3e6044fadb60ee6c6f63a81721f6533 ("OSXでのビルドが通る様に修正")
- Date: 2020/6/6