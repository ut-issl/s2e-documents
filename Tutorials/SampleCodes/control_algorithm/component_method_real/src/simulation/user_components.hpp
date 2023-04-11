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
#include <components/real/aocs/initialize_gyro_sensor.hpp>
#include <components/real/aocs/initialize_reaction_wheel.hpp>

#include "../../components/user_on_board_computer.hpp"

class UserOnBoardComputer;

class UserComponents : public InstalledComponents {
 public:
  UserComponents(const Dynamics *dynamics, Structure *structure, const LocalEnvironment *local_environment,
                 const GlobalEnvironment *global_environment, const SimulationConfiguration *configuration, ClockGenerator *clock_generator,
                 const unsigned int spacecraft_id);
  ~UserComponents();
  libra::Vector<3> GenerateForce_b_N();
  libra::Vector<3> GenerateTorque_b_Nm();
  void LogSetup(Logger &logger);

  // Getter
  inline GyroSensor &GetGyroSensor() { return *gyro_sensor_; }
  inline ReactionWheel &GetReactionWheel() { return *reaction_wheel_; }

 private:
  // Components
  UserOnBoardComputer *obc_;       //!< Onboard Computer
  GyroSensor *gyro_sensor_;        //!< Gyro sensor
  ReactionWheel *reaction_wheel_;  //!< Reaction wheel

  // States
  const SimulationConfiguration *configuration_;  //!< Simulation settings
  const Dynamics *dynamics_;                      //!< Dynamics information of the spacecraft
  Structure *structure_;                          //!< Structure information of the spacecraft
  const LocalEnvironment *local_environment_;     //!< Local environment information around the spacecraft
  const GlobalEnvironment *global_environment_;   //!< Global environment information
};

#endif  // S2E_SIMULATION_SPACECRAFT_USER_COMPONENTS_HPP_