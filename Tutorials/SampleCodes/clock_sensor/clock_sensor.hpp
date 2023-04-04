/**
 * @file clock_sensor.hpp
 * @brief An example to emulate a sensor to measure simulation elapsed time
 */

#ifndef S2E_COMPONENTS_CLOCK_SENSOR_HPP_
#define S2E_COMPONENTS_CLOCK_SENSOR_HPP_

#include <components/base/component.hpp>
#include <environment/global/simulation_time.hpp>
#include <library/logger/loggable.hpp>

/**
 * @class ClockSensor
 * @brief An example to emulate a sensor to measure simulation elapsed time
 */
class ClockSensor : public Component, public ILoggable {
 public:
  /**
   * @fn ClockSensor
   * @brief Constructor
   * @param [in] prescaler: Frequency scale factor for update
   * @param [in] clock_generator: Clock generator
   * @param [in] simulation_time: Simulation time information
   * @param [in] bias_sec: Bias value for clock observation [sec]
   */
  ClockSensor(const int prescaler, ClockGenerator* clock_generator, const SimulationTime& simulation_time, const double bias_sec);

 private:
  // Override functions for Component
  /**
   * @fn MainRoutine
   * @brief Main routine for sensor observation
   */
  void MainRoutine(const int time_count) override;

  // Override ILoggable
  /**
   * @fn GetLogHeader
   * @brief Override GetLogHeader function of ILoggable
   */
  virtual std::string GetLogHeader() const;
  /**
   * @fn GetLogValue
   * @brief Override GetLogValue function of ILoggable
   */
  virtual std::string GetLogValue() const;

  const SimulationTime& simulation_time_;  //!< Simulation time information
  double bias_sec_;                        //!< Bias value for clock observation [sec]
  double time_output_sec_;                 //!< Output of measured time information
};

#endif  // S2E_COMPONENTS_CLOCK_SENSOR_HPP_
