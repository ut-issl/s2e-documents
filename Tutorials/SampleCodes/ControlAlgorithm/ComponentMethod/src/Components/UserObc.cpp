#include "User_OBC.h"
#include "../Simulation/Spacecraft/User_Components.h"

UserOBC::UserOBC(ClockGenerator* clock_gen, UserComponents& components)
: ComponentBase(1, clock_gen), components_(components)
{
  Initialize();
}

UserOBC::~UserOBC()
{
}

void UserOBC::Initialize()
{
}

void UserOBC::MainRoutine(int count)
{
  // Sensor inputs
  libra::Vector<3> gyro_omega_c = components_.GetGyro().GetOmegaC();
  double rw_rpm = components_.GetRw().GetVelocityRpm();

  // Control Algorithm
  double Kp = 5e-3;
  double torque = -1.0*Kp*gyro_omega_c(0);
  
  // Actuator outputs
	components_.GetRw().SetDriveFlag(true);
	components_.GetRw().SetVelocityLimitRpm(8000);
  components_.GetRw().SetTargetTorqueBody(torque);
}
