#include "ClockSensor.hpp"

ClockSensor::ClockSensor(
  const int prescaler,
  ClockGenerator* clock_gen,
  const SimTime& sim_time,
  const double bias_sec
)
: ComponentBase(prescaler, clock_gen),
  sim_time_(sim_time), bias_sec_(bias_sec),
  time_output_sec_(0.0)
{
}

void ClockSensor::MainRoutine(int count)
{
  UNUSED(count);
  time_output_sec_ = sim_time_.GetElapsedSec() + bias_sec_;
}

std::string ClockSensor::GetLogHeader() const
{
  std::string str_tmp = "";
  std::string GSection = "clock_sensor";
  str_tmp += WriteScalar(GSection, "sec");

  return str_tmp;
}

std::string ClockSensor::GetLogValue() const
{
  std::string str_tmp = "";

  str_tmp += WriteScalar(time_output_sec_);

  return str_tmp;
}
