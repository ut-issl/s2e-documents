#include "User_OBC.h"
#include "../Simulation/Spacecraft/User_Components.h"

UserOBC::UserOBC(ClockGenerator* clock_gen, UserComponents& components) : ComponentBase(100,clock_gen), components_(components)
{
  Initialize();
}

UserOBC::~UserOBC()
{
}

void UserOBC::Initialize()
{
}

double UserOBC::GetCurrent(int port_id) const
{
  if (isOn_)
  {
    return 0.1;
  }
  return 0;
}

void UserOBC::MainRoutine(int count)
{
  //Sensor inputs
  Vector<3> gyro_omega_c = components_.GetGyro().GetOmegaC();
  double rw_rpm = components_.GetRw().GetVelocityRpm();

  //Control Algorithm
  double Kp = 5e-3;
  double torque = -1.0*Kp*gyro_omega_c(0);
  
  //Actuator outputs
	components_.GetRw().SetDriveFlag(true);
	components_.GetRw().SetVelocityLimitRpm(6000);
  components_.GetRw().SetTargetTorqueBody(torque);
}
