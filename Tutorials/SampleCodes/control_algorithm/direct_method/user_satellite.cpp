/**
 * @file user_satellite.cpp
 * @brief An example of user side spacecraft class
 */

#include "user_satellite.hpp"

#include "user_components.hpp"

UserSatellite::UserSatellite(const SimulationConfiguration *simulation_configuration, const GlobalEnvironment *global_environment,
                             const unsigned int spacecraft_id)
    : Spacecraft(simulation_configuration, global_environment, spacecraft_id) {
  components_ =
      new UserComponents(dynamics_, structure_, local_environment_, global_environment, simulation_configuration, &clock_generator_, spacecraft_id);
}
void UserSatellite::Update(const SimulationTime *simulation_time) {
  dynamics_->ClearForceTorque();

  // Update local environment and disturbance
  local_environment_->Update(dynamics_, simulation_time);
  disturbances_->Update(*local_environment_, *dynamics_, simulation_time);

  // Control algorithm
  ControlAlgorithm();

  // Add generated force and torque by disturbances
  dynamics_->AddAcceleration_i_m_s2(disturbances_->GetAcceleration_i_m_s2());
  dynamics_->AddTorque_b_Nm(disturbances_->GetTorque_b_Nm());
  dynamics_->AddForce_b_N(disturbances_->GetForce_b_N());

  // Propagate dynamics
  dynamics_->Update(simulation_time, &(local_environment_->GetCelestialInformation()));
}

void UserSatellite::ControlAlgorithm(void) {
  // Sensing
  Vector<3> observed_omega_b_rad_s = dynamics_->GetAttitude().GetAngularVelocity_b_rad_s();

  // Control algorithm
  Vector<3> control_torque_b_Nm(0.0);
  Vector<3> control_force_b_N(0.0);
  double Kp = 5.0e-3;
  control_torque_b_Nm = -1.0 * Kp * observed_omega_b_rad_s;

  // Generate force and torque
  dynamics_->AddTorque_b_Nm(control_torque_b_Nm);
  dynamics_->AddForce_b_N(control_force_b_N);
}
