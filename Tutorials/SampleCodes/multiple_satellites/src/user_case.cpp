/**
 * @file user_case.cpp
 * @brief Example of user defined simulation case
 */

#include "user_case.hpp"

UserCase::UserCase(const std::string initialise_base_file) : SimulationCase(initialise_base_file) {}

UserCase::~UserCase() {
  delete spacecraft0_;
  delete spacecraft1_;
}

void UserCase::InitializeTargetObjects() {
  // Instantiate the target of the simulation
  // `spacecraft_id` corresponds to the index of `spacecraft_file` in simulation_base.ini
  spacecraft0_ = new UserSatellite(&simulation_configuration_, global_environment_, 0);
  spacecraft1_ = new UserSatellite(&simulation_configuration_, global_environment_, 1);

  // Register the log output
  spacecraft0_->LogSetup(*(simulation_configuration_.main_logger_));
  spacecraft1_->LogSetup(*(simulation_configuration_.main_logger_));
}

void UserCase::UpdateTargetObjects() {
  // Spacecraft Update
  spacecraft0_->Update(&(global_environment_->GetSimulationTime()));
  spacecraft1_->Update(&(global_environment_->GetSimulationTime()));
}

std::string UserCase::GetLogHeader() const {
  std::string str_tmp = "";
  return str_tmp;
}

std::string UserCase::GetLogValue() const {
  std::string str_tmp = "";

  return str_tmp;
}
