/**
 * @file user_on_board_computer.hpp
 * @brief User defined on board computer
 */

#include "user_on_board_computer.hpp"

UserOnBoardComputer::UserOnBoardComputer(ClockGenerator* clock_generator, UserComponents& components)
    : Component(1, clock_generator), components_(components) {}

UserOnBoardComputer::~UserOnBoardComputer() {}

void UserOnBoardComputer::MainRoutine(const int time_count) {
  UNUSED(time_count);
  // Sensor inputs
  const libra::Vector<3> gyro_omega_c = components_.GetGyroSensor().GetMeasuredAngularVelocity_c_rad_s();
  // const double rw_rpm = components_.GetReactionWheel().GetAngularVelocity_rpm();  // An example of RW rotation speed observation

  // Control Algorithm
  const double Kp = 5e-3;
  double torque = -1.0 * Kp * gyro_omega_c(0);

  // Actuator outputs
  components_.GetReactionWheel().SetDriveFlag(true);
  components_.GetReactionWheel().SetVelocityLimit_rpm(8000.0);
  components_.GetReactionWheel().SetTargetTorque_b_Nm(torque);
}
