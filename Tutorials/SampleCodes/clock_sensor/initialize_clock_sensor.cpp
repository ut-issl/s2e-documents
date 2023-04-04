
/**
 * @file initialize_clock_sensor.cpp
 * @brief Initialize function for ClockSensor class
 */

#include "initialize_clock_sensor.hpp"

#include <library/initialize/initialize_file_access.hpp>

ClockSensor InitClockSensor(ClockGenerator* clock_generator, const SimulationTime& simulation_time, const std::string file_name) {
  IniAccess ini_file(file_name);

  const double bias_sec = ini_file.ReadDouble("ClockSensor", "bias_sec");
  const int prescaler = ini_file.ReadInt("ClockSensor", "prescaler");
  ClockSensor clock_sensor(prescaler, clock_generator, simulation_time, bias_sec);

  return clock_sensor;
}
