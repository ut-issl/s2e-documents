# Specification for GNSS

## 1. Overview
### 1. function
- A class to read data about orbit and clock bias of GNSS satellites such as .sp3 and .clk_30s and use them in other classes.
- Determine the file name of GNSS satellites' data and time from `[GNSS_SATELLITES]` in `sample_gnss.ini`.

### 2. Related files
- `src/environment/global/globalEnvironment.cpp, .hpp`
  - GnssSatellites class is defined. Various GET functions are also implemented.
- `src/environment/global/initialize_gnss_satellites.cpp, .hpp`
  - This makes the instance of the GnssSatellites class. The initialization is described in the `sample_gnss.ini` file. 
- `ExtLibraries/sp3`
  - It contains a set of files (.sp3, .clk_30s) necessary for generating orbits and clock biases.

### 3. About downloading .sp3 files, etc.
- The author has not yet written script files to download .sp3 or .clk. Users can download them from `ftp://igs.ensg.ign.fr/pub/igs/products/`, `http://mgmds01.tksc.jaxa.jp/`, etc., referring to the directory classification. The directories are assumed to be as follows.
```
ExtLibraries  
    |  
   sp3  
    ├── CODE  
    │   └── final  
    ├── IGS  
    │   ├── igl    
    │   ├── igr
    │   │   └── clk
    │   ├── igs  
    │   │   └── clk_30s
    │   └── igu
    ├── JAXA
    │   ├── final
    │   ├── madoca
    │   ├── rapid
    │   └── ultra_rapid
    └── QZSS
        ├── final
        ├── rapid
        └── ultra_rapid
```

## 2. How to use
- Parameters, which file to use or else are set in `sample_gnss.ini`
    - `directory_path`: fixed
    - `calculation`: whether to use this GNSS class
    - `true_position_file_sort`: Select the type of file to generate the true value of the GNSS satellite coordinates.
    - `true_position_first`: The first file to read
    - `true_position_last`: The last file to read
    - `true_position_interpolation_method`: Select the interpolation method
    - `true_position_interpolation_number`: Select the number of points to be interpolated, so the order of the function will be `true_position_interpolation_number` -1.
    - `true_clock_file_extension`: Whether to use .sp3 or clock-only files such as .clk_30s  

  `estimation` parameters are the same as above.

- Users can retrieve the coordinates and clock bias of each GNSS satellite with the provided `Get` functions.  

## 3. Algorithm
Basically, the trajectory is generated by interpolation, but some data are often missing, so we have dealt with it. For the coordinates, the trajectory is generated by interpolation from the available coordinates, and for the clock bias is generated by extracting only the strictly surrounding values. 

1. Extract the contents of the file with `initialize_gnss_satellites.cpp`.
2. Create a table for generating coordinates and clock bias with `Init()`.
    - `time_table_`: The Unix Time of all times are listed.
    - `gnss_*_table_*`: Contains the coordinates or clock bias values at all times.
    - `available_table_`: Whether available of the data of all satellites at all times
    - `time_and_index_list_`: Contains the pair of available time and the index in the table. 
3. `SetUp()`: Set the first interpolation reference location from `time_table_` and `time_and_index_list_`, set the index of the reference to `nearest_index_` (used later in Update). `time_vector_`, `ecef_`, `eci_`, `clock_` are `std::vector` used for interpolation calculation.
4. `Update()`: Coordinates and clock bias are calculated based on the time. The `time_vector_`, `ecef_`, `eci_`, and `clock_`, which are used as the basis of interpolation, are updated according to the nearest time.

## 4. Result and Specification
Some of the calculated ECI coordinates are shown below.

<img src="./figs/result_gnss.png" style = "zoom: 75%">

