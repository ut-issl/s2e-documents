#include "User_Components.h"
#include "Initialize.h"
#include "../../Components/Initialize_UserComponent.h"

UserComponents::UserComponents(
  const Dynamics* dynamics, 
  const Structure* structure, 
  const LocalEnvironment* local_env, 
  const GlobalEnvironment* glo_env,
  const SimulationConfig* config,
  ClockGenerator* clock_gen,
  const int sat_id
):dynamics_(dynamics), structure_(structure), local_env_(local_env), glo_env_(glo_env), config_(config)
{
  IniAccess iniAccess = IniAccess(config->sat_file_[0]);
  double compo_step_sec = glo_env_->GetSimTime().GetCompoStepSec();

  obc_ = new OBC(clock_gen);

  std::string clock_sensor_ini_path = iniAccess.ReadString("COMPONENTS_FILE",
                                                           "clock_sensor_file");
  clock_sensor_ = new ClockSensor(InitClockSensor(clock_gen,
                                                  &glo_env->GetSimTime(),
                                                  clock_sensor_ini_path));
}

UserComponents::~UserComponents()
{
  delete clock_sensor_;
  delete obc_;
  // OBC must be deleted the last since it has com ports
}

Vector<3> UserComponents::GenerateForce_b()
{
  // There is no orbit control component, so it remains 0
  Vector<3> force_b_(0.0);
  return force_b_;
};

Vector<3> UserComponents::GenerateTorque_b()
{
  // No attitude control component
  Vector<3> torque_b_(0.0);
  return torque_b_;
};

void UserComponents::CompoLogSetUp(Logger & logger)
{
  // Users can set log output when they need component log
  logger.AddLoggable(clock_sensor_);
}
