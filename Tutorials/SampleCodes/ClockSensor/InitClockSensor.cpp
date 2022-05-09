#include "ClockSensor.hpp"
#include <Interface/InitInput/IniAccess.h>

ClockSensor InitClockSensor(ClockGenerator* clock_gen,
                            const SimTime& sim_time,
                            const std::string file_name)
{
  IniAccess ini_file(file_name);

  const double bias_sec = ini_file.ReadDouble("ClockSensor", "bias_sec");
  const int prescaler = ini_file.ReadInt("ClockSensor", "prescaler");
  ClockSensor clock_sensor(prescaler, clock_gen, sim_time, bias_sec);

  return clock_sensor;
}
