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
  IniAccess ini_access = IniAccess(config->sat_file_[0]);
  const double compo_step_sec = glo_env_->GetSimTime().GetCompoStepSec();

  obc_ = new UserObc(clock_gen, *this);
  
  const std::string gyro_ini_path = ini_access.ReadString("COMPONENTS_FILE", "gyro_file");
  gyro_ = new Gyro(InitGyro(clock_gen, 1, gyro_ini_path, compo_step_sec, dynamics));

  const std::string rw_ini_path = ini_access.ReadString("COMPONENTS_FILE", "rw_file");
  rw_ = new RWModel(InitRWModel(clock_gen, 1, rw_ini_path, dynamics->GetAttitude().GetPropStep(), compo_step_sec));
}

UserComponents::~UserComponents()
{
  delete gyro_;
  delete rw_;
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
  torque_Nm_b_ = rw_->GetOutputTorqueB();
  return torque_Nm_b_;
}

void UserComponents::LogSetup(Logger & logger)
{
  logger.AddLoggable(gyro_);
  logger.AddLoggable(rw_);
}
