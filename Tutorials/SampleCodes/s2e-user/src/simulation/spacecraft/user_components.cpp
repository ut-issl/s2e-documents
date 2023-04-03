#include "UserComponents.hpp"

#include <Interface/InitInput/IniAccess.h>

UserComponents::UserComponents(
  const Dynamics* dynamics, 
  const Structure* structure, 
  const LocalEnvironment* local_env, 
  const GlobalEnvironment* glo_env,
  const SimulationConfig* config,
  ClockGenerator* clock_gen
):dynamics_(dynamics), structure_(structure), local_env_(local_env), glo_env_(glo_env), config_(config)
{
  obc_ = new OBC(clock_gen);
}

UserComponents::~UserComponents()
{
  // OBC must be deleted the last since it has com ports
  delete obc_;
}

Vector<3> UserComponents::GenerateForce_N_b()
{
  // There is no orbit control component, so it remains 0
  Vector<3> force_N_b_(0.0);
  return force_N_b_;
}

Vector<3> UserComponents::GenerateTorque_Nm_b()
{
  // No attitude control component
  Vector<3> torque_Nm_b_(0.0);
  return torque_Nm_b_;
}

void UserComponents::LogSetup(Logger & logger)
{
  // Users can set log output when they need component log
  UNUSED(logger);
}
