#pragma once

#include <Simulation/Spacecraft/InstalledComponents.hpp>

#include "Dynamics.h"
#include "GlobalEnvironment.h"
#include "LocalEnvironment.h"
#include "Vector.hpp"

// include for components
#include "OBC_C2A.h"
#include "EXP.h"

class C2aCoreSampleComponents : public InstalledComponents {
 public:
  C2aCoreSampleComponents(const Dynamics* dynamics, const Structure* structure, const LocalEnvironment* local_env, const GlobalEnvironment* glo_env,
                          const SimulationConfig* config, ClockGenerator* clock_gen);
  ~C2aCoreSampleComponents();
  libra::Vector<3> GenerateForce_N_b();
  libra::Vector<3> GenerateTorque_Nm_b();
  void LogSetup(Logger& logger);

 private:
  // Components
  OBC_C2A* obc_;
  EXP *exp_;

  // References
  const Dynamics* dynamics_;
  const Structure* structure_;
  const LocalEnvironment* local_env_;
  const GlobalEnvironment* glo_env_;
  const SimulationConfig* config_;
};
