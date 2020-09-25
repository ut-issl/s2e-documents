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

  std::cout << "Starting simulation..." << std::endl;
  std::cout << "\tIni file: "; print_path(ini_file);

  auto simcase = UserCase(ini_file);
  simcase.Initialize();
  simcase.Main();

  return EXIT_SUCCESS;
}
