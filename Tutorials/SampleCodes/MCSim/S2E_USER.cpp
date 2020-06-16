#ifdef WIN32
	#define _WINSOCKAPI_    // stops windows.h including winsock.h
	#include <windows.h>
#endif

#include <cstdio>
#include <iostream>
#include <string>
#include <cstdlib>

// Simulator includes
#include "Initialize.h"
#include "Logger.h"
#include "SimulationCase.h"

//Add custom include files
#include "./Simulation/Case/User_case.h"

// degub print of initialize file path
void print_path(std::string path)
{
#ifdef WIN32
  std::cout << path << std::endl;
#else
  const char *rpath = realpath(path.c_str(), NULL);
  if(rpath) {
    std::cout << rpath << std::endl;
    free((void *)rpath);
  }
#endif
}

// Main function
int main(int argc, char* argv[])
{
  //Set initialize file
  std::string ini_file = "../../data/ini/User_SimBase.ini";
  IniAccess iniAccess = IniAccess(ini_file);
  const string mc_file_path = iniAccess.ReadString("SIM_SETTING", "mcsim_file");
  MCSimExecutor* mc_sim = InitMCSim(mc_file_path);
  Logger *log_mc_sim = InitLogMC(ini_file, mc_sim->IsEnabled());

  std::cout << "Starting simulation..." << std::endl;
  std::cout << "\tIni file: "; print_path(ini_file);

  while (mc_sim->WillExecuteNextCase())
  {
    auto simcase = UserCase(ini_file, *mc_sim, log_mc_sim->GetLogPath());
    // Initialize
    log_mc_sim->AddLoggable(&simcase);
    if (mc_sim->GetNumOfExecutionsDone() == 0) log_mc_sim->WriteHeaders();
    simcase.Initialize();

    //Main
    log_mc_sim->WriteValues(); //write initial value
    simcase.Main();
    log_mc_sim->WriteValues(); //write final value
    log_mc_sim->ClearLoggables();
  }

  return EXIT_SUCCESS;
}
