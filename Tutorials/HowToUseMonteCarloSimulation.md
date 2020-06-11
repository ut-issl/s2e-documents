# How To Use Monte Carlo Simulation

## 1.  Overview

- S2E has a feature to execute Monte Carlo Simulation (MCSim)
- This tutorial explains how to use it.

## 2. Edit CMakeList.txt

- Add following description to add new include directory to access header files for the MCSim

  `include_directories(${S2E_CORE_DIR}/src/Simulation/MCSim)`

## 3. Edit Simulation Case

- To use the MCSim, uses have to edit their `user_case.h` and `user_case.cpp`

- `user_case.h`

  - Add header including

    `#include "MCSimExecutor.h"`

  - Add a private member variable of MCSimExecutor

    `MCSimExecutor& mc_sim_;`

  - Add an argument in constructor for MCSimExecutor

    `UserCase(string ini_fname, MCSimExecutor& mc_sim, string log_path);`

- `user_case.cpp`

  - Add header including

    `#include "SimulationObject.h"`
    
  - Add the new constructor
  
    ```c++
    ISSL6UCase::ISSL6UCase(string ini_fname, MCSimExecutor& mc_sim, string log_path)
    : ini_fname(ini_fname),mc_sim_(mc_sim), log_path_(log_path)
    {
  }
    ```

  - Edit Initialize function
  
    - Edit log file name definition and 
  
      ```c++
    string fname = "default" + to_string(mc_sim_.GetNumOfExecutionsDone()) + ".csv";
      default_log = new Logger(fname, log_path_, ini_fname_, false, mc_sim_.LogHistory());
    Logger& log  = *default_log;
      ```
      
    - Add MCSim initialization
  
      ```c++
       //Monte Carlo Simulation
        mc_sim_.SetSeed();
        mc_sim_.RandomizeAllParameters();
        SimulationObject::SetAllParameters(mc_sim_);
        mc_sim_.AtTheBeginningOfEachCase();
      ```
  
  - Edit Main function
  
    - Add MC finish process
  
      `mc_sim_.AtTheEndOfEachCase();`
  
  - Add log for Monte Carlo settings
  
    - The `GetLogHeader` and `GetLogValue` functions are used for Monte Carlo log output
    - 



## 4. Edit the main code

- To use the MCSim, uses have to edit their `S2E_user.cpp`

- Please copy the 

- Make an instance of MCSimExecutor

  - Add following codes in the main function

    `MCSimExecutor* mc_sim = InitMCSim("data/ini/MCsim.ini");`

- Make an instance of Logger to output a log file for MCSim

  - Add following codes in the main function

    `Logger *log_mc_sim = InitLogMC(ini_file);`

- Describe as follows

  ```c++
    while (mc_sim->WillExecuteNextCase())
    {
      auto simcase = ISSL6UCase(ini_file, *mc_sim, log_mc_sim->GetLogPath());
      // Initialize
      log_mc_sim->AddLoggable(&simcase);
      if (mc_sim->GetNumOfExecutionsDone() == 0) log_mc_sim->WriteHeaders();
      simcase.Initialize();
  
      //Main
      log_mc_sim->WriteValues(); //write initial value
      simcase.Main();
      log_mc_sim->WriteValues(); //write final value
      log_mc_sim->ClearLoggables();
    }
  ```

  

- 

## 5. Ini file for MCSim

- Copy `MCSim.ini`