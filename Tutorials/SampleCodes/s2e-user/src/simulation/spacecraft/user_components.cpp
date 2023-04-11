/**
 * @file user_components.cpp
 * @brief An example of user side components management installed on a spacecraft
 */

#include "user_components.hpp"

#include <library/initialize/initialize_file_access.hpp>

UserComponents::UserComponents(const Dynamics *dynamics, Structure *structure, const LocalEnvironment *local_environment,
                               const GlobalEnvironment *global_environment, const SimulationConfiguration *configuration,
                               ClockGenerator *clock_generator, const unsigned int spacecraft_id)
    : configuration_(configuration),
      dynamics_(dynamics),
      structure_(structure),
      local_environment_(local_environment),
      global_environment_(global_environment) {
  obc_ = new OnBoardComputer(clock_generator);
}

UserComponents::~UserComponents() {
  // OBC must be deleted the last since it has com ports
  delete obc_;
}

Vector<3> UserComponents::GenerateForce_b_N() {
  // There is no orbit control component, so it remains 0
  Vector<3> force_b_N(0.0);
  return force_b_N;
}

Vector<3> UserComponents::GenerateTorque_b_Nm() {
  // No attitude control component
  Vector<3> torque_b_Nm(0.0);
  return torque_b_Nm;
}

void UserComponents::LogSetup(Logger &logger) {
  // Users can set log output when they need component log
  UNUSED(logger);
}
