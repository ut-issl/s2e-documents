#pragma once

#include "Spacecraft.h"
#include "UserComponents.hpp"

class UserSat : public Spacecraft
{
public:
  UserSat(SimulationConfig* sim_config, const GlobalEnvironment* glo_env, const int sat_id);
  void UserSat::Update(const SimTime* sim_time);
private:
};
