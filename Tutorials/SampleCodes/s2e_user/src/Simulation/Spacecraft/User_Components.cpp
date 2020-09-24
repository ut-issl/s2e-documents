#include "User_Components.h"

UserComponents::UserComponents(const Dynamics* dynamics, const SimulationConfig* config, ClockGenerator* clock_gen, const int sat_id)
  :dynamics_(dynamics), config_(config)
{
  obc_ = new OBC(clock_gen);
}

UserComponents::~UserComponents()
{
  delete obc_;
}

Vector<3> UserComponents::GenerateForce_b()
{
  //There is no orbit control component, so it remains 0
  Vector<3> force_b_(0.0);
  return force_b_;
};

Vector<3> UserComponents::GenerateTorque_b()
{
  //No attitude control component
  Vector<3> torque_b_(0.0);
  return torque_b_;
};

void UserComponents::CompoLogSetUp(Logger & logger)
{
}