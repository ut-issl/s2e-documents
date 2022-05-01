cmake_policy(SET CMP0048 NEW)
project(S2E_FOR_C2A_CORE
  LANGUAGES CXX
  DESCRIPTION "S2E_FOR_C2A_CORE"
  VERSION 1.0
)

cmake_minimum_required(VERSION 3.13)

# build config
option(USE_HILS "Use HILS" OFF)
option(USE_C2A "Use C2A" ON)

# preprocessor
if(WIN32)
  add_definitions(-DWIN32)
endif()

## set directory path
set(S2E_CORE_DIR ../s2e-core)
if(NOT DEFINED EXT_LIB_DIR)
  set(EXT_LIB_DIR ../ExtLibraries)
endif()
set(CSPICE_DIR ${EXT_LIB_DIR}/cspice)
set(NRLMSISE00_DIR ${EXT_LIB_DIR}/nrlmsise00)

if(NOT DEFINED FLIGHT_SW_DIR)
  set(FLIGHT_SW_DIR ../FlightSW)
endif()
if(NOT DEFINED C2A_NAME)
  set(C2A_NAME "c2a-core/Examples/minimum_user_for_s2e")
endif()

## options to use C2A
if(USE_C2A)
  set(C2A_DIR ${FLIGHT_SW_DIR}/${C2A_NAME})
  message("C2A dir: ${C2A_DIR}")
  add_definitions(-DUSE_C2A)
  add_definitions(-DSILS_FW)
  #include_directories of C2A
  include_directories(${C2A_DIR}/src)
  include_directories(${S2E_CORE_DIR}/src/Interface/SpacecraftInOut)

  #add subdirectory
  set(BUILD_C2A_AS_CXX ON)
  add_subdirectory(${C2A_DIR} C2A)
endif()

## options to use HILS
if(USE_HILS AND WIN32)
  add_definitions(-DUSE_HILS)
  ## winsock2
  SET (CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
  find_library(WS2_32_LIB ws2_32.lib)
  message("path for winsock2 is")
  message(${WS2_32_LIB})
endif()

set(S2E_DIR ${CMAKE_CURRENT_COURCE_DIR})

## include directories of S2E-CORE
include_directories(${CSPICE_DIR}/include)
include_directories(${NRLMSISE00_DIR}/src)
include_directories(${S2E_CORE_DIR}/src)
include_directories(${S2E_CORE_DIR}/src/Library/math)
include_directories(${S2E_CORE_DIR}/src/Library/utils)
include_directories(${S2E_CORE_DIR}/src/Dynamics)
include_directories(${S2E_CORE_DIR}/src/Disturbance)
include_directories(${S2E_CORE_DIR}/src/Interface/InitInput)
include_directories(${S2E_CORE_DIR}/src/Interface/LogOutput)
include_directories(${S2E_CORE_DIR}/src/Interface/SpacecraftInOut/Ports)
include_directories(${S2E_CORE_DIR}/src/Simulation)
include_directories(${S2E_CORE_DIR}/src/Simulation/MCSim)
include_directories(${S2E_CORE_DIR}/src/Simulation/Spacecraft)
include_directories(${S2E_CORE_DIR}/src/Simulation/Spacecraft/Structure)
include_directories(${S2E_CORE_DIR}/src/Simulation/GroundStation)
include_directories(${S2E_CORE_DIR}/src/Simulation/Case)
include_directories(${S2E_CORE_DIR}/src/Disturbance)
include_directories(${S2E_CORE_DIR}/src/Environment/Global)
include_directories(${S2E_CORE_DIR}/src/Environment/Local)
include_directories(${S2E_CORE_DIR}/src/Component)
include_directories(${S2E_CORE_DIR}/src/Component/Abstract)
include_directories(${S2E_CORE_DIR}/src/Component/AOCS)
include_directories(${S2E_CORE_DIR}/src/Component/CDH)
include_directories(${S2E_CORE_DIR}/src/Component/CommGS)
include_directories(${S2E_CORE_DIR}/src/Component/Mission/Telescope)
include_directories(${S2E_CORE_DIR}/src/Component/Power)
include_directories(${S2E_CORE_DIR}/src/Component/Propulsion)
include_directories(${S2E_CORE_DIR}/src/Component/Thermal)

## add_subdirectories
add_subdirectory(${S2E_CORE_DIR}/src/Component S2E_CORE/Component)
add_subdirectory(${S2E_CORE_DIR}/src/Disturbance S2E_CORE/Disturbance)
add_subdirectory(${S2E_CORE_DIR}/src/Dynamics S2E_CORE/Dynamics)
add_subdirectory(${S2E_CORE_DIR}/src/Environment/Global S2E_CORE/Environment/Global)
add_subdirectory(${S2E_CORE_DIR}/src/Environment/Local S2E_CORE/Environment/Local)
add_subdirectory(${S2E_CORE_DIR}/src/RelativeInformation S2E_CORE/RelativeInformation)
add_subdirectory(${S2E_CORE_DIR}/src/Interface/InitInput S2E_CORE/InitInput)
add_subdirectory(${S2E_CORE_DIR}/src/Interface/LogOutput S2E_CORE/LogOutput)
add_subdirectory(${S2E_CORE_DIR}/src/Interface/SpacecraftInOut S2E_CORE/SpacecraftInOut)
add_subdirectory(${S2E_CORE_DIR}/src/Interface/HilsInOut S2E_CORE/HilsInOut)
add_subdirectory(${S2E_CORE_DIR}/src/Library/igrf S2E_CORE/igrf)
add_subdirectory(${S2E_CORE_DIR}/src/Library/inih S2E_CORE/inih)
add_subdirectory(${S2E_CORE_DIR}/src/Library/math S2E_CORE/math)
add_subdirectory(${S2E_CORE_DIR}/src/Library/nrlmsise00 S2E_CORE/nrlmsise00)
add_subdirectory(${S2E_CORE_DIR}/src/Library/sgp4 S2E_CORE/sgp4)
add_subdirectory(${S2E_CORE_DIR}/src/Library/utils S2E_CORE/utils)
add_subdirectory(${S2E_CORE_DIR}/src/Library/optics S2E_CORE/optics)
add_subdirectory(${S2E_CORE_DIR}/src/Library/RelativeOrbit S2E_CORE/RelativeOrbit)
add_subdirectory(${S2E_CORE_DIR}/src/Library/Orbit S2E_CORE/Orbit)
add_subdirectory(${S2E_CORE_DIR}/src/Library/Geodesy S2E_CORE/Geodesy)
add_subdirectory(${S2E_CORE_DIR}/src/Simulation S2E_CORE/Simulation)

set(SOURCE_FILES
  src/s2e_for_c2a_core.cpp
  src/Simulation/Case/c2a_core_sample_case.cpp
  src/Simulation/Spacecraft/c2a_core_sample_sat.cpp
  src/Simulation/Spacecraft/c2a_core_sample_components.cpp
)
# Create executable file
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

## cspice library
if(CYGWIN)
  SET (CMAKE_FIND_LIBRARY_SUFFIXES ".so" ".a")
  find_library(CSPICE_LIB
    NAMES cspice.a csupport.a
    PATHS ${CSPICE_DIR}/cspice_cygwin/lib
  )
elseif(UNIX)
  find_library(CSPICE_LIB
    NAMES cspice.a csupport.a
    PATHS ${CSPICE_DIR}/cspice_unix/lib
  )
elseif(WIN32)
  SET (CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
  find_library(CSPICE_LIB
    NAMES cspice.lib csupport.lib
    PATHS ${CSPICE_DIR}/cspice_msvs/lib
  )
endif()
if(NOT CSPICE_LIB)
  message(FATAL_ERROR "cspice not found in ${EXT_LIB_DIR}")
endif()

## nrlmsise00 library
if(CYGWIN)
  SET (CMAKE_FIND_LIBRARY_SUFFIXES ".a")
  find_library(NRLMSISE00_LIB
    NAMES libnrlmsise00.a
    PATHS ${NRLMSISE00_DIR}/lib
  )
elseif(UNIX)
  find_library(NRLMSISE00_LIB
    NAMES libnrlmsise00.a
    PATHS ${NRLMSISE00_DIR}/lib
  )
elseif(WIN32)
  SET (CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
  find_library(NRLMSISE00_LIB
    NAMES libnrlmsise00.lib
    PATHS ${NRLMSISE00_DIR}/lib
  )
endif()
if(NOT NRLMSISE00_LIB)
  message(FATAL_ERROR "nrlmsise00 not found in ${EXT_LIB_DIR}")
endif()

## Linking libraries
set(S2E_LIBRARIES
  IGRF WRAPPER_NRLMSISE00 INIH SGP4 UTIL OPTICS RELATIVE_ORBIT_MODELS ORBIT_MODELS GEODESY MATH
)
# Initialize link
target_link_libraries(COMPONENT DYNAMICS GLOBAL_ENVIRONMENT LOCAL_ENVIRONMENT SC_IO RELATIVE_INFO ${S2E_LIBRARIES})
target_link_libraries(DYNAMICS GLOBAL_ENVIRONMENT LOCAL_ENVIRONMENT SIMULATION ${S2E_LIBRARIES})
target_link_libraries(DISTURBANCE DYNAMICS GLOBAL_ENVIRONMENT LOCAL_ENVIRONMENT ${S2E_LIBRARIES})
target_link_libraries(SIMULATION DYNAMICS GLOBAL_ENVIRONMENT LOCAL_ENVIRONMENT DISTURBANCE ${S2E_LIBRARIES})
target_link_libraries(GLOBAL_ENVIRONMENT ${CSPICE_LIB} ${S2E_LIBRARIES})
target_link_libraries(LOCAL_ENVIRONMENT GLOBAL_ENVIRONMENT ${CSPICE_LIB} ${S2E_LIBRARIES})
target_link_libraries(WRAPPER_NRLMSISE00 ${NRLMSISE00_LIB})

target_link_libraries(${PROJECT_NAME} DYNAMICS)
target_link_libraries(${PROJECT_NAME} DISTURBANCE)
target_link_libraries(${PROJECT_NAME} SIMULATION)
target_link_libraries(${PROJECT_NAME} GLOBAL_ENVIRONMENT LOCAL_ENVIRONMENT)
target_link_libraries(${PROJECT_NAME} RELATIVE_INFO)
target_link_libraries(${PROJECT_NAME} INI_ACC LOG_OUT SC_IO)
target_link_libraries(${PROJECT_NAME} COMPONENT)
target_link_libraries(${PROJECT_NAME} HILS_IO)

## C2A integration
if(USE_C2A)
  target_link_libraries(${PROJECT_NAME} C2A)
endif()

## HILS
if(USE_HILS)
  target_link_libraries(${PROJECT_NAME} ${WS2_32_LIB})
  set_target_properties(${PROJECT_NAME} PROPERTIES COMMON_LANGUAGE_RUNTIME "")
  set_target_properties(COMPONENT PROPERTIES COMMON_LANGUAGE_RUNTIME "")
  set_target_properties(DYNAMICS PROPERTIES COMMON_LANGUAGE_RUNTIME "")
  set_target_properties(DISTURBANCE PROPERTIES COMMON_LANGUAGE_RUNTIME "")
  set_target_properties(SIMULATION PROPERTIES COMMON_LANGUAGE_RUNTIME "")
  set_target_properties(GLOBAL_ENVIRONMENT PROPERTIES COMMON_LANGUAGE_RUNTIME "")
  set_target_properties(LOCAL_ENVIRONMENT PROPERTIES COMMON_LANGUAGE_RUNTIME "")
  set_target_properties(HILS_IO PROPERTIES COMMON_LANGUAGE_RUNTIME "")
  set_target_properties(RELATIVE_INFO PROPERTIES COMMON_LANGUAGE_RUNTIME "")
endif()

## Cmake debug
message("Cspice_LIB:  " ${CSPICE_LIB})
message("nrlmsise00_LIB:  " ${NRLMSISE00_LIB})

include(common.cmake)
