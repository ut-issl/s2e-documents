#pragma once
#include "Vector.hpp"
#include "Dynamics.h"
#include "GlobalEnvironment.h"
#include "../../Components/User_OBC.h"
#include "Gyro.h"
#include "RWModel.h"

using libra::Vector;

class UserComponents
{
public:
  UserComponents(const Dynamics* dynamics, const GlobalEnvironment* glo_env, const SimulationConfig* config, ClockGenerator* clock_gen, const int sat_id);
  ~UserComponents();
  Vector<3> GenerateForce_b();
  Vector<3> GenerateTorque_b();
  void CompoLogSetUp(Logger& logger);

  //Getter
  inline Gyro& GetGyro(){ return *gyro_; }
  inline RWModel& GetRw(){ return *rw_; }
private:
  UserOBC* obc_;
  Gyro* gyro_;
  RWModel* rw_;
};