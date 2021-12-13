#pragma once
#include "ClockSensor.h"

ClockSensor InitClockSensor(ClockGenerator* clock_gen,
                            const SimTime* sim_time,
                            std::string file_name);