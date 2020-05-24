#include "User_case.h"
#include "Initialize.h"
#include "SimulationConfig.h"
#include "Disturbances.h"
#include "Environment.h"
#include "../Spacecraft/User_sat.h"

UserCase::UserCase(string ini_fname)
  : ini_fname(ini_fname)
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
  default_log = InitLog(ini_fname);  // file name of log output
  SimulationConfig config = {ini_fname, sim_time, default_log};  //config

  //Instantiation
  spacecraft = new UserSat(config);
  
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
}

//TODO log definition in Simulation Case is not necessary?
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
