/**
 * @file clock_sensor.cpp
 * @brief An example to emulate a sensor to measure simulation elapsed time
 */

#include "clock_sensor.hpp"

ClockSensor::ClockSensor(const int prescaler, ClockGenerator* clock_generator, const SimulationTime& simulation_time, const double bias_sec)
    : Component(prescaler, clock_generator), simulation_time_(simulation_time), bias_sec_(bias_sec), time_output_sec_(0.0) {}

void ClockSensor::MainRoutine(const int time_count) {
  UNUSED(time_count);
  time_output_sec_ = simulation_time_.GetElapsedTime_s() + bias_sec_;
}

std::string ClockSensor::GetLogHeader() const {
  std::string str_tmp = "";
  std::string section = "clock_sensor_";
  str_tmp += WriteScalar(section + "observed_time", "sec");

  return str_tmp;
}

std::string ClockSensor::GetLogValue() const {
  std::string str_tmp = "";

  str_tmp += WriteScalar(time_output_sec_);

  return str_tmp;
}
