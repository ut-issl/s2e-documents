// Simulator includes
#include <Simulation/MCSim/InitMcSim.hpp>
#include <Interface/LogOutput/InitLog.hpp>

// Add custom include files
#include "./Simulation/Case/UserCase.hpp"

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
int main()
{
  // Set initialize file
  std::string ini_file = "../../data/ini/UserSimBase.ini";
  MCSimExecutor* mc_sim = InitMCSim(ini_file);
  Logger *log_mc_sim = InitLogMC(ini_file, mc_sim->IsEnabled());

  std::cout << "Starting simulation..." << std::endl;
  std::cout << "\tIni file: ";
  print_path(ini_file);

  while (mc_sim->WillExecuteNextCase())
  {
    auto simcase = UserCase(ini_file, *mc_sim, log_mc_sim->GetLogPath());
    // Initialize
    log_mc_sim->AddLoggable(&simcase);
    if (mc_sim->GetNumOfExecutionsDone() == 0) log_mc_sim->WriteHeaders();
    simcase.Initialize();

    // Main
    log_mc_sim->WriteValues(); // log initial value
    simcase.Main();
    log_mc_sim->WriteValues(); // log final value
    log_mc_sim->ClearLoggables();
  }

  delete log_mc_sim;
  delete mc_sim;

  return EXIT_SUCCESS;
}
