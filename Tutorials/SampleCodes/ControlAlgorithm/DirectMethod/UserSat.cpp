#include "UserSat.hpp"
#include "UserComponents.hpp"

UserSat::UserSat(SimulationConfig* sim_config, const GlobalEnvironment* glo_env, const int sat_id)
:Spacecraft(sim_config, glo_env, sat_id)
{
  components_ = new UserComponents(dynamics_, structure_, local_env_, glo_env, sim_config, &clock_gen_);
}

void UserSat::Update(const SimTime* sim_time)
{
  dynamics_->ClearForceTorque();

  // Update local environment and disturbance
  local_env_->Update(dynamics_, sim_time);
  disturbances_->Update(*local_env_, *dynamics_, sim_time);
  // Update components
  clock_gen_.UpdateComponents(sim_time);
  
  // Sensing
  Vector<3> observed_omega_b = dynamics_->GetAttitude().GetOmega_b();
  
  // Control algorithm
  Vector<3> control_torque_b(0.0);
  Vector<3> control_force_b(0.0);
  double Kp = 5.0e-3;
  control_torque_b = -1.0 * Kp * observed_omega_b;

  // Add generated force and torque by disturbances
  dynamics_->AddAcceleration_i(disturbances_->GetAccelerationI());
  dynamics_->AddTorque_b(disturbances_->GetTorque());
  dynamics_->AddForce_b(disturbances_->GetForce());
  // Generate force and torque
  dynamics_->AddTorque_b(control_torque_b);
  dynamics_->AddForce_b(control_force_b);

  // Propagate dynamics
  dynamics_->Update(sim_time, &(local_env_->GetCelesInfo()));
}
