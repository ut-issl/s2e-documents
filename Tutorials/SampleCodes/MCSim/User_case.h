#pragma once

#include "SimulationCase.h"
#include "../Spacecraft/User_sat.h"
#include "MCSimExecutor.h"

class UserCase : public SimulationCase
{
public:
  UserCase(string ini_fname, MCSimExecutor& mc_sim, const string log_path);
  virtual ~UserCase();
  
  void Initialize();
  void Main();

  virtual string GetLogHeader() const;
  virtual string GetLogValue() const;

private:
  UserSat* spacecraft_;
  MCSimExecutor& mc_sim_;
};
