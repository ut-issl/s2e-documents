/**
 * @file user_satellite.cpp
 * @brief An example of user side spacecraft class
 */

#include "user_satellite.hpp"

#include "user_components.hpp"

UserSatellite::UserSatellite(const SimulationConfiguration *simulation_configuration, const GlobalEnvironment *global_environment,
                             const unsigned int spacecraft_id)
    : Spacecraft(simulation_configuration, global_environment, spacecraft_id) {
  components_ =
      new UserComponents(dynamics_, structure_, local_environment_, global_environment, simulation_configuration, &clock_generator_, spacecraft_id);
}
