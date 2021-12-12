#pragma once

#include "Vector.hpp"
#include "Dynamics.h"
#include "GlobalEnvironment.h"
#include "LocalEnvironment.h"

// include for component
#include "OBC_C2A.h"
#include "../../../Component/Abstract/EXP.h"

class OBC_C2A;
class EXP;

class UserComponents
{
public:
  UserComponents(
    const Dynamics* dynamics, 
    const Structure* structure, 
    const LocalEnvironment* local_env, 
    const GlobalEnvironment* glo_env,
    const SimulationConfig* config,
    ClockGenerator* clock_gen,
    const int sat_id
  );
  ~UserComponents();
  libra::Vector<3> GenerateForce_b();
  libra::Vector<3> GenerateTorque_b();
  void CompoLogSetUp(Logger& logger);
private:
  OBC_C2A* obc_;
  EXP *exp_;
};
