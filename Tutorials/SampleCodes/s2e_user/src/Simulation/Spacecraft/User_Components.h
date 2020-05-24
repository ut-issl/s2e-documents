#pragma once
#include "Vector.hpp"
#include "Dynamics.h"
#include "OBC.h"

using libra::Vector;
class OBC;

class UserComponents
{
public:
  UserComponents(const Dynamics* dynamics, const SimulationConfig* config);
  ~UserComponents();
  Vector<3> GenerateForce_b();
  Vector<3> GenerateTorque_b();
  void CompoLogSetUp(Logger& logger);
private:
  OBC* obc_;
  const SimulationConfig* config_;
  const Dynamics* dynamics_;
};