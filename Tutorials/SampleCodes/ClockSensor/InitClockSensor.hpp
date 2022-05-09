#pragma once
#include "ClockSensor.hpp"

ClockSensor InitClockSensor(ClockGenerator* clock_gen,
                            const SimTime& sim_time,
                            const std::string file_name);