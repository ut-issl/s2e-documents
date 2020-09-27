#pragma once
#include "ComponentBase.h"
#include "Vector.hpp"

class UserComponents;

class UserOBC: public ComponentBase
{
public:
  UserOBC(ClockGenerator* clock_gen, UserComponents& components);
  ~UserOBC();
  void Initialize();
  double GetCurrent(int port_id) const;
protected:
  UserComponents& components_;
  void MainRoutine(int count);
};