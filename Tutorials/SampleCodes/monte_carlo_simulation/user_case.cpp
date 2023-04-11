/**
 * @file user_case.cpp
 * @brief Example of user defined simulation case
 */

#include "user_case.hpp"

#include <./simulation/monte_carlo_simulation/simulation_object.hpp>

UserCase::UserCase(const std::string initialize_base_file, MonteCarloSimulationExecutor &monte_carlo_simulator, const std::string log_path)
    : SimulationCase(initialize_base_file, monte_carlo_simulator, log_path), monte_carlo_simulator_(monte_carlo_simulator) {}

UserCase::~UserCase() { delete spacecraft_; }

void UserCase::InitializeTargetObjects() {
  // Instantiate the target of the simulation
  // `spacecraft_id` corresponds to the index of `spacecraft_file` in simulation_base.ini
  const int spacecraft_id = 0;
  spacecraft_ = new UserSatellite(&simulation_configuration_, global_environment_, spacecraft_id);

  // Register the log output
  spacecraft_->LogSetup(*(simulation_configuration_.main_logger_));

  // Monte Carlo Simulation
  monte_carlo_simulator_.SetSeed();
  monte_carlo_simulator_.RandomizeAllParameters();
  SimulationObject::SetAllParameters(monte_carlo_simulator_);
  monte_carlo_simulator_.AtTheBeginningOfEachCase();
}

void UserCase::UpdateTargetObjects() {
  // Spacecraft Update
  spacecraft_->Update(&(global_environment_->GetSimulationTime()));
}

std::string UserCase::GetLogHeader() const {
  std::string str_tmp = "";

  str_tmp += WriteScalar("elapsed_time", "s");
  str_tmp += WriteVector("spacecraft_angular_velocity", "b", "rad/s", 3);
  str_tmp += WriteVector("spacecraft_quaternion", "i2b", "-", 4);

  return str_tmp;
}

std::string UserCase::GetLogValue() const {
  std::string str_tmp = "";

  str_tmp += WriteScalar(global_environment_->GetSimulationTime().GetElapsedTime_s());
  str_tmp += WriteVector(spacecraft_->GetDynamics().GetAttitude().GetAngularVelocity_b_rad_s(), 3);
  str_tmp += WriteQuaternion(spacecraft_->GetDynamics().GetAttitude().GetQuaternion_i2b());

  return str_tmp;
}
