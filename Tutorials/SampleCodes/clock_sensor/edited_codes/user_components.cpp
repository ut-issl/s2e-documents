#include "UserComponents.hpp"

#include <Interface/InitInput/IniAccess.h>
#include "../../Components/InitClockSensor.hpp"

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
  IniAccess ini_access = IniAccess(config->sat_file_[0]);
  std::string clock_sensor_ini_path = ini_access.ReadString("COMPONENTS_FILE", "clock_sensor_file");
  clock_sensor_ = new ClockSensor(InitClockSensor(clock_gen, glo_env->GetSimTime(), clock_sensor_ini_path));
}

UserComponents::~UserComponents()
{
  delete clock_sensor_;
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
  logger.AddLoggable(clock_sensor_);
}
