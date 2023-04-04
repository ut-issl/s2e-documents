/**
 * @file user_case.hpp
 * @brief Example of user defined simulation case
 */

#ifndef S2E_SIMULATION_CASE_USER_CASE_HPP_
#define S2E_SIMULATION_CASE_USER_CASE_HPP_

#include <./simulation/case/simulation_case.hpp>
#include <./simulation/monte_carlo_simulation/monte_carlo_simulation_executor.hpp>

#include "../spacecraft/user_satellite.hpp"

/**
 * @class UserCase
 * @brief An example of user defined simulation case
 */
class UserCase : public SimulationCase {
 public:
  /**
   * @fn UserCase
   * @brief Constructor
   */
  UserCase(const std::string initialize_base_file, MonteCarloSimulationExecutor &monte_carlo_simulator, const std::string log_path);
  /**
   * @fn ~UserCase
   * @brief Destructor
   */
  virtual ~UserCase();

  /**
   * @fn GetLogHeader
   * @brief Override function of GetLogHeader
   */
  virtual std::string GetLogHeader() const;
  /**
   * @fn GetLogValue
   * @brief Override function of GetLogValue
   */
  virtual std::string GetLogValue() const;

 private:
  UserSatellite *spacecraft_;  //!< Instance of spacecraft

  MonteCarloSimulationExecutor &monte_carlo_simulator_;

  /**
   * @fn InitializeTargetObjects
   * @brief Override function of InitializeTargetObjects in SimulationCase
   */
  void InitializeTargetObjects();

  /**
   * @fn UpdateTargetObjects
   * @brief Override function of Main in SimulationCase
   */
  void UpdateTargetObjects();
};

#endif  // S2E_SIMULATION_CASE_USER_CASE_HPP_
