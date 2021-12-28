# How to download CSPICE Library

## 1.  Overview
- [SPICE](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/info/intrdctn.html) is a system to combine the most accurate space geometry and event data with space mission analysis, observation planning, or science data processing software developed by NASA.
- [CSPICE](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/index.html) is the C language version of SPICE and mandatory library for S2E to get planet information.

## 2. How to set up CSPICE Library for S2E
**Note**: Users can use the script file to automatically set up the following process in the `s2e-core/script` directory. If the script does not work, please see the following process.

- Make directories as follow
<pre>   
  ├─ExtLibraries  
  │  └─cspice  
  │      ├─cspice_xxx  
  │      │  └─lib  
  │      ├─generic_kernels  
  │      └─include  
  └─s2e-core  
</pre>  
  - xxx is depends on your compile environment
    - `xxx = msvs` for Microsoft Visual Studio
    - `xxx = cygwin` for Cygwin gCC
    - `xxx = unix` for Linux gCC
  
- Download library and compile
  - Download `cspice.zip` from [NAIF Toolkit](https://naif.jpl.nasa.gov/naif/toolkit_C.html), and unzip.
  - You need to choose a link suit with your compile environment
  - Copy `include` directory into `cspice` directory
  - Copy `lib` or `lib64` directory into `cspice_***` directory
    - VS 2019 users need to compile the library before copying the `lib`
      - launch following command prompt for VS2019 compile from the start menu of Windows
        - 32bit:  `x86 Native tools command prompt for VS2019` 
        - 64bit:  `x64 Native tools command prompt for VS2019` 
      - Move to the unzipped directory and execute `makeall.bat`

- Download kernel files
  - Download the following kernel files from [NAIF Generic Kernels](https://naif.jpl.nasa.gov/pub/naif/generic_kernels/), and copy them to the directories
    - Each kernel file can be updated for the latest one, but we have not confirmed it yet.
  <pre>         
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
  </pre>
**Note:** When you change the directory or file name, you should modify `s2e-core/CMakeLists` and `PlanetSelect.ini`

