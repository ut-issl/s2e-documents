/**
 * @file user_case.cpp
 * @brief Example of user defined simulation case
 */

#include "user_case.hpp"

UserCase::UserCase(const std::string initialise_base_file) : SimulationCase(initialise_base_file) {}

UserCase::~UserCase() { delete spacecraft_; }

void UserCase::InitializeTargetObjects() {
  // Instantiate the target of the simulation
  // `spacecraft_id` corresponds to the index of `spacecraft_file` in simulation_base.ini
  const int spacecraft_id = 0;
  spacecraft_ = new UserSatellite(&simulation_configuration_, global_environment_, spacecraft_id);

  // Register the log output
  spacecraft_->LogSetup(*(simulation_configuration_.main_logger_));
}

void UserCase::UpdateTargetObjects() {
  // Spacecraft Update
  spacecraft_->Update(&(global_environment_->GetSimulationTime()));
}

std::string UserCase::GetLogHeader() const {
  std::string str_tmp = "";
  return str_tmp;
}

std::string UserCase::GetLogValue() const {
  std::string str_tmp = "";

  return str_tmp;
}
