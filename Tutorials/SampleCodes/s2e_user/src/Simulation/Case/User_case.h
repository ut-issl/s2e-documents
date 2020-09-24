#pragma once

#include "SimulationCase.h"
#include "../Spacecraft/User_sat.h"

class UserCase : public SimulationCase
{
public:
  UserCase(string ini_fname);
  virtual ~UserCase();
  
  void Initialize();
  void Main();

  virtual string GetLogHeader() const;
  virtual string GetLogValue() const;

private:
  UserSat* spacecraft_;
};
