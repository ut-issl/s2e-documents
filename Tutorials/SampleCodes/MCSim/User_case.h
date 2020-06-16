#pragma once

#include "SimulationCase.h"
#include "MCSimExecutor.h"
#include "../Spacecraft/User_sat.h"

class SimTime;
class Logger;

class UserCase : public SimulationCase
{
public:
  UserCase(string ini_fname, MCSimExecutor& mc_sim, string log_path);
  virtual ~UserCase();
  void Initialize();
  void Main();

  virtual string GetLogHeader() const;
  virtual string GetLogValue() const;

private:
  string ini_fname;
  SimTime* sim_time;
  Logger* default_log;
  UserSat* spacecraft;
  MCSimExecutor& mc_sim_;
  string log_path_;
};
