#include "User_case.h"
#include "Initialize.h"
#include "SimulationConfig.h"
#include "../Spacecraft/User_sat.h"

UserCase::UserCase(string ini_fname, MCSimExecutor& mc_sim, string log_path)
  :ini_fname(ini_fname), mc_sim_(mc_sim), log_path_(log_path)
{
}

UserCase::~UserCase()
{
  delete sim_time;
  delete default_log;
  delete spacecraft;
}

void UserCase::Initialize()
{
  //Setting simulation condition
	sim_time = InitSimTime(ini_fname);  //simulation time
  string log_file_name = "default" + to_string(mc_sim_.GetNumOfExecutionsDone()) + ".csv";
  default_log = new Logger(log_file_name, log_path_, ini_fname, false, mc_sim_.LogHistory());
  SimulationConfig config = {ini_fname, sim_time, default_log};  //config

  //Instantiation
  spacecraft = new UserSat(config);

  //Monte Carlo Simulation
  mc_sim_.SetSeed();
  mc_sim_.RandomizeAllParameters();
  SimulationObject::SetAllParameters(mc_sim_);
  mc_sim_.AtTheBeginningOfEachCase();
  
  //Register log output
  default_log->AddLoggable(sim_time);
  spacecraft->LogSetup(*default_log);

  //Write Log headers
  default_log->WriteHeaders();

  //Start simulation
  cout << "\nSimulationDateTime \n";
  sim_time->PrintStartDateTime();
}

void UserCase::Main()
{
  sim_time->ResetClock();
  while (!sim_time->GetState().finish)
  {
    //logging
    if (sim_time->GetState().log_output) default_log->WriteValues();
    // Update Time
    sim_time->UpdateTime();
    // Update spacecraft dynamics and components
    spacecraft->Update();
    // debug output
    if (sim_time->GetState().disp_output)
    {
      cout << "Progresss: " << sim_time->GetProgressionRate() << "%\r";
    }
  }
  //MC finish
  mc_sim_.AtTheEndOfEachCase();
}

string UserCase::GetLogHeader() const
{
  string str_tmp = "";
  str_tmp += WriteScalar("time", "s");
  str_tmp += WriteVector("Omega", "b", "rad/s", 3);
  str_tmp += WriteVector("quat", "i2b", "-", 4);

  return str_tmp;
}

string UserCase::GetLogValue() const
{
  string str_tmp = "";
  str_tmp += WriteScalar(sim_time->GetElapsedSec());
  str_tmp += WriteVector(spacecraft->dynamics_->GetAttitude().GetOmega_b(), 3);
  str_tmp += WriteQuaternion(spacecraft->dynamics_->GetAttitude().GetQuaternion_i2b());
  return str_tmp;
}
