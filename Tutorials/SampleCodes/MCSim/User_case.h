#pragma once

#include "SimulationCase.h"
#include "../Spacecraft/User_sat.h"
#include "MCSimExecutor.h"

class UserCase: public SimulationCase
{
public:
  UserCase(std::string ini_fname, MCSimExecutor& mc_sim, const std::string log_path);
  virtual ~UserCase();
  
  void Initialize();
  void Main();

  virtual std::string GetLogHeader() const;
  virtual std::string GetLogValue() const;

private:
  UserSat* spacecraft_;
  MCSimExecutor& mc_sim_;
};
