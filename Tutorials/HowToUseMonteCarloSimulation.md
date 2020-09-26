# How To Use Monte Carlo Simulation

## 1.  Overview

- S2E has a framework to execute the Monte Carlo Simulation, and it is called `MCSim`.
- MCSim provides a framework to randomize arbitrary parameters in each class. 
- Users can set the mean value and standard deviation for the randomized parameters with `MCSim.ini` file
  - Please see the specification document for [MCSim](../Specifications/Simulation/Spec_MonteCarloSimulation.md) for a detailed description 
- This tutorial explains how to randomly change the initial value of the angular velocity.
  - There are sample codes in `SampleCodes\MCSim`.
- Supported version of this document
  - S2E_CORE_OSS:c4c7cf6567c077f0918f07a9a82c2d7e4531ceb7

## 2. Edit Simulation Case
- To use the MCSim, users have to edit their `User_case.h` and `User_case.cpp`
- `User_case.h`
  - Add header including
    ```c++
    #include "MCSimExecutor.h"
    ```
  - Add private member variables for MCSimExecutor and string
    ```c++
    MCSimExecutor& mc_sim_;
    ```
  - Replace the constructor of UserCase class to add arguments
    ```c++
    UserCase(string ini_fname, MCSimExecutor& mc_sim, const string log_path);
    ```
- `User_case.cpp`
  - Add header including
    ```c++
    #include "SimulationObject.h"
    ```
  - Replace the constructor as follows
    ```c++
    UserCase::UserCase(string ini_fname, MCSimExecutor& mc_sim, const string log_path)
    : SimulationCase(ini_fname,mc_sim,log_path),mc_sim_(mc_sim)
    {
    }
    ```
  - Edit `Initialize` function
    - Edit log file name definition and       
    - Add MCSim initialization
      ```c++
        //Monte Carlo Simulation
        mc_sim_.SetSeed();
        mc_sim_.RandomizeAllParameters();
        SimulationObject::SetAllParameters(mc_sim_);
        mc_sim_.AtTheBeginningOfEachCase();
      ```  
  - Edit `Main` function
    - Add MC finish process at the end of the function
      ```c++
      mc_sim_.AtTheEndOfEachCase();
      ```
  - Add log settings for the Monte Carlo simulation  
    - The `GetLogHeader` and `GetLogValue` functions are used for Monte Carlo log output.   
      - The log output defined in the function is executed at the beginning and end of a simulation case.  
      - The output line will be `2N+1`, where N is the sample number of the Monte Carlo simulation.
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
        str_tmp += WriteScalar(glo_env_->GetSimTime().GetElapsedSec());
        str_tmp += WriteVector(spacecraft_->GetDynamics().GetAttitude().GetOmega_b(), 3);
        str_tmp += WriteQuaternion(spacecraft_->GetDynamics().GetAttitude().GetQuaternion_i2b());
        return str_tmp;
      }
      ```

## 3. Edit `S2E_USER` code
- To use the MCSim, users have to edit their `S2E_USER.cpp`
- Add header file
  ```c++
  #include "MCSimExecutor.h"
  ```
- Make an instance of MCSimExecutor and Logger for MC log
  ```c++
  MCSimExecutor* mc_sim = InitMCSim(ini_file);
  Logger *log_mc_sim = InitLogMC(ini_file,mc_sim->IsEnabled());
  ```
- Add while loop for Monte Carlo simulation as follows
  ```c++
  while (mc_sim->WillExecuteNextCase())
  {
    auto simcase = UserCase(ini_file, *mc_sim, log_mc_sim->GetLogPath());
    // Initialize
    log_mc_sim->AddLoggable(&simcase);
    if (mc_sim->GetNumOfExecutionsDone() == 0) log_mc_sim->WriteHeaders();
    simcase.Initialize();
    //Main
    log_mc_sim->WriteValues(); //log initial value
    simcase.Main();
    log_mc_sim->WriteValues(); //log final value
    log_mc_sim->ClearLoggables();
  }
  ```

## 4. Initialize file for MCSim

- Edit `User_SimBase.ini` to add the following description
  ```c++
  [MC_EXECUTION]
  //ENABLED or DISABLED
  MCSimEnabled = ENABLED
  //When LogHistory=ENABLED, a default csv log file is outputted for each sample case.
  //ENABLED or DISABLED
  LogHistory = ENABLED
  //Note: When MCSimEnabled=ENABLED, a default csv log file will be always generated.
  //Number of Monte Carlo executions
  //The total calculation time is proportional with this value
  NumOfExecutions = 5
  [MC_RANDOMIZATION]
  Param(0) = ATTITUDE0.Omega_b
  ATTITUDE0.Omega_b.randomization_type = CartesianUniform
  ATTITUDE0.Omega_b.mean_or_min(0) = 0.0
  ATTITUDE0.Omega_b.mean_or_min(1) = 0.0
  ATTITUDE0.Omega_b.mean_or_min(2) = 0.0
  ATTITUDE0.Omega_b.sigma_or_max(0) = 0.05
  ATTITUDE0.Omega_b.sigma_or_max(1) = 0.05
  ATTITUDE0.Omega_b.sigma_or_max(2) = 0.05
  ```
- You can set the following parameters
  - MCSimEnabled: ENABLED or DISABLED
    - `ENABLED`: S2E executes the Monte Carlo Simulation.
    - `DISABLED`: S2E executes a simulation case defined in ini files.  
  - LogHistory: ENABLED or DISABLED
    - `ENABLED`: A default csv log file is outputted for each sample case.
      - **Note**: 100 csv files will be generated when you set `NumOfExecutions=100`.
    - `DISABLED`:  No default csv log file will be generated. Only a `mont csv log` file will be generated.
      - **Note**: When `MCSimEnabled=ENABLED`, a default csv log file will be always generated.
  - NumOfExecutions: integer lager than 1
    - The total calculation time is proportional to this value.
  
- Randomized parameters
  - randomization_type: You can choose the randomization type. See [MCSim](../Specifications/Simulation/Spec_MonteCarloSimulation.md) for detail.
  - mean_or_min: Input mean value or minimum value. (Depends on Randomization type)
  - sigma_or_max: Input standard deviation or maximum value. (Depends on Randomization type)

## 6. Execute and check logs

- Build the S2E_USER and execute it.
- In the `data` directory, you can find one `xxxx_mont.csv` file and several `xxxx_default.csv` files, which depend on your MCSim setting.
- The initial value of angular velocity is randomly varied by the MCSim.

