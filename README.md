# S2E-Documents
## Overview

- This repository summarizes documents of [S2E (Spacecraft Simulation Environment)](https://github.com/ut-issl/s2e-core/).
- The branch construction
  - main
    - Documents for the latest stable version of s2e-core
      - Current version supports [s2e-core v6.0.0](https://github.com/ut-issl/s2e-core/releases/tag/v6.0.0)
    - The old versions are managed with `release/tag/v.*.*.*`
      - The release version number is compatible with s2e-core's version number
  - develop
    - Documents for the latest `develop` branch of s2e-core
    - This version is only for s2e-core developers
  - feature/branch-name
    - Writing documents before merge with the `develop`
  - hotfix/branch-name
    - Fix typos, misdescription, etc.
- If you have any questions or comments for S2E, feel free to ask us on the [discussions page of s2e-core](https://github.com/ut-issl/s2e-core/discussions).

## Index

1. General Information
   1. [Coding Convention of S2E](./General/CodingConvention.md)
   1. [Naming Rule for User Interface](./General/NamingRuleForUserInterface.md)
   1. [Format of S2E Documents](./General/DocumentFormat.md)
   1. Mandatory set up and How to Build the S2E  
	   1. [How to build with Visual Studio](./General/HowToCompileWithVisualStudio.md)
	   1. [How to build with Ubuntu in Docker](./General/HowToCompileWithUbuntuInDocker.md) for **both Windows and Mac** users
	   1. How to build with other compilers will be written
   1. Set up of External Libraries  
      **NOTE**: Currenly, this setting sequence is included in the mandatory setups described above. So users don't need to see the following documents.
      1. [How to download CSPICE Library](./General/HowToDwnloadCSPCElibrary.md)
	   1. [How to download and make NRLMSISE00 Library](./General/HowToDownloadNRLMSISE00library.md)
   1. Visulalization of Simulation Results
      1. [How to Visualize Simulation Results](./General/HowToVisualizeSimulationResults.md)
     

1. Tutorials  
   - We strongly recommend to sequencially follow the tutorials without external hardware at first.
   1. [Getting Started](./Tutorials/GettingStarted.md)
   - <details><summary> Tutorials without any external hardware </summary>

     1. [How To Make New Simulation Scenario](./Tutorials/HowToMakeNewSimulationScenario.md)
     1. [How To Add Components](./Tutorials/HowToAddComponents.md)
     1. [How To Make New Components](./Tutorials/HowToMakeNewComponents.md)
     1. [How To Use Monte Carlo Simulation](./Tutorials/HowToUseMonteCarloSimulation.md)
     1. [How To Add Control Algorithms](./Tutorials/HowToAddControlAlgorithms.md)
     1. [How To Integrate C2A](./Tutorials/HowToIntegrateC2A.md)
     1. [How To Simulate Multiple Satellites](./Tutorials/HowToSimulateMultipleSatellites.md)
     1. TBW

     </details>

   - <details><summary> Tutorials with external hardware for HILS test </summary>

     1. [How To Perform UART HILS Test](./Tutorials/HowToPerformUartHilsTest.md)
     1. [How To Perform I2C HILS Test](./Tutorials/HowToPerformI2cHilsTest.md)
     1. TBW

     </details>

1. Specifications
   1. [Overall Structure](./Specifications/OverallStructure/OverallStructure.md)

   1. <details><summary> Components </summary>
      
      - `components` directory manages source codes to emulate components mounted on spacecraft and ground stations.

      1. <details><summary> Base </summary>

         - `base` directory manages base classes which are inherited to make component classes.

         1. [Component](./Specifications/Component/Abstract/Spec_ComponentBase.md)
         1. GPIO Communication with OBC: TBW
         1. I2C Controller: TBW
         1. I2C Target Communication with OBC: TBW
         1. Interface GPIO Component: TBW
         1. Interface Tickable: TBW
         1. [Sensor](./Specifications/Component/Abstract/Spec_SensorBase.md)
         1. [UART Communication with OBC](./Specifications/Component/Abstract/Spec_ObcCommunicationBase.md)

         </details>

      1. <details><summary> Ports </summary>

         - `ports` directory manages source codes to emulate connection of components including communication and power ports.

         1. GPIO Port: TBW
         1. I2C Port: TBW
         1. [Power Port](./Specifications/Interface/Spec_PowerPort.md)
         1. UART Port: TBW
         1. HILS I2C Target Port
         1. HILS UART Port

         </details>

      1. <details><summary> Examples </summary>

         - `examples` directory manages example source codes to show how to make user defined components.
         - Please do not use these classes directory for your simulation analysis.

         1. Change structure: TBW
         1. I2C controller for HILS: TBW
         1. I2C target for HILS: TBW
         1. Serial communication HILS: TBW
         1. Serial communication OBC: TBW

         </details>

      1. <details><summary> Ideal </summary>

         - `ideal` directory manages source codes of idealized components which are used in initial analysis phase in research and satellite development.
         - Force Generator
         - Torque Generator

         </details>

      1. <details><summary> Real </summary>

         - `real` directory manages source codes to emulate well used components in a normal satellite mission.

         1. <details><summary> AOCS (Attitude and Orbit Control System) </summary>

            - `aocs` directory manages components like sensor and actuators for AOCS subsystem.

            1. GNSS Receiver: TBW
            1. GYRO Sensor: TBW
            1. Magnetometer: TBW
            1. Magnetorquer: TBW
            1. Reaction wheel: TBW
            1. [Reaction wheel jitter](./Specifications/Component/AOCS/Spec_RWJitter.md)
            1. [Star sensor](./Specifications/Component/AOCS/Spec_STT.md)
            1. Sun sensor: TBW

            </details>

         1. <details><summary> CDH (Command and Data Handling) </summary>

            - `cdh` directory manages components for CDH subsystem.

            1. OBC (On-board Computer): TBW
            1. OBC with C2A: TBW

            </details>

         1. <details><summary> Communication </summary>

            - `communication` directory manages components for communication of spacecraft and ground stations.

            1. Antenna: TBW
            1. GS calculator: TBW

            </details>

         1. <details><summary> Mission </summary>

            - `mission` directory manages mission specific components like science instruments of spacecraft.

            1. [Telescope](./Specifications/Component/Mission/Spec_Telescope_en.md) ([Japanese version](./Specifications/Component/Mission/Spec_Telescope_ja.md))

            </details>

         1. <details><summary> Power </summary>

            - `power` directory manages components for power subsystem.

            1. Battery: TBW
            1. CSV scenario interface: TBW
            1. [Power Control Unit](./Specifications/Component/Power/Spec_PCU.md)
            1. PCU Initial study: TBW
            1. Solar Array Panel: TBW

            </details>

         1. <details><summary> Propulsion </summary>

            - `propulsion` directory manages components for propulsion subsystem.

            1. [Simple Thruster](./Specifications/Component/Propulsion/Spec_SimpleThruster.md)

            </details>

         1. Thermal: No components now.

         </details>

      1. <details><summary> Products </summary>

         - `products` directory manages source codes to emulate specific products published in the world. The telemetry and command interfaces are also emulated based on ICDs.
         - Users can use them for a practical simulation for satellite development.
         - TBW

         </details>

      </details>

   1. <details><summary> Disturbances </summary>

      - `disturbances` directory manages source codes to calculate disturbances acting on spacecraft on orbit.

      1. Base classes
         1. [Disturbance](./Specifications/Disturbance/Spec_Disturbance.md)
         1. [Disturbances](./Specifications/Disturbance/Spec_Disturbances.md)
      1. Disturbance calculations
         1. [Geopotential](./Specifications/Disturbance/Spec_GeoPotential.md)
         1. [Third Body Gravity](./Specifications/Disturbance/Spec_ThirdBodyGravity.md)
         1. [Gravity Gradient Torque](./Specifications/Disturbance/Spec_GravityGradient.md)
         1. [Magnetic Disturbance Torque](./Specifications/Disturbance/Spec_MagneticDisturbance.md)
         1. [Surface force](./Specifications/Disturbance/Spec_SurfaceForce.md)
            1. [Air Drag](./Specifications/Disturbance/Spec_SurfaceForce_AirDrag.md)
            1. [Solar Radiation Pressure](./Specifications/Disturbance/Spec_SurfaceForce_SolarRadiation.md)
      
      </details>

   1. <details><summary> Dynamics </summary>

      - `dynamics` directory manages source codes to calculate dynamics behavior of spacecraft.

      1. Attitude
         1. Overview of Attitude calculation: TBW
         1. [Attitude RK4](./Specifications/Dynamics/Spec_AttitudeDynamics.md)
         1. [Controlled Attitude](./Specifications/Dynamics/Spec_ControlledAttitude.md)
      1. Orbit
         1. [Overview of Orbit calculation](./Specifications/Dynamics/Spec_Orbit.md)
         1. [Kepler Orbit](./Specifications/Dynamics/Spec_KeplerOrbit.md)
         1. [RK4 Orbit Propagation](./Specifications/Dynamics/Spec_Rk4Orbit.md)
         1. [SGP4 Orbit Propagation with TLE](./Specifications/Dynamics/Spec_Sgp4.md)
         1. [Encke method](./Specifications/Dynamics/Spec_EnckeMethod.md)
         1. [Relative Orbit](./Specifications/Dynamics/Spec_RelativeOrbit.md)
      1. Thermal: not supported now.
      
      </details>

   1. <details><summary> Environment </summary>

      - `environment` directory manages source codes to calculate space environment simulation.

      1. Overview of Environment calculation
         - We divided space environment into two categories: `global` and `local`.
         - `global` directory manages space environment calculations which are shared with all spacecraft and ground stations in the simulation scenario.
           - e.g., planet position vector in the inertial frame.
         - `local` directory manages space environment calculations only for a spacecraft at its position and attitude.
           - e.g., planet position vector from the spacecraft in the spacecraft body frame.

      1. Global Environment
         1. [Global Environment](./Specifications/Environment/Spec_GlobalEnvironment.md)
         1. [Celestial Information](./Specifications/Environment/Spec_CelestialInformation.md)
         1. [Celestial Rotation](./Specifications/Environment/Spec_CelestialRotation.md)
         1. [Clock Generator](./Specifications/Environment/Spec_ClockGenerator.md)
         1. [GNSS Satellites](./Specifications/Environment/Spec_GnssSatellites_en.md), ([Japanese version](./Specifications/Environment/Spec_GnssSatellites_ja.md))
         1. [Hipparcos Catalogue](./Specifications/Environment/Spec_HipparcosCatalogue_en.md), ([Japanese version](./Specifications/Environment/Spec_HipparcosCatalogue_ja.md))
         1. [Physical Constants](./Specifications/Environment/Spec_PhysicalConstants.md)
         1. [Simulation Time](./Specifications/Environment/Spec_SimulationTime.md)

      1. Local Environment
         1. [Local Environment](./Specifications/Environment/Spec_LocalEnvironment.md)
         1. [Local Celestial Information](./Specifications/Environment/Spec_LocalCelestialInformation.md)
         1. [Atmosphere](./Specifications/Environment/Spec_Atmosphere.md)
         1. [Geomagnetic field](./Specifications/Environment/Spec_GeomagneticField.md)
         1. [Solar Radiation Pressure Environment](./Specifications/Environment/Spec_SRPEnvironment.md)

      </details>

   1. <details><summary> Library </summary>

      1. External
         - External library related source codes.
         1. IGRF (International Geomagnetic Reference Field): TBW
         1. inih: TBW
         1. nrlmsise00: TBW
         1. sgp4: TBW

      1. Geodesy
         1. Geodetic Position: TBW

      1. Communication
         1. COM port interface: TBW

      1. <details><summary> math </summary>

         1. MatVec (Matrix and Vector) : TBW
         1. Matrix: TBW
         1. ODE (Ordinaly Differential Equation): TBW
         1. Quaternion: TBW
         1. Vector: TBW
         1. s2e_math: TBW

         </details>

      1. Initialize
         1. Initialize file access: TBW

      1. Logger
         1. Loggable: TBW
         1. Log Utility: TBW
         1. Logger: TBW

      1. optics
         1. Gaussian Beam Base: TBW

      1. Orbit
         1. Kepler Orbit: TBW
         1. Orbital Elements: TBW
         1. Relative Orbit Models: TBW

      1. Randomization
         1. Global randomization: TBW
         1. Normal randomization: TBW
         1. Minimal standard linear congruential generator
         1. Minimal standard linear congruential generator with shuffle
         1. Random walk

      1. utilities
         1. Macros: TBW
         1. Endian: TBW
         1. SLIP: TBW
         1. Quantization: TBW
         1. Ring Buffer: TBW
      
      </details>

   1. <details><summary> Simulation </summary>

      - `simulation` directory manages source codes to define simulation scenario.

      1. [Simulation Configuration](./Specifications/Simulation/Spec_SimulationConfiguration.md)

      1. Case
         1. [Simulation Case](./Specifications/Simulation/Spec_SimulationCase.md)

      1. Ground Station
         1. [Ground Station](./Specifications/Simulation/Spec_GroundStation.md)

      1. HILS
         1. HILS port manager: TBW

      1. [Monte Carlo Simulation](./Specifications/Simulation/Spec_MonteCarloSimulation.md)

      1. Multiple Spacecraft
         1. Inter Spacecraft Communication: TBW
         1. Relative Information: TBW

      1. Spacecraft
         1. [Spacecraft](./Specifications/Simulation/Spec_Spacecraft.md)
         1. [Installed Components](./Specifications/Simulation/Spec_InstalledComponents.md)
         1. [Structure](./Specifications/Simulation/Spec_Structure.md)
            1. Kinematics Parameters
            1. Surface
            1. Residual Magnetic Moment
      
      </details>

   1. <details><summary> Simulation Sample </summary>

      - `simulation_sample` directory manages example source codes for user defined simulation scenario. Users can copy and modify this directory to make user defined simulation scenario.

      1. Case
         1. [Sample Case](./Specifications/Simulation/Spec_SampleCase.md)

      1. Ground Station
         1. [Sample Ground Station](./Specifications/Simulation/Spec_SampleGroundStation.md)
         1. [Sample Ground Station Components](./Specifications/Simulation/Spec_SampleGroundStationComponents.md)

      1. Spacecraft
         1. [Sample Spacecraft](./Specifications/Simulation/Spec_SampleSpacecraft.md)
         1. [Sample Components](./Specifications/Simulation/Spec_SampleSpacecraftComponents.md)
         1. SamplePortConfiguration: TBW
      
      </details>
