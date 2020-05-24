## General Settings
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
project(S2E_USER)
# preprocessor
if(WIN32)
	add_definitions(-DWIN32)
endif()

## set directory path
set(S2E_CORE_DIR ../S2E_CORE_OSS)
set(CSPICE_DIR ../ExtLibraries/cspice)
set(FLIGHT_SW_DIR ../FlightSW)
set(C2A_DIR ${FLIGHT_SW_DIR}/C2A)

## options to use C2A
option(USE_C2A "Use C2A")
set(USE_C2A OFF)
if(USE_C2A)
  add_definitions(-DUSE_C2A)
  #include_directories
  include_directories(${C2A_DIR}/SH7254R_C2A/src/Core/AnomalyLogger)
  include_directories(${C2A_DIR}/SH7254R_C2A/src/Core/ApplicationManager)
  include_directories(${C2A_DIR}/SH7254R_C2A/src/Applications)
  include_directories(${C2A_DIR}/SH7254R_C2A/src/Core/TimeManager)
  include_directories(${C2A_DIR}/SH7254R_C2A/src/CmdTlm)
  include_directories(${C2A_DIR}/SH7254R_C2A/src/Core/ModeManager)
  include_directories(${C2A_DIR}/SH7254R_C2A/src/Core/TaskManager)
  include_directories(${C2A_DIR}/SH7254R_C2A/src/Core/WatchdogTimer)
  include_directories(${S2E_CORE_DIR}/src/Interface/SpacecraftInOut)
  #add subdirectory
  add_subdirectory(${C2A_DIR} C2A)
endif()

## include directories
include_directories(${CSPICE_DIR}/include)
include_directories(${S2E_CORE_DIR}/src/Library/math)
include_directories(${S2E_CORE_DIR}/src/Dynamics)
include_directories(${S2E_CORE_DIR}/src/Disturbance)
include_directories(${S2E_CORE_DIR}/src/Interface/InitInput)
include_directories(${S2E_CORE_DIR}/src/Interface/LogOutput)
include_directories(${S2E_CORE_DIR}/src/Simulation)
include_directories(${S2E_CORE_DIR}/src/Simulation/spacecraft)
include_directories(${S2E_CORE_DIR}/src/Simulation/Case)
include_directories(${S2E_CORE_DIR}/src/Disturbance)
include_directories(${S2E_CORE_DIR}/src/Environment)
include_directories(${S2E_CORE_DIR}/src/Component/Abstract)
include_directories(${S2E_CORE_DIR}/src/Component/AOCS)
include_directories(${S2E_CORE_DIR}/src/Component/CDH)
include_directories(${S2E_CORE_DIR}/src/Component/Power)
include_directories(${S2E_CORE_DIR}/src/Component/Propulsion)
include_directories(${S2E_CORE_DIR}/src/Component/Thermal)

## add_subdirectories
add_subdirectory(${S2E_CORE_DIR}/src/Component S2E_CORE/Component)
add_subdirectory(${S2E_CORE_DIR}/src/Disturbance S2E_CORE/Disturbance)
add_subdirectory(${S2E_CORE_DIR}/src/Dynamics S2E_CORE/Dynamics)
add_subdirectory(${S2E_CORE_DIR}/src/Environment S2E_CORE/Environment)
add_subdirectory(${S2E_CORE_DIR}/src/Interface/InitInput S2E_CORE/InitInput)
add_subdirectory(${S2E_CORE_DIR}/src/Interface/LogOutput S2E_CORE/LogOutput)
add_subdirectory(${S2E_CORE_DIR}/src/Interface/SpacecraftInOut S2E_CORE/SpacecraftInOut)
add_subdirectory(${S2E_CORE_DIR}/src/Library/igrf S2E_CORE/igrf)
add_subdirectory(${S2E_CORE_DIR}/src/Library/inih S2E_CORE/inih)
add_subdirectory(${S2E_CORE_DIR}/src/Library/math S2E_CORE/math)
add_subdirectory(${S2E_CORE_DIR}/src/Library/sgp4 S2E_CORE/sgp4)
add_subdirectory(${S2E_CORE_DIR}/src/Library/utils S2E_CORE/utils)
add_subdirectory(${S2E_CORE_DIR}/src/Simulation S2E_CORE/Simulation)

set(SOURCE_FILES
		src/S2E_USER.cpp
        src/Simulation/Case/User_case.cpp
        src/Simulation/Spacecraft/User_sat.cpp
        src/Simulation/Spacecraft/User_Components.cpp
)
# Create executable file
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
# Compile option
if(MSVC)
    target_compile_options(${PROJECT_NAME} PUBLIC "/W4")
	target_compile_options(${PROJECT_NAME} PUBLIC "/source-charset:utf-8")
else()
    target_compile_options(${PROJECT_NAME} PUBLIC "${CMAKE_CXX_FLAGS} -Wall")
endif()

## Linking libraries
## components
target_link_libraries(${PROJECT_NAME} COMPONENT)
## dynamics, environment, disturbance
target_link_libraries(${PROJECT_NAME} DYNAMICS ENVIRONMENT DISTURBANCE)
## Interface
target_link_libraries(${PROJECT_NAME} INI_IN INI_ACC LOG_OUT SC_IO)
## Library
target_link_libraries(${PROJECT_NAME} IGRF INIH MATH SGP4 UTIL)
## simulation
target_link_libraries(${PROJECT_NAME} SIMULATION)

## cspice library
if(CYGWIN)
  SET (CMAKE_FIND_LIBRARY_SUFFIXES ".so" ".a")
  find_library(CSPICE_LIB
    NAMES cspice.a csupport.a
    PATHS ${CSPICE_DIR}/cspice_cygwin/lib)
elseif(UNIX)
  find_library(CSPICE_LIB
    NAMES cspice.a csupport.a
    PATHS ${CSPICE_DIR}/cspice_unix/lib)
elseif(WIN32)
  SET (CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
  find_library(CSPICE_LIB
    NAMES cspice.lib csupport.lib
    PATHS ${CSPICE_DIR}/cspice_msvs/lib)
endif()
target_link_libraries(${PROJECT_NAME} ${CSPICE_LIB})
message("Cspice_LIB:  "${CSPICE_LIB})

## C2A integration
if(USE_C2A)
  target_link_libraries(${PROJECT_NAME} C2A)
endif()