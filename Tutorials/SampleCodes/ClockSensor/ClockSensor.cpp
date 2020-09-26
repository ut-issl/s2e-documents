#include "ClockSensor.h"

ClockSensor::ClockSensor(int prescaler, ClockGenerator* clock_gen, const SimTime* sim_time, double bias_sec)
 : ComponentBase(prescaler, clock_gen), sim_time_(sim_time), bias_sec_(bias_sec), time_output_sec_(0.0)
{
}

void ClockSensor::MainRoutine(int count)
{
  time_output_sec_ = sim_time_->GetElapsedSec() + bias_sec_;
}

string ClockSensor::GetLogHeader() const
{
  string str_tmp = "";
  string GSection = "clock_sensor";
  str_tmp += WriteScalar(GSection, "sec");

  return str_tmp;
}

string ClockSensor::GetLogValue() const
{
  string str_tmp = "";

  str_tmp += WriteScalar(time_output_sec_);

  return str_tmp;
}
