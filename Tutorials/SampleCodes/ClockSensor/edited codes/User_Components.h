#pragma once
#include "Vector.hpp"
#include "Dynamics.h"
#include "GlobalEnvironment.h"
#include "OBC.h"
#include "Gyro.h"
#include "../../Components/ClockSensor.h"

using libra::Vector;
class OBC;

class UserComponents
{
public:
  UserComponents(const Dynamics* dynamics, const GlobalEnvironment* glo_env, const SimulationConfig* config, ClockGenerator* clock_gen, const int sat_id);
  ~UserComponents();
  Vector<3> GenerateForce_b();
  Vector<3> GenerateTorque_b();
  void CompoLogSetUp(Logger& logger);
private:
  OBC* obc_;
  ClockSensor* clock_sensor_;
};