#include "User_sat.h"
#include "User_Components.h"
#include "Initialize.h"
#include "ClockGenerator.h"


UserSat::UserSat(SimulationConfig* sim_config, const GlobalEnvironment* glo_env, const int sat_id)
:Spacecraft(sim_config, glo_env, sat_id)
{
  Initialize(sim_config, glo_env, sat_id);
}

UserSat::~UserSat()
{
  delete components_;
}

void UserSat::Initialize(SimulationConfig* sim_config, const GlobalEnvironment* glo_env, const int sat_id)
{
  components_ = new UserComponents(dynamics_, glo_env, sim_config, &clock_gen_, sat_id);
}

void UserSat::LogSetup(Logger & logger)
{
  Spacecraft::LogSetup(logger);
  components_->CompoLogSetUp(logger);
}

void UserSat::Update(const SimTime* sim_time)
{
  // Update Components
  for (int i = 0; i < sim_time->GetStepSec() * 1000; i++)
  {
    clock_gen_.TickToComponents();
  }
  GenerateTorque_b();
  // Update Dynamics
  Spacecraft::Update(sim_time);
}

void UserSat::GenerateTorque_b()
{
  dynamics_->AddTorque_b(components_->GenerateTorque_b());
}

void UserSat::GenerateForce_b()
{
  dynamics_->AddForce_b(components_->GenerateForce_b());
}
