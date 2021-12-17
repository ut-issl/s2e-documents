#pragma once

#include "Spacecraft.h"
#include "User_Components.h"

class UserSat : public Spacecraft
{
public:
  UserSat(SimulationConfig* sim_config, const GlobalEnvironment* glo_env, const int sat_id);
  ~UserSat();

  virtual void Initialize(SimulationConfig* sim_config, const GlobalEnvironment* glo_env, const int sat_id);
  virtual void LogSetup(Logger& logger);
  virtual void Update(const SimTime* sim_time);

private:
  UserComponents* components_;
};
