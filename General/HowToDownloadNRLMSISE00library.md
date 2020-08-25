# How to download and make NRLMSISE00 Library

## 1.  Overview

- [NRLMSISE00](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/info/intrdctn.html) is an atmosphere model to calculate an air density, considering the solar activity
- [C language version of NRLMSISE00](https://ccmc.gsfc.nasa.gov/pub/modelweb/atmospheric/msis/nrlmsise00/nrlmsis00_c_version/) is mandatory library for S2E. 
- How to use NRLMSISE00 is written in [Specification of Atomosphere model](../Specifications/Environment/Spec_Atomosphere.md)

## 2. How to set up NRLMSISE00 for S2E
  
1. Run `scripts/Common/download_nrlmsise00_src_and_table.sh`.
  + Source codes of NRLMISE00 and SpaceWeather.txt will be downloaded, and libnrlmsise00.a will be made for Linux and OSX.
  + If you use Windows, bash terminal for Windows (e.g. Git bash, WSL, MSYS) is needed to run this script.

2. If you use Windows, run `scripts/VisualStudio/make_nrlmsise00_VS32bit.bat` after 1.
  + VS command prompt will be launched, then run `scripts/VisualStudio/make_libnrlmsise.bat` in VS command prompt.
  + libnrlmise.lib which is the library for Windows will be made.

3. Check your directories are as follows.
<pre>   
  ├─ExtLibraries  
  │  └─nrlmsise00
  │      ├─table 
  |      |  └─SpaceWeather.txt
  │      ├─lib
  |      |  |─libnrlmsise00.a
  |      |  └─libnrlmsise00.lib
  │      └─src
  |         └─nrlmsise-00.h
  └─s2e_core  
</pre>  


