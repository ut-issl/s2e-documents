#pragma once
#include "ComponentBase.h"
#include "Vector.hpp"

class UserComponents;

class UserObc: public ComponentBase
{
public:
  UserObc(ClockGenerator* clock_gen, UserComponents& components);
  ~UserObc();
  void Initialize();
  double GetCurrent(int port_id) const;
protected:
  UserComponents& components_;
  void MainRoutine(int count);
};
