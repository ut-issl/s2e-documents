#pragma once
#include "ComponentBase.h"
#include "ILoggable.h"
#include "SimTime.h"

class ClockSensor: public ComponentBase, public ILoggable
{
public:
  ClockSensor(int prescaler, ClockGenerator* clock_gen, const SimTime* sim_time, double bias_sec);
protected:
  void MainRoutine(int count);
  virtual string GetLogHeader() const;
  virtual string GetLogValue() const;
private:
  int prescaler_;
  ClockGenerator* clock_gen_;
  const SimTime* sim_time_;
  double time_output_sec_;
  double bias_sec_;
};