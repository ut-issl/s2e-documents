# How to download and make NRLMSISE00 Library

## 1.  Overview
- [NRLMSISE00](https://agupubs.onlinelibrary.wiley.com/doi/full/10.1029/2002JA009430) is an atmosphere model to calculate an air density, considering the solar activity.
- [C language version of NRLMSISE00](https://git.linta.de/?p=~brodo/nrlmsise-00.git;a=summary) is a mandatory library for S2E to calculate the atmosphere density around the Earth.
- How to use NRLMSISE00 is written in the [Specification of Atmosphere model](../Specifications/Environment/Spec_Atmosphere.md).
- **Note** The [s2e-core v5.0.0](https://github.com/ut-issl/s2e-core/releases/tag/v5.0.0) provides the CMake file to download and install the external libraries, and we recommend to use it since it is simpler. So users do not need to execute the following process.


## 2. How to set up NRLMSISE00 for S2E [OLD Descriptions]
1. In any environment, run `s2e-core/scripts/Common/download_nrlmsise00_src_and_table.sh`
   + Source codes of NRLMISE00 and `SpaceWeather.txt` will be downloaded, and `libnrlmsise00.a` will be made for Linux and OSX.
     + Users have to compile the codes using the same compiler with S2E. After these codes are downloaded, you can directly compile them by using makefile in the `ExtLibraries\nrlmsise00\src`.
   + If you use Windows, a bash terminal for Windows (e.g. Git bash, WSL, MSYS) is needed to run this script, and you need to run an additional script. Proceed to Step 2.


2. For Windows Visual Studio users, run `s2e-core/scripts/VisualStudio/make_nrlmsise00_VS32bit.bat` after the process 1.
   + VS command prompt will be launched, then run `scripts/VisualStudio/make_libnrlmsise.bat` in VS command prompt.
   + `libnrlmise.lib`, which is the library for Windows Visual Studio will be made.
   + At the end of the procedure, you may see "指定されたバッチ ラベルが見つかりません - END". If there is `libnrlmsise00.lib` in the right place and all the files are in the right place, you may ignore this message.

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
  └─s2e-core  
</pre>  
