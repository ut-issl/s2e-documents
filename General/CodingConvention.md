# Coding Convention of S2E

## Fomatter
- We use [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) for S2E. 
  - We selected `Google` base style with small modifications.
  - Details are written in [.clang-format](https://github.com/ut-issl/s2e-core/blob/develop/.clang-format).


## Naming Rules
- Now discussing
  - The following rules are follows until the new naming rule is decided.
  - Several old files do not follow the rules.

- File and directory Name
  - `CamelCase`

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


## Documentation
- Use Doxygen
- Use Markdown for Doxygen
- Examples:
  - https://developer.lsst.io/cpp/api-docs.html


## Initialization files (`.ini` files)
- Comments
  - Use //

## Abbreviations in codes
- Basically, we follows the [Naming Rules in the Google Style Guide](https://google.github.io/styleguide/cppguide.html#General_Naming_Rules)
- Single character abbreviations are restricted for wide scope variables.
  - Such as: `q = quaternion`, `v = velocity`, etc.
- Unfamiliar abbreviations are restricted for wide scope variables.
  - Such as: `pos = position`, `quat = quaternion`.
- Write the full name in the comment when you use abbreviations.
- Available abbreviations are decided during review processes.
  - Examples of available abbreviations
    - `EKF`: Extended Kalman Filter
    - `RW`: Reaction Wheel
    - `GNSS`: Global Navigation Satellite System
- Abbreviations to show the frame and the unit are available.
  - Examples of frame
    - `i`: Inertial frame
    - `b`: Body fixed frame
    - `c`: Component fixed frame
    - `ecef`: Earth Center Earth Fixed frame
    - `lvlh`: Local vertical Local Horizontal
    - `rtn`: Radial-Transverse-Normal
  - Examples of unit: `Nm`, `rad/s`, `m/s2`, `degC`
