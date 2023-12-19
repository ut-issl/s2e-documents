/**
 * @file c2a_core_sample_components.cpp
 * @brief User side components management installed on a spacecraft for C2A-CORE
 */

#include "c2a_core_sample_components.hpp"

#include <library/initialize/initialize_file_access.hpp>

#ifdef USE_C2A
#include "src_user/Settings/port_config.h"
#endif

C2aCoreSampleComponents::C2aCoreSampleComponents(const Dynamics* dynamics, Structure* structure, const LocalEnvironment* local_environment,
                                                 const GlobalEnvironment* global_environment, const SimulationConfiguration* configuration,
                                                 ClockGenerator* clock_generator)
    : dynamics_(dynamics),
      structure_(structure),
      local_environment_(local_environment),
      global_environment_(global_environment),
      configuration_(configuration) {
#ifdef USE_C2A
  obc_ = new ObcWithC2a(clock_generator, 100);
  exp_serial_communication_ = new ExampleSerialCommunicationWithObc(clock_generator, 1, 1, obc_);

  obc_->ConnectComPort(PORT_CH_RS422_MOBC_EXT, 1024, 1024);  // UART通信用にとりあえず繋いでおく
#endif
}

C2aCoreSampleComponents::~C2aCoreSampleComponents() {
  delete exp_serial_communication_;
  // OBC must be deleted the last since it has com ports
  delete obc_;
}

Vector<3> C2aCoreSampleComponents::GenerateForce_b_N() {
  // There is no orbit control component, so it remains 0
  Vector<3> force_b_N(0.0);
  return force_b_N;
}

Vector<3> C2aCoreSampleComponents::GenerateTorque_b_Nm() {
  // No attitude control component
  Vector<3> torque_b_Nm(0.0);
  return torque_b_Nm;
}

void C2aCoreSampleComponents::LogSetup(Logger& logger) { UNUSED(logger); }
