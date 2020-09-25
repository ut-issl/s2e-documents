#include "User_case.h"
#include "Initialize.h"

UserCase::UserCase(string ini_fname):SimulationCase(ini_fname)
{
}

UserCase::~UserCase()
{
  delete spacecraft_;
}

void UserCase::Initialize()
{
  //Instantiate the target of the simulation
  const int sat_id = 0;//`sat_id=0` corresponds to the index of `sat_file` in Simbase.ini
  spacecraft_ = new UserSat(&sim_config_, glo_env_, sat_id); 

  //Register the log output
  glo_env_->LogSetup(*(sim_config_.main_logger_));
  spacecraft_->LogSetup(*(sim_config_.main_logger_));

  //Write headers to the log
  sim_config_.main_logger_->WriteHeaders();

  //Start the simulation
  cout << "\nSimulationDateTime \n";
  glo_env_->GetSimTime().PrintStartDateTime();

}

void UserCase::Main()
{
  glo_env_->Reset(); //for MonteCarlo Sim
  while (!glo_env_->GetSimTime().GetState().finish)
  {
    //Logging
    if (glo_env_->GetSimTime().GetState().log_output)
    {
      sim_config_.main_logger_->WriteValues();
    }
    // Global Environment Update
    glo_env_->Update();
    // Spacecraft Update
    spacecraft_->Clear(); //Zero clear force and torque for dynamics
    spacecraft_->Update(&(glo_env_->GetSimTime()));
    // Debug output
    if (glo_env_->GetSimTime().GetState().disp_output)
    {
      cout << "Progresss: " << glo_env_->GetSimTime().GetProgressionRate() << "%\r";
    }
  }
}

string UserCase::GetLogHeader() const
{
  string str_tmp = "";

  return str_tmp;
}

string UserCase::GetLogValue() const
{
  string str_tmp = "";

  return str_tmp;
}
