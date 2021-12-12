#pragma once

#include "Spacecraft.h"
#include "User_Components.h"

class UserSat : public Spacecraft
{
public:
  UserSat(SimulationConfig* sim_config, const GlobalEnvironment* glo_env, const int sat_id);
  ~UserSat();

  // 初期化
  virtual void Initialize(SimulationConfig* sim_config, const GlobalEnvironment* glo_env, const int sat_id);
  // ログ保存機能
  virtual void LogSetup(Logger& logger);
  // 状態量の更新
  virtual void Update(const SimTime* sim_time);

private:
  UserComponents* components_;
};
