#pragma once

#include <Simulation/Spacecraft/InstalledComponents.hpp>

#include "Dynamics.h"
#include "GlobalEnvironment.h"
#include "LocalEnvironment.h"
#include "Vector.hpp"

// include for components
#include "../../Components/UserObc.hpp"
#include "InitGyro.hpp"
#include "InitRwModel.hpp"


class UserComponents : public InstalledComponents
{
public:
  UserComponents(
    const Dynamics* dynamics, 
    const Structure* structure, 
    const LocalEnvironment* local_env, 
    const GlobalEnvironment* glo_env,
    const SimulationConfig* config,
    ClockGenerator* clock_gen
  );
  ~UserComponents();
  libra::Vector<3> GenerateForce_N_b();
  libra::Vector<3> GenerateTorque_Nm_b();
  void LogSetup(Logger& logger);
  //Getter
  inline Gyro& GetGyro(){ return *gyro_; }
  inline RWModel& GetRw(){ return *rw_; }

private:
  // Components
  UserObc* obc_;
  Gyro* gyro_;
  RWModel* rw_;

  // References
  const Dynamics* dynamics_;
  const Structure* structure_;
  const LocalEnvironment* local_env_;
  const GlobalEnvironment* glo_env_;
  const SimulationConfig* config_;
};
