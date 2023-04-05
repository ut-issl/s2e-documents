/**
 * @file sample_components.hpp
 * @brief An example of user side components management installed on a spacecraft
 */

#ifndef S2E_SIMULATION_SPACECRAFT_USER_COMPONENTS_HPP_
#define S2E_SIMULATION_SPACECRAFT_USER_COMPONENTS_HPP_

#include <dynamics/dynamics.hpp>
#include <environment/global/global_environment.hpp>
#include <environment/local/local_environment.hpp>
#include <library/math/vector.hpp>
#include <simulation/spacecraft/installed_components.hpp>

// include for components
#include <components/real/cdh/on_board_computer.hpp>

#include "../../components/initialize_clock_sensor.hpp"

class UserComponents : public InstalledComponents {
 public:
  UserComponents(const Dynamics *dynamics, Structure *structure, const LocalEnvironment *local_environment,
                 const GlobalEnvironment *global_environment, const SimulationConfiguration *configuration, ClockGenerator *clock_generator,
                 const unsigned int spacecraft_id);
  ~UserComponents();
  libra::Vector<3> GenerateForce_b_N();
  libra::Vector<3> GenerateTorque_b_Nm();
  void LogSetup(Logger &logger);

 private:
  // Components
  OnBoardComputer *obc_;  //!< Onboard Computer
  ClockSensor *clock_sensor_;

  // States
  const SimulationConfiguration *configuration_;  //!< Simulation settings
  const Dynamics *dynamics_;                      //!< Dynamics information of the spacecraft
  Structure *structure_;                          //!< Structure information of the spacecraft
  const LocalEnvironment *local_environment_;     //!< Local environment information around the spacecraft
  const GlobalEnvironment *global_environment_;   //!< Global environment information
};

#endif  // S2E_SIMULATION_SPACECRAFT_USER_COMPONENTS_HPP_
