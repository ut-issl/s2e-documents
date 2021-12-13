#pragma once

#include "Spacecraft.h"

class UserComponents;

class UserSat : public Spacecraft
{
public:
  UserSat(SimulationConfig* sim_config, const GlobalEnvironment* glo_env, const int sat_id);
  ~UserSat();

  virtual void Initialize(void);
  virtual void LogSetup(Logger& logger);
  virtual void Update(const SimTime* sim_time);

private:
};
