#pragma once

#include <dynamics/dynamics.hpp>
#include <environment/global/global_environment.hpp>
#include <environment/local/local_environment.hpp>
#include <library/math/vector.hpp>
#include <simulation/spacecraft/installed_components.hpp>

// include for components
#include <components/examples/example_serial_communication_with_obc.hpp>
#include <components/real/cdh/on_board_computer_with_c2a.hpp>

class C2aCoreSampleComponents : public InstalledComponents {
 public:
  C2aCoreSampleComponents(const Dynamics* dynamics, const Structure* structure, const LocalEnvironment* local_env, const GlobalEnvironment* glo_env,
                          const SimulationConfiguration* config, ClockGenerator* clock_gen);
  ~C2aCoreSampleComponents();
  libra::Vector<3> GenerateForce_b_N();
  libra::Vector<3> GenerateTorque_b_Nm();
  void LogSetup(Logger& logger);

 private:
  // Components
  ObcWithC2a* obc_;
  ExampleSerialCommunicationWithObc* exp_serial_communication_;

  // References
  const Dynamics* dynamics_;
  const Structure* structure_;
  const LocalEnvironment* local_env_;
  const GlobalEnvironment* glo_env_;
  const SimulationConfiguration* config_;
};
