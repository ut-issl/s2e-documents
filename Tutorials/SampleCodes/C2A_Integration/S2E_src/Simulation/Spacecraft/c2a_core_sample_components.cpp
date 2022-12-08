#include "c2a_core_sample_components.h"

#include <Interface/InitInput/IniAccess.h>

#ifdef USE_C2A
#include "src_user/Settings/port_config.h"
#endif

C2aCoreSampleComponents::C2aCoreSampleComponents(const Dynamics* dynamics, const Structure* structure, const LocalEnvironment* local_env,
                                                 const GlobalEnvironment* glo_env, const SimulationConfig* config, ClockGenerator* clock_gen)
    : dynamics_(dynamics), structure_(structure), local_env_(local_env), glo_env_(glo_env), config_(config) {
#ifdef USE_C2A
  obc_ = new OBC_C2A(clock_gen, 100);
  exp_ = new EXP(clock_gen, 1, 1, obc_);

  obc_->ConnectComPort(PORT_CH_RS422_MOBC_EXT, 1024, 1024);  // UART通信用にとりあえず繋いでおく
#endif
}

C2aCoreSampleComponents::~C2aCoreSampleComponents() {
  delete exp_;
  // OBC must be deleted the last since it has com ports
  delete obc_;
}

Vector<3> C2aCoreSampleComponents::GenerateForce_N_b() {
  // There is no orbit control component, so it remains 0
  Vector<3> force_N_b_(0.0);
  return force_N_b_;
}

Vector<3> C2aCoreSampleComponents::GenerateTorque_Nm_b() {
  // No attitude control component
  Vector<3> torque_Nm_b_(0.0);
  return torque_Nm_b_;
}

void C2aCoreSampleComponents::LogSetup(Logger& logger) { UNUSED(logger); }
