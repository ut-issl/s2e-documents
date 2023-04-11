# Naming Rule for User Interface

## Overview
This document describes the naming rule for user interface layer which includes `parameters in initialize files` and `variable names in CSV log files`. Since users directly access to the values, we need to care the readability more than the name of variables in codes.

### Common rules
- The names has following structure
  - Scalar values: `[name]_[unit]`
  - Vector or matrix values: `[name]_[frame]_[unit]`
  - If the value has no unit, we can remove the `[unit]` information.
- Variable name field: `[name]` 
  - It should be written as `snake_case`.
  - Single character abbreviations are prohibited.
    - Examples: `q = quaternion`, `v = velocity` are prohibited.
  - We do not recommend to use unfamiliar abbreviations.
    - Examples: `pos = position`, `quat = quaternion` are not recommended.
  - Available abbreviations are decided during review processes.
- Unit field: `[unit]`
  - For readability, we recommend to use general unit description in the SI unit system, and we do not need to follow the `snake_case` description in the unit field.
  - Examples: `Nm`, `rad/s`, `m/s2`, `degC`
- Frames
  - For readability, we recommend to use the following abbreviation in the unit field. When new abbreviation is needed for the frame description, please add it into the following list.
    - `i`: Inertial frame
    - `b`: Body fixed frame
    - `c`: Component fixed frame
    - `ecef`: Earth Centered Earth Fixed frame
    - `lvlh`: Local Vertical Local Horizontal
    - `rtn`: Radial-Transverse-Normal
  - To express the frame conversion, we can use `i2b` as `frame conversion from the inertial frame to the body-fixed frame`.
  - Note: The definition of origin of inertial frame is defined by the user settings. So sometimes we cannot use `eci = Earth Centered Inertial`.
  - The axis of the frame is described as `i_x, i_y, i_z`.

## Initialize files
- S2E uses `INI` format initialize files.
- `INI` has `Section` and `key` fields as follows
  ```
  [SECTION]
  key = value
  ```
- The `SECTION` field should be written as `SNAKE_CASE`
- The `key` fields should be written to follow the above `Common rules`.
- The axis of the frame is described as `(0), (1), (2)`, and they mean `X, Y, Z`
  - For quaternion `(0), (1), (2), (3)` is used as `X, Y, Z, W`.
  - TODO: Modify to use `X, Y, Z` directory?

## CSV log files
- S2E generates `CSV` format log files.
- The output file has the `variable names` in the first rows.
- The `variable names` should be written to follow the above `Common rules`.
- The unit is written in the brackets `[ ]` as `[N]`
