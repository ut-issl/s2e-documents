#pragma once
#include "ComponentBase.h"
#include "ILoggable.h"
#include "SimTime.h"

class ClockSensor: public ComponentBase, public ILoggable
{
public:
  ClockSensor(
    const int prescaler,
    ClockGenerator* clock_gen,
    const SimTime& sim_time,
    const double bias_sec
  );

protected:
  void MainRoutine(int count);
  virtual std::string GetLogHeader() const;
  virtual std::string GetLogValue() const;

private:
  int prescaler_;
  ClockGenerator* clock_gen_;
  const SimTime& sim_time_;
  double bias_sec_;
  double time_output_sec_;
};
