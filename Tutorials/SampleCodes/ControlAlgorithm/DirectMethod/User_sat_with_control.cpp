#include "User_sat_with_control.h"

UserSat::UserSat(SimulationConfig* sim_config, const GlobalEnvironment* glo_env, const int sat_id)
:Spacecraft(sim_config, glo_env, sat_id)
{
}

UserSat::~UserSat()
{
}

void UserSat::Initialize(void)
{
}

void UserSat::LogSetup(Logger & logger)
{
  Spacecraft::LogSetup(logger);
}

void UserSat::Update(const SimTime* sim_time)
{
  // Update Dynamics
  Spacecraft::Update(sim_time);
  // clear force and torques
  Clear();
  
  // Sensing
  Vector<3> observed_omega_b = dynamics_->GetAttitude().GetOmega_b();
  
  // Control algorithm
  Vector<3> control_torque_b(0.0);
  Vector<3> control_force_b(0.0);
  double Kp = 5.0e-3;
  control_torque_b = -1.0 * Kp * observed_omega_b;

  // Generate force and torque
  dynamics_->AddTorque_b(control_torque_b);
  dynamics_->AddForce_b(control_force_b);
}
