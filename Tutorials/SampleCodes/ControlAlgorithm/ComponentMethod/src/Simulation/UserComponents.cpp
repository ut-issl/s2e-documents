#include "User_Components.h"
#include "Initialize.h"

UserComponents::UserComponents(
  const Dynamics* dynamics, 
  const Structure* structure, 
  const LocalEnvironment* local_env, 
  const GlobalEnvironment* glo_env,
  const SimulationConfig* config,
  ClockGenerator* clock_gen,
  const int sat_id
):dynamics_(dynamics), structure_(structure),
  local_env_(local_env), glo_env_(glo_env),
  config_(config)
{
  IniAccess iniAccess = IniAccess(config->sat_file_[0]);
  double compo_step_sec = glo_env_->GetSimTime().GetCompoStepSec();

  obc_ = new UserOBC(clock_gen, *this);
  
  const std::string gyro_ini_path = iniAccess.ReadString("COMPONENTS_FILE", "gyro_file");
  gyro_ = new Gyro(InitGyro(clock_gen, 1, gyro_ini_path, compo_step_sec, dynamics));

  const std::string rw_ini_path = iniAccess.ReadString("COMPONENTS_FILE", "rw_file");
  rw_ = new RWModel(InitRWModel(clock_gen, 1, rw_ini_path, dynamics->GetAttitude().GetPropStep(), compo_step_sec));
}

UserComponents::~UserComponents()
{
  delete gyro_;
  delete rw_;
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
  torque_b_ = rw_->GetOutputTorqueB();
  return torque_b_;
};

void UserComponents::CompoLogSetUp(Logger & logger)
{
  // Users can set log output when they need component log
  logger.AddLoggable(gyro_);
  logger.AddLoggable(rw_);
}
