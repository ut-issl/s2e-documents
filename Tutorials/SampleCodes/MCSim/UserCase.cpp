#include "UserCase.hpp"
#include "SimulationObject.h"

UserCase::UserCase(std::string ini_fname, MCSimExecutor& mc_sim, const std::string log_path)
: SimulationCase(ini_fname,mc_sim,log_path), mc_sim_(mc_sim)
{
}

UserCase::~UserCase()
{
  delete spacecraft_;
}

void UserCase::Initialize()
{
  // Instantiate the target of the simulation
  const int sat_id = 0;// `sat_id=0` corresponds to the index of `sat_file` in Simbase.ini
  spacecraft_ = new UserSat(&sim_config_, glo_env_, sat_id); 

  // Monte Carlo Simulation
  mc_sim_.SetSeed();
  mc_sim_.RandomizeAllParameters();
  SimulationObject::SetAllParameters(mc_sim_);
  mc_sim_.AtTheBeginningOfEachCase();

  // Register the log output
  glo_env_->LogSetup(*(sim_config_.main_logger_));
  spacecraft_->LogSetup(*(sim_config_.main_logger_));

  // Write headers to the log
  sim_config_.main_logger_->WriteHeaders();

  // Start the simulation
  std::cout << "\nSimulationDateTime \n";
  glo_env_->GetSimTime().PrintStartDateTime();

}

void UserCase::Main()
{
  glo_env_->Reset(); // for MonteCarlo Sim
  while (!glo_env_->GetSimTime().GetState().finish)
  {
    // Logging
    if (glo_env_->GetSimTime().GetState().log_output)
    {
      sim_config_.main_logger_->WriteValues();
    }
    // Global Environment Update
    glo_env_->Update();
    // Spacecraft Update
    spacecraft_->Update(&(glo_env_->GetSimTime()));
    // Debug output
    if (glo_env_->GetSimTime().GetState().disp_output)
    {
      std::cout << "Progresss: " << glo_env_->GetSimTime().GetProgressionRate() << "%\r";
    }
  }
  mc_sim_.AtTheEndOfEachCase();
}

std::string UserCase::GetLogHeader() const
{
  std::string str_tmp = "";
  str_tmp += WriteScalar("time", "s");
  str_tmp += WriteVector("Omega", "b", "rad/s", 3);
  str_tmp += WriteVector("Quaternion", "i2b", "-", 4);
  return str_tmp;
}
std::string UserCase::GetLogValue() const
{
  std::string str_tmp = "";
  str_tmp += WriteScalar(glo_env_->GetSimTime().GetElapsedSec());
  str_tmp += WriteVector(spacecraft_->GetDynamics().GetAttitude().GetOmega_b(), 3);
  str_tmp += WriteQuaternion(spacecraft_->GetDynamics().GetAttitude().GetQuaternion_i2b());
  return str_tmp;
}
