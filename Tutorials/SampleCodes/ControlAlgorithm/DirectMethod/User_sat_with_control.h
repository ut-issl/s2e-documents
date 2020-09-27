#pragma once

#include "Spacecraft.h"

class UserComponents;

class UserSat : public Spacecraft
{
public:
  UserSat(SimulationConfig* sim_config, const GlobalEnvironment* glo_env, const int sat_id);
  ~UserSat();

  // 初期化
  virtual void Initialize(void);
  // ログ保存機能
  virtual void LogSetup(Logger& logger);
  // 状態量の更新
  virtual void Update(const SimTime* sim_time);

private:
};