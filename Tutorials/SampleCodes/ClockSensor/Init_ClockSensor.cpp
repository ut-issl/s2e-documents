#include "Initialize.h"
#include <string.h>
#include "../../../Component/Abstract/ClockSensor.h"

ClockSensor InitClockSensor(SimTime* sim_time_, string file_name_)
{
  IniAccess ini_file(file_name_);

  double bias_sec_ = ini_file.ReadDouble("ClockSensor", "bias_sec");
  ClockSensor clock_sensor_(sim_time_, bias_sec_);

  return clock_sensor_;
}
