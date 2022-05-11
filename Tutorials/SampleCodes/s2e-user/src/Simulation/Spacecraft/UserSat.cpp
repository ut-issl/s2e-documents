#include "UserSat.hpp"
#include "UserComponents.hpp"

UserSat::UserSat(SimulationConfig* sim_config, const GlobalEnvironment* glo_env, const int sat_id)
:Spacecraft(sim_config, glo_env, sat_id)
{
  components_ = new UserComponents(dynamics_, structure_, local_env_, glo_env, sim_config, &clock_gen_);
}
