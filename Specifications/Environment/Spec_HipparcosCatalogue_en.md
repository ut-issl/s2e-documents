# Specification for Hipparcos catalogue

## 1.  Overview
- This class read the csv file of Hipparcos catalogue and to enable other classes to use the data.
- Specify the max visual magnitude to read in `Environment.ini`
  1. functions
     + `ReadContents`
       * Function to read `hip_main.csv`
     +  `Get` functions
        * Functions to access the data of `HipparcosCatalogue` from outside of this class

  2. files
     + `HipparcosCatalogue.cpp` ，`HipparcosCatalogue.h`
       * Definitions and declarations of the class
     + `Init_HipCatalogue.cpp`
       * Interface functions for the initialization
     + `Environment.ini`
       * Parameters for initialization
     + `hip_main.csv`
       * This is the original data of the Hipparcos catalogue. It is in the `ExtLibraries` directory. This data is sorted in of the visual magnitude, not in the order of HIP ID.

  3. How to download `hip_main.csv`
     + `s2e-core/scripts/download_HIPcatalogue.sh` is the script to download it. Run the following code using Git bash in `s2e-core/scripts/`．
       * **NOTE for Mac OS users: Run the following script not from the Mac terminal but the Ubuntu terminal in Docker.** (Because the specification of `sed` is different between Mac and Linux, the file cannot be generated correctly. Reference: <https://qiita.com/catfist/items/1156ae0c7875f61417ee>) 
      ```
       bash download_HIPcatalogue.sh 
       ```
    
  4. How to use
     + Set the parameters in `Environment.ini`
     + Create an instance by using initialization function `InitHipCatalogue`
     + Run `GetContents` to read the csv file
     + Get the data from outside this class using `Get` functions.
     + The `HipData` structure has four elements, hip_num(HIP ID), vmag(visual magnitude), ra(right ascension), de(declination). `HipparcosCatalogue` stores the data as a vector of `HipData`.

## 2. Explanation of Algorithm
TBW

## 3. Result of verification
The verification using this class is conducted in `Spec_Telescope.md`.



