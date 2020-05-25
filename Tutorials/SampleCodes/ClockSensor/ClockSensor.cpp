#include "ClockSensor.h"

ClockSensor::ClockSensor(SimTime* sim_time_) : ComponentBase(),sim_time(sim_time_)
{
  time_output_sec = 0.0;
  bias_sec = 0.001;
}

void ClockSensor::MainRoutine(int count)
{
  time_output_sec = sim_time->GetElapsedSec() + bias_sec;
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

  str_tmp += WriteScalar(time_output_sec);

  return str_tmp;
}
