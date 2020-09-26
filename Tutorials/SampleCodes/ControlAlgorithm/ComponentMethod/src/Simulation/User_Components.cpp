#include "User_Components.h"

UserComponents::UserComponents(const Dynamics *dynamics, const GlobalEnvironment* glo_env, const SimulationConfig *config, ClockGenerator *clock_gen, const int sat_id)
{
  IniAccess iniAccess = IniAccess(config->sat_file_[0]);
  obc_ = new UserOBC(clock_gen,*this);

  const string gyro_ini_path = iniAccess.ReadString("COMPONENTS_FILE", "gyro_file");
  gyro_ = new Gyro(InitGyro(clock_gen, 1, 1, gyro_ini_path, dynamics));

  const string rw_ini_path = iniAccess.ReadString("COMPONENTS_FILE", "rw_file");
  rw_ = new RWModel(InitRWModel(clock_gen, 1,rw_ini_path,dynamics->GetAttitude().GetPropStep(),0.001));
}

UserComponents::~UserComponents()
{
  delete obc_;
  delete gyro_;
  delete rw_;
}

Vector<3> UserComponents::GenerateForce_b()
{
  //There is no orbit control component, so it remains 0
  Vector<3> force_b_(0.0);
  return force_b_;
};

Vector<3> UserComponents::GenerateTorque_b()
{
  Vector<3> torque_b_(0.0);
  torque_b_ = rw_->GetOutputTorqueB();
  return torque_b_;
};

void UserComponents::CompoLogSetUp(Logger &logger)
{
  logger.AddLoggable(gyro_);
  logger.AddLoggable(rw_);
}