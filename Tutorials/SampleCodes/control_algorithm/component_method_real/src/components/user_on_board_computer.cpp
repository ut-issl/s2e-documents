#include "UserObc.hpp"
#include "../Simulation/Spacecraft/UserComponents.hpp"

UserObc::UserObc(ClockGenerator* clock_gen, UserComponents& components)
: ComponentBase(1, clock_gen), components_(components)
{
  Initialize();
}

UserObc::~UserObc()
{
}

void UserObc::Initialize()
{
}

void UserObc::MainRoutine(int count)
{
  UNUSED(count);
  // Sensor inputs
  const libra::Vector<3> gyro_omega_c = components_.GetGyro().GetOmegaC();
  // const double rw_rpm = components_.GetRw().GetVelocityRpm();  // An example of RW rotation speed observation

  // Control Algorithm
  const double Kp = 5e-3;
  double torque = -1.0 * Kp * gyro_omega_c(0);
  
  // Actuator outputs
	components_.GetRw().SetDriveFlag(true);
	components_.GetRw().SetVelocityLimitRpm(8000);
  components_.GetRw().SetTargetTorqueBody(torque);
}
