# How to download CSPICE Library

## 1.  Overview

- [SPICE](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/info/intrdctn.html) is a system to combine the most accurate space geometry and event data with your mission analysis, observation planning or science data processing software developed by NASA.
- [CSPICE](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/index.html) is C language version of SPICE and mandatory library for S2E to get planet information. 


## 2. How to set up CSPICE Library for S2E


- Make directories as follow

  ├─ExtLibraries  
  │  └─cspice  
  │      ├─cspice_xxx  
  │      │  └─lib  
  │      ├─generic_kernels  
  │      └─include  
  └─s2e_core  
  
  - xxx is depends on your compile environment
    - xxx = msvs for Microsoft Visual Studio
    - xxx = cygwin for Cygwin gCC
    - xxx = unix for Linux gCC
  
- Download library and compile

    - Download `cspice.zip` from [NAIF Toolkit](https://naif.jpl.nasa.gov/naif/toolkit_C.html), and unzip.
    - You can chose several link to suit with your compile environment
    - Copy `include` directory into `cspice` directory
    - Copy l`lib` or `lib64` directory into `cspice_***` directory
        - VS 2017 users need to compile the library before copy the `lib`
            - launch following command prompt for VS2017 compile from start menu of Windows
                - 32bit:  `x86 Native tools command prompt for VS2017` 
                - 64bit:  `x64 Native tools command prompt for VS2017` 
            - Move to unzipped directory and execute `makeall.bat`

- Download kernel files

    - Download following kernel files from [NAIF Generic Kernels](https://naif.jpl.nasa.gov/pub/naif/generic_kernels/), and copy it to the directories

        - Each kernel files can be updated for latest one, but we didn't confirm yet.
        
        ├─generic_kernels  
        │  ├─lsk  
        │      └─naif0010.tls  
        │  ├─pck  
        │      └─de-403-masses.tpc  
        │      └─gm_de431.tpc  
        │      └─pck00010.tpc  
        │  └─spk  
        │      └─planets  
        │  │      └─de430.bsp  

**Note:** When you change the directory or file name, you should modify `S2E_CORE/CMakeLists` and `PlanetSelect.ini`

