# How To Use Monte Carlo Simulation

## 1.  Overview

- S2E has a framework to execute the Monte Carlo Simulation.
- The feature provides a framework to randomize arbitrary parameters in each class. 
- Users can set the mean value and standard deviation for the randomized parameters with `simulation_base.ini` file of each user.
  - Please see the specification document for [Monte Carlo Simulation](../Specifications/Simulation/Spec_MonteCarloSimulation.md) for a detailed description.
- This tutorial explains how to randomly change the initial value of the spacecraft angular velocity.
  - There are sample codes in [s2e-user-example/sample/how-to-use-monte-carlo-simulation](https://github.com/ut-issl/s2e-user-example/tree/sample/how-to-use-monte-carlo-simulation).
- The supported version of this document
  - Please confirm that the version of the documents and s2e-core is compatible.

## 2. Edit Simulation Case
- To use the Monte Carlo simulation, users have to edit their `user_case.hpp` and `user_case.cpp`
- `user_case.hpp`
  - Add header including
    ```c++
    #include <./simulation/monte_carlo_simulation/monte_carlo_simulation_executor.hpp>
    ```
  - Add private member variables for `MonteCarloSimulationExecutor`.
    ```c++
    MonteCarloSimulationExecutor &monte_carlo_simulator_;
    ```
  - Replace the constructor of UserCase class to add arguments for Monte Carlo simulation.
    ```c++
    UserCase(const std::string initialize_base_file, MonteCarloSimulationExecutor &monte_carlo_simulator, const std::string log_path);
    ```
- `user_case.cpp`
  - Add header including
    ```c++
    #include <./simulation/monte_carlo_simulation/simulation_object.hpp>
    ```
  - Replace the constructor as follows
    ```c++
    UserCase::UserCase(const std::string initialize_base_file, MonteCarloSimulationExecutor &monte_carlo_simulator, const std::string log_path)
    : SimulationCase(initialize_base_file, monte_carlo_simulator, log_path), monte_carlo_simulator_(monte_carlo_simulator) {}
    ```
  - Edit `InitializeTargetObjects` function
    - Edit log file name definition and       
    - Add `MonteCarloSimulationExecutor` initialization
      ```c++
      // Monte Carlo Simulation
      monte_carlo_simulator_.SetSeed();
      monte_carlo_simulator_.RandomizeAllParameters();
      SimulationObject::SetAllParameters(monte_carlo_simulator_);
      monte_carlo_simulator_.AtTheBeginningOfEachCase();
      ```  
  - Add log settings for the Monte Carlo simulation  
    - The `GetLogHeader` and `GetLogValue` functions are used for Monte Carlo log output.   
      - The log output defined in the function is executed at the beginning and end of a simulation case.  
      - The output line will be `2N+1`, where N is the sample number of the Monte Carlo simulation.
        - +1 line is for headers.
    - In this tutorial, time, angular velocity, and quaternion are logged.
      - Users can customize this output depending on their needs.
      ```c++
      std::string UserCase::GetLogHeader() const
      {
        std::string str_tmp = "";

        str_tmp += WriteScalar("elapsed_time", "s");
        str_tmp += WriteVector("spacecraft_angular_velocity", "b", "rad/s", 3);
        str_tmp += WriteVector("spacecraft_quaternion", "i2b", "-", 4);

        return str_tmp;
      }
      std::string UserCase::GetLogValue() const
      {
        std::string str_tmp = "";

        str_tmp += WriteScalar(global_environment_->GetSimulationTime().GetElapsedTime_s());
        str_tmp += WriteVector(spacecraft_->GetDynamics().GetAttitude().GetAngularVelocity_b_rad_s(), 3);
        str_tmp += WriteQuaternion(spacecraft_->GetDynamics().GetAttitude().GetQuaternion_i2b());

        return str_tmp;
      }
      ```

## 3. Edit `s2e_user.cpp` code
- To use the Monte Carlo Simulator, users have to edit their `s2e_user.cpp`
- Add header file
  ```c++
  #include <./simulation/monte_carlo_simulation/initialize_monte_carlo_simulation.hpp>
  ```
- If you find description below
  ```c++
  #include "library/logger/logger.hpp"
  ```
  rewrite as the following description 
  ```c++
  #include "library/logger/initialize_log.hpp"
  ```
- Make an instance of `MonteCarloSimulatorExecutor` and Logger for Monte Carlo log
  ```c++
  MonteCarloSimulationExecutor *mc_simulator = InitMonteCarloSimulation(ini_file);
  Logger *log_mc_sim = InitMonteCarloLog(ini_file, mc_simulator->IsEnabled());
  ```
- Add while loop for Monte Carlo simulation as follows
  ```c++
  while (mc_simulator->WillExecuteNextCase()) {
    auto simulation_case = UserCase(ini_file, *mc_simulator);
    // Initialize
    log_mc_simulator->AddLogList(&simulation_case);
    if (mc_simulator->GetNumberOfExecutionsDone() == 0) log_mc_simulator->WriteHeaders();
    simulation_case.Initialize();
    // Main
    log_mc_simulator->WriteValues();  // log initial value
    simulation_case.Main();
    mc_simulator->AtTheEndOfEachCase();
    log_mc_simulator->WriteValues();  // log final value
    log_mc_simulator->ClearLogList();
  }

  delete log_mc_simulator;
  delete mc_simulator;
  ```

## 4. Initialize file for Monte Carlo simulator

- Edit `user_simulation_base.ini` to add the following description
  ```c++
  [MONTE_CARLO_EXECUTION]
  // Whether Monte-Carlo Simulation is executed or not
  monte_carlo_enable = ENABLE

  // Whether you want output the log file for each step
  log_enable = ENABLE

  // Number of execution
  number_of_executions = 3

  [MONTE_CARLO_RANDOMIZATION]
  parameter(0) = attitude0.angular_velocity_b_rad_s
  attitude0.angular_velocity_b_rad_s.randomization_type = CartesianUniform
  attitude0.angular_velocity_b_rad_s.mean_or_min(0) = 0.0
  attitude0.angular_velocity_b_rad_s.mean_or_min(1) = 0.0
  attitude0.angular_velocity_b_rad_s.mean_or_min(2) = 0.0
  attitude0.angular_velocity_b_rad_s.sigma_or_max(0) = 0.05817764 // 3-sigma = 10 [deg/s]
  attitude0.angular_velocity_b_rad_s.sigma_or_max(1) = 0.05817764 // 3-sigma = 10 [deg/s]
  attitude0.angular_velocity_b_rad_s.sigma_or_max(2) = 0.05817764 // 3-sigma = 10 [deg/s]
  ```
- You can set the following parameters
  - `monte_carlo_enable`:
    - `ENABLE`: S2E executes the Monte Carlo Simulation.
    - `DISABLE`: S2E executes a simulation case defined in ini files.  
  - `log_enable`:
    - `ENABLE`: A default csv log file is outputted for each sample case.
      - **Note**: 100 csv files will be generated when you set `number_of_executions = 100`.
    - `DISABLE`:  No default csv log file will be generated. Only a `monte_carlo csv log` file will be generated.
      - **Note**: When `monte_carlo_enable = DISABLE`, a default csv log file will always be generated.
  - `number_of_executions`: integer lager than 1
    - The total calculation time is proportional to this value.
  
- Randomized parameters
  - randomization_type: You can choose the randomization type. See [Monte Carlo Simulation](../Specifications/Simulation/Spec_MonteCarloSimulation.md) for detail.
  - `mean_or_min`: Input mean value or minimum value. (Depends on Randomization type)
  - `sigma_or_max`: Input standard deviation or maximum value. (Depends on Randomization type)

## 6. Execute and check logs

- Build the `S2E_USER` and execute it.
- In the `data` directory, you can find one `xxxx_monte_carlo.csv` file and several `xxxx_default.csv` files, which depend on your Monte Carlo Simulator setting.
- The initial value of angular velocity is randomly varied by the Monte Carlo Simulator.

