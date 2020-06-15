# How To Use Monte Carlo Simulation

## 1.  Overview

- S2E has a framework to execute Monte Carlo Simulation, and it is called MCSim.

- MCSim provides a framework to randomize arbitrary parameters in each class. 

- By using the framework, users can set the mean value and standard deviation for the randomized parameters with `MCSim.ini` file

  - Please see specification document for [MCSim](../Specifications/Simulation/Spec_MonteCarloSimulation.md) for detailed description 

- This tutorial explains how to randomly change the initial value of the angular velocity.

  - There are sample codes in `SampleCodes\MCSim`.

## 2. Edit CMakeList.txt

- Add following description to add new include directory to access header files for the MCSim

  - At line 45 in the sample codes.
  
  `include_directories(${S2E_CORE_DIR}/src/Simulation/MCSim)`

## 3. Edit Simulation Case

- To use the MCSim, uses have to edit their `user_case.h` and `user_case.cpp`

- `user_case.h`

  - Add header including

    `#include "MCSimExecutor.h"`

  - Add private member variables for MCSimExecutor and string

    ```c++
      MCSimExecutor& mc_sim_;
      string log_path_;
    ```

  - Replace the constructor of UserCase class to add arguments

    `UserCase(string ini_fname, MCSimExecutor& mc_sim, string log_path);`

- `user_case.cpp`

  - Add header including

    `#include "SimulationObject.h"`
    
  - Add the new constructor
  
    ```c++
    UserCase::UserCase(string ini_fname, MCSimExecutor& mc_sim, string log_path)
    :ini_fname(ini_fname), mc_sim_(mc_sim), log_path_(log_path)
    {
  }
    ```

  - Edit Initialize function
  
    - Edit log file name definition and 
  
      - At line 22-24 in the sample codes.
    
      ```c++
      string log_file_name = "default" + to_string(mc_sim_.GetNumOfExecutionsDone()) + ".csv";
        default_log = new Logger(log_file_name, log_path_, ini_fname, false, mc_sim_.LogHistory());
        SimulationConfig config = {ini_fname, sim_time, default_log};  //config
      ```
      
    - Add MCSim initialization
  
      - At line 29-33 in the sample codes.
  
      ```c++
        //Monte Carlo Simulation
        mc_sim_.SetSeed();
        mc_sim_.RandomizeAllParameters();
        SimulationObject::SetAllParameters(mc_sim_);
        mc_sim_.AtTheBeginningOfEachCase();
      ```
  
  - Edit Main function
  
    - Add MC finish process at the end of the function
  
      - At line 65 in the sample codes.
  
      `mc_sim_.AtTheEndOfEachCase();`
  
  - Add log settings for the Monte Carlo simulation
  
    - The `GetLogHeader` and `GetLogValue` functions are used for Monte Carlo log output. 
  
      - The log output defined in the function is executed at the beginning and ending of a simulation case.  
      - The output line will be `2N+1`, where N is sample number of the Monte Carlo simulation.
        - +1 line is for headers.
  
    - In this tutorial, time, angular velocity, and quaternion are logged.
  
      - Users can customize this output depends on their needs.
      
      ```c++
      string UserCase::GetLogHeader() const
      {
        string str_tmp = "";
        str_tmp += WriteScalar("time", "s");
        str_tmp += WriteVector("Omega", "b", "rad/s", 3);
        str_tmp += WriteVector("quat", "i2b", "-", 4);
      
        return str_tmp;
      }
      
      string UserCase::GetLogValue() const
      {
        string str_tmp = "";
        str_tmp += WriteScalar(sim_time->GetElapsedSec());
        str_tmp += WriteVector(spacecraft->dynamics_->GetAttitude().GetOmega_b(), 3);
        str_tmp += WriteQuaternion(spacecraft->dynamics_->GetAttitude().GetQuaternion_i2b());
        return str_tmp;
      }
      ```

## 4. Edit the main code

- To use the MCSim, uses have to edit their `S2E_user.cpp`

- Make an instance of MCSimExecutor

  - At line 38-41 in the sample codes.

    ```c++
      IniAccess iniAccess = IniAccess(ini_file);
      const string mc_file_path = iniAccess.ReadString("SIM_SETTING", "mcsim_file");
      MCSimExecutor* mc_sim = InitMCSim(mc_file_path);
      Logger *log_mc_sim = InitLogMC(ini_file,mc_sim->IsEnabled());
    ```
    
    

- Make an instance of Logger to output a log file for MCSim

  - At line 41 in the sample codes.

    `Logger *log_mc_sim = InitLogMC(ini_file);`

- Describe as follows

  - At line 46-59 in the sample codes.

  ```c++
    while (mc_sim->WillExecuteNextCase())
    {
      auto simcase = UserCase(ini_file, *mc_sim, log_mc_sim->GetLogPath());
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

## 5. Initiarize file for MCSim

- Edit `User_SimBase.ini` to add following description in [SIM_SETTING] region

  ```c++
  mcsim_file	   = ../../data/ini/User_MCSim.ini
  ```

- Copy `User_MCSim.ini` in the sample code directory to your `data/ini` directory

- In the ini file, you can set following parameters
  - MCSimEnabled: ENABLED or DISABLED
    - `ENABLED`: S2E executes the Monte Carlo Simulation.
    - `DISABLED`: S2E executes a simulation case defined in ini files.  
  - LogHistory: ENABLED or DISABLED
    - `ENABLED`: A default csv log file is outputted for each sample case.
      - **Note**: 100 csv files will be generated when you set `NumOfExecutions=100`.
    - `DISABLED`:  No default csv log file will be generated. Only a mont csv log file will be generated.
      - **Note**: When `MCSimEnabled=ENABLED`, a default csv log file will be always generated.
  - NumOfExecutions: integer lager than 1
    - The total calculation time is proportional with this value.
  
- Randomized parameters
  - randomization_type: You can chose randomization type. See [MCSim](../Specifications/Simulation/Spec_MonteCarloSimulation.md) for detail.
  - mean_or_min: Input mean value or minimum value. (Depends on Randomization type)
  - sigma_or_max: Input standard deviation or maximum value. (Depends on Randomization type)

## 6. Execute and check logs

- Build the S2E_USER and execute it.
- In `data` directory, you can find one `xxxx_mont.csv` file and several `xxxx_default.csv` files, which is depends on your MCSim setting.
- The initial value of angular velocity is randomly varied by the MCSim.

