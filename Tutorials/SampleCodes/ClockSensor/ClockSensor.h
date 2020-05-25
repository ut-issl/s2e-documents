#pragma once
#include "../Abstract/ComponentBase.h"
#include "../../Interface/LogOutput/ILoggable.h"
#include "../../Dynamics/SimTime.h"

class ClockSensor : public ComponentBase, public ILoggable
{
public:
  ClockSensor(SimTime* sim_time_ );
protected:
  void MainRoutine(int count);
  virtual string GetLogHeader() const;
  virtual string GetLogValue() const;
private:
  SimTime* sim_time; //本当はconstにしたいが．．．
  double time_output_sec;
  double bias_sec;
};