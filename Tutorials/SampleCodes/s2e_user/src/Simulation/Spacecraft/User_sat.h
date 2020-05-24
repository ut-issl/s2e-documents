#pragma once

#include "Spacecraft.h"
#include "Disturbances.h"

class Envir;
class Disturbances;
class UserComponents;

class UserSat : public Spacecraft
{
public:
  UserSat(SimulationConfig config);
  ~UserSat();

  // 初期化
  virtual void Initialize();
  // ログ保存機能
  virtual void LogSetup(Logger& logger);
  // 状態量の更新
  virtual void Update();

private:
  Envir* environments_;
  Disturbances* disturbances_;
  UserComponents* components_;
};