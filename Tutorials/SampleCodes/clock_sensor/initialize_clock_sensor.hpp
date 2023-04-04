/**
 * @file initialize_clock_sensor.hpp
 * @brief Initialize function for ClockSensor class
 */

#ifndef S2E_COMPONENTS_INITIALIZE_CLOCK_SENSOR_HPP_
#define S2E_COMPONENTS_INITIALIZE_CLOCK_SENSOR_HPP_

#include "clock_sensor.hpp"

/**
 * @fn InitGyroSensor
 * @brief Initialize functions for gyro sensor without power port
 * @param [in] clock_generator: Clock generator
 * @param [in] simulation_time: Simulation time information
 * @param [in] file_name: Path to the initialize file
 */
ClockSensor InitClockSensor(ClockGenerator *clock_generator, const SimulationTime &simulation_time, const std::string file_name);

#endif  // S2E_COMPONENTS_INITIALIZE_CLOCK_SENSOR_HPP_
