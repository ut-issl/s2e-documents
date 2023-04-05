# Specification documents for Simulation Configuration

## 1.  Overview

1. Functions
   - `SimulationConfiguration` is a structure for simulation setting parameters.
   - Parameters
     - Input/Output
       - initialize_base_file_name_
       - main_logger_
     - Spacecraft
       - number_of_simulated_spacecraft_
       - spacecraft_file_list_
     - Ground Station
       - number_of_simulated_ground_station_
       - ground_station_file_list_
     - Others
       - inter_sc_communication_file_
       - gnss_file_

2. Related files
   - `src/simulation/simulation_configuration.hpp`
     - The `SimulationConfiguration` structure is defined here.

3. How to use
   - The `SimulationConfiguration` is initialized in the beginning of the simulation case.
   - In other process, the `SimulationConfiguration` is used as read only to share the simulation setting parameters.

## 2. Explanation of Algorithm
NA

## 3. Results of verifications
NA

## 4. References
NA
