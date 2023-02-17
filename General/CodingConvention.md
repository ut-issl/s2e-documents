# Coding Convention of S2E

## Fomatter
- We use [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) for S2E. 
  - We selected `Google` base style with small modifications.
  - Details are written in [.clang-format](https://github.com/ut-issl/s2e-core/blob/develop/.clang-format).


## Naming Rules
- Now discussing
  - The following rules are follows until the new naming rule is decided.
  - Several old files do not follow the rules.
  - We are discussing follow the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) with small modifications.

- File and directory Name
  - `snake_case`
  - C++ files should end in `.cpp`, and header files should end in `.hpp`.

- Macro (define)
  - Snake case with capital case
  - `SNAKE_CASE`

- Name of the class
  - `CamelCase`

- Variable name
  - Snake case with lower case
  - `snake_case`

- Constant name (not a define but a constant)
  - Add k at the beginning and the rest is CamelCase
  - `kCamelCase`

- Member variables in the class
  - Snake case with lower case end with `_`
  - `snake_case_`

- Methods (functions) in the class
  - `CamelCase`

- The #define Guard
  - Apply [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).
  - `#pragma once` is prohibited

## Documentation
- Use Doxygen
- Use Markdown for Doxygen
- Examples:
  - https://developer.lsst.io/cpp/api-docs.html


## Initialization files (`.ini` files)
- Comments
  - Use //

## Abbreviations 
- Basically, we follows the [Naming Rules in the Google Style Guide](https://google.github.io/styleguide/cppguide.html#General_Naming_Rules)
- Single character abbreviations are prohibited.
  - Examples: `q = quaternion`, `v = velocity` are prohibited.
- We do not recommend to use abbreviations for one word cutting the word.
  - Examples: `pos = position`, `quat = quaternion` are not recommended.
  - The following abbreviations are available as exceptions since they are widely used in the math, science, and technology field.
    - `max`: maximum
    - `min`: minimum
    - `init`: initial, initialize
    - `calc`: calculate, calculation
- Abbreviation only file name is not recommended.
  - Examples
    - `ode.hpp` should be written as `ordinary_differential_equation.hpp`
    - `gnssr.hpp` is not recommended, but `gnss_receiver.hpp` is available since we can guess the abbreviation meaning from the context.
- Write the full words in the comment when you use abbreviations.
- Available abbreviations are decided during review processes.
  - Examples of available abbreviations with comments
    - `EKF`: Extended Kalman Filter
    - `GNSS`: Global Navigation Satellite System
- Abbreviations to show the frame and the unit are available.
  - Examples of frame
    - `i`: Inertial frame
    - `b`: Body fixed frame
    - `c`: Component fixed frame
    - `ecef`: Earth Centered Earth Fixed frame
    - `lvlh`: Local Vertical Local Horizontal
    - `rtn`: Radial-Transverse-Normal
  - Examples of unit: `Nm`, `rad/s`, `m/s2`, `degC`
- Available abbreviations 
  - `S2E`: Spacecraft Simulation Environment
  - `AOCS`: Attitude and Orbit Control System
  - `CDH`: Command and Data Handling
