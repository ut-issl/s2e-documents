#pragma once

#include "SimulationCase.h"
#include "../Spacecraft/UserSat.hpp"

class UserCase: public SimulationCase
{
public:
  UserCase(std::string ini_fname);
  virtual ~UserCase();
  
  void Initialize();
  void Main();

  virtual std::string GetLogHeader() const;
  virtual std::string GetLogValue() const;

private:
  UserSat* spacecraft_;
};
