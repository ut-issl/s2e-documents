#pragma once
#include "Vector.hpp"
#include "Dynamics.h"
#include "OBC_C2A.h"
#include "../../../Component/Abstract/EXP.h"

using libra::Vector;
class OBC_C2A;
class EXP;

class UserComponents
{
public:
  UserComponents(const Dynamics* dynamics, const SimulationConfig* config, ClockGenerator* clock_gen, const int sat_id);
  ~UserComponents();
  Vector<3> GenerateForce_b();
  Vector<3> GenerateTorque_b();
  void CompoLogSetUp(Logger& logger);
private:
  OBC_C2A* obc_;
  EXP *exp_;
};