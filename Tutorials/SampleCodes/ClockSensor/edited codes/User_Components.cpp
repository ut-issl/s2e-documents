#include "User_Components.h"
#include "../../Components/Initialize_UserComponent.h"

UserComponents::UserComponents(const Dynamics *dynamics, const GlobalEnvironment* glo_env, const SimulationConfig *config, ClockGenerator *clock_gen, const int sat_id)
{
  IniAccess iniAccess = IniAccess(config->sat_file_[0]);
  obc_ = new OBC(clock_gen);
  //clock_sensor_ = new ClockSensor(10,clock_gen,&glo_env->GetSimTime(),0.001);
  string clock_sensor_ini_path = iniAccess.ReadString("COMPONENTS_FILE", "clock_sensor_file");
  clock_sensor_ = new ClockSensor(InitClockSensor(clock_gen,&glo_env->GetSimTime(),clock_sensor_ini_path));
}

UserComponents::~UserComponents()
{
  delete obc_;
  delete clock_sensor_;
}

Vector<3> UserComponents::GenerateForce_b()
{
  //There is no orbit control component, so it remains 0
  Vector<3> force_b_(0.0);
  return force_b_;
};

Vector<3> UserComponents::GenerateTorque_b()
{
  //No attitude control component
  Vector<3> torque_b_(0.0);
  return torque_b_;
};

void UserComponents::CompoLogSetUp(Logger &logger)
{
  logger.AddLoggable(clock_sensor_);
}