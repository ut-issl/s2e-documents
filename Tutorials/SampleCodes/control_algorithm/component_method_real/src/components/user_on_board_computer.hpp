/**
 * @file user_on_board_computer.hpp
 * @brief User defined on board computer
 */

#ifndef S2E_COMPONENTS_USER_ON_BOARD_COMPUTER_HPP_
#define S2E_COMPONENTS_USER_ON_BOARD_COMPUTER_HPP_

#include <components/base/component.hpp>
#include <library/math/vector.hpp>

#include "../simulation/spacecraft/user_components.hpp"

class UserComponents;

/*
 * @class UserOnBoardComputer
 * @brief Class to emulate user defined on board computer
 */
class UserOnBoardComputer : public Component {
 public:
  /**
   * @fn UserOnBoardComputer
   * @brief Constructor
   * @param [in] clock_generator: Clock generator
   * @param [in] components: Component list
   */
  UserOnBoardComputer(ClockGenerator* clock_generator, UserComponents& components);

  /**
   * @fn ~UserOnBoardComputer
   * @brief Destructor
   */
  ~UserOnBoardComputer();

 protected:
  UserComponents& components_;  //!< Component list

  /**
   * @fn MainRoutine
   * @brief Override Component::Main function
   */
  void MainRoutine(const int time_count);
};

#endif  // S2E_COMPONENTS_USER_ON_BOARD_COMPUTER_HPP_
