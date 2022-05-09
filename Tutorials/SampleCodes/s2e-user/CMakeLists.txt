## General Settings
cmake_minimum_required(VERSION 3.13)
project(S2E_USER)
set(CMAKE_CXX_STANDARD 14)
# preprocessor
if(WIN32)
  add_definitions(-DWIN32)
endif()

## set directory path
set(S2E_CORE_DIR ../s2e-core)
set(CSPICE_DIR ../ExtLibraries/cspice)
set(NRLMSISE00_DIR ../ExtLibraries/nrlmsise00)
set(FLIGHT_SW_DIR ../FlightSW)
set(C2A_DIR ${FLIGHT_SW_DIR}/c2a_user_oss)

if(WIN32)
elseif(APPLE)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./out)  # set build path
endif()

## Options to use C2A
option(USE_C2A "Use C2A")
set(USE_C2A OFF)
if(USE_C2A)
  # add definition
  add_definitions(-DUSE_C2A)
  add_definitions(-DSILS_FW)
  
  # include_directories of C2A
  include_directories(${C2A_DIR}/src/src_core/System/AnomalyLogger)
  include_directories(${C2A_DIR}/src/src_core/System/ApplicationManager)
  include_directories(${C2A_DIR}/src/src_core/System/ModeManager)
  include_directories(${C2A_DIR}/src/src_core/System/TaskManager)
  include_directories(${C2A_DIR}/src/src_core/System/WatchdogTimer)
  include_directories(${C2A_DIR}/src/src_core/System/TimeManager)
  include_directories(${C2A_DIR}/src/src_core/CmdTlm)
  include_directories(${C2A_DIR}/src/src_user/Applications)
  include_directories(${C2A_DIR}/src)
  include_directories(${S2E_CORE_DIR}/src/Interface/SpacecraftInOut)
  
  # add subdirectory
  add_subdirectory(${C2A_DIR} C2A_CORE)
  
  message("USE C2A")
endif()

## Options to use HILS
option(USE_HILS "Use HILS")
set(USE_HILS OFF)
if(USE_HILS AND WIN32)
  add_definitions(-DUSE_HILS)
  ## winsock2
  SET (CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
  find_library(WS2_32_LIB ws2_32.lib)
  message("path for winsock2 is")
  message(${WS2_32_LIB})
endif()

## include directories of S2E_CORE
include_directories(${CSPICE_DIR}/include)
include_directories(${NRLMSISE00_DIR}/src)
include_directories(${S2E_CORE_DIR}/src/Library/math)
include_directories(${S2E_CORE_DIR}/src/Dynamics)
include_directories(${S2E_CORE_DIR}/src/Disturbance)
include_directories(${S2E_CORE_DIR}/src/Interface/InitInput)
include_directories(${S2E_CORE_DIR}/src/Interface/LogOutput)
include_directories(${S2E_CORE_DIR}/src/Simulation)
include_directories(${S2E_CORE_DIR}/src/Simulation/MCSim)
include_directories(${S2E_CORE_DIR}/src/Simulation/Spacecraft)
include_directories(${S2E_CORE_DIR}/src/Simulation/Spacecraft/Structure)
include_directories(${S2E_CORE_DIR}/src/Simulation/GroundStation)
include_directories(${S2E_CORE_DIR}/src/Simulation/Case)
include_directories(${S2E_CORE_DIR}/src/Disturbance)
include_directories(${S2E_CORE_DIR}/src/Environment/Global)
include_directories(${S2E_CORE_DIR}/src/Environment/Local)
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
  target_compile_options(${PROJECT_NAME} PUBLIC "${CMAKE_CXX_FLAGS}-Wall")
  set(CMAKE_CXX_FLAGS "-m32 -rdynamic -Wall -g")
  set(CMAKE_C_FLAGS "-m32 -rdynamic -Wall -g")
endif()

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

## nrlmsise00 library
if(CYGWIN)
  SET (CMAKE_FIND_LIBRARY_SUFFIXES ".a")
  find_library(NRLMSISE00_LIB 
    NAMES libnrlmsise00.a
    PATHS ${NRLMSISE00_DIR}/lib)
elseif(UNIX)
  find_library(NRLMSISE00_LIB 
    NAMES libnrlmsise00.a
    PATHS ${NRLMSISE00_DIR}/lib)
elseif(WIN32)
  SET (CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
  find_library(NRLMSISE00_LIB 
    NAMES libnrlmsise00.lib
    PATHS ${NRLMSISE00_DIR}/lib)
endif()

## Linking libraries
set(S2E_LIBRARIES
  IGRF WRAPPER_NRLMSISE00 INIH MATH SGP4 UTIL OPTICS RELATIVE_ORBIT_MODELS
)
# Initialize link
target_link_libraries(COMPONENT INTERFACE INI_IN DYNAMICS GLOBAL_ENVIRONMENT LOCAL_ENVIRONMENT SC_IO RELATIVE_INFO ${S2E_LIBRARIES})
target_link_libraries(DYNAMICS INTERFACE INI_IN GLOBAL_ENVIRONMENT LOCAL_ENVIRONMENT SIMULATION ${S2E_LIBRARIES})
target_link_libraries(DISTURBANCE INTERFACE INI_IN DYNAMICS GLOBAL_ENVIRONMENT LOCAL_ENVIRONMENT ${S2E_LIBRARIES})
target_link_libraries(SIMULATION INTERFACE INI_IN DYNAMICS GLOBAL_ENVIRONMENT LOCAL_ENVIRONMENT DISTURBANCE ${S2E_LIBRARIES})
target_link_libraries(GLOBAL_ENVIRONMENT INTERFACE INI_IN ${CSPICE_LIB} ${S2E_LIBRARIES})
target_link_libraries(LOCAL_ENVIRONMENT INTERFACE INI_IN GLOBAL_ENVIRONMENT ${CSPICE_LIB} ${S2E_LIBRARIES})
target_link_libraries(INI_IN INTERFACE DYNAMICS GLOBAL_ENVIRONMENT LOCAL_ENVIRONMENT ${S2E_LIBRARIES})
target_link_libraries(WRAPPER_NRLMSISE00 INTERFACE ${NRLMSISE00_LIB})

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
  set_target_properties(INI_IN PROPERTIES COMMON_LANGUAGE_RUNTIME "")
  set_target_properties(HILS_IO PROPERTIES COMMON_LANGUAGE_RUNTIME "")
  set_target_properties(RELATIVE_INFO PROPERTIES COMMON_LANGUAGE_RUNTIME "")
endif()

## Cmake debug
message("Cspice_LIB:  " ${CSPICE_LIB})
message("nrlmsise00_LIB:  " ${NRLMSISE00_LIB})
