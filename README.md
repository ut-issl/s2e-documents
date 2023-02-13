# S2E-Documents
## Overview

- This repository summarizes documents of [S2E (Spacecraft Simulation Environment)](https://github.com/ut-issl/s2e-core/).
- The branch construction
  - main
    - Documents for the latest stable version of s2e-core
      - Current version supports [s2e-core v5.0.0](https://github.com/ut-issl/s2e-core/releases/tag/v5.0.0)
    - The old versions are managed with `release/tag/v.*.*.*`
      - The release version number is compatible with s2e-core's version number
  - develop
    - Documents for the latest `develop` branch of s2e-core
    - This version is only for s2e-core developers
  - feature/branch-name
    - Writing documents before merge with the `develop`
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
     1. [How to simulate multiple satellites](./Tutorials/HowToSimulateMultipleSatellites.md)
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
         1. [sensor](./Specifications/Component/Abstract/Spec_SensorBase.md)
         1. [UART Communication with OBC](./Specifications/Component/Abstract/Spec_ObcCommunicationBase.md)

         </details>

      1. <details><summary> AOCS (Attitude and Orbit Control System) </summary>

         - `aocs` directory manages components like sensor and actuators for AOCS subsystem.

         1. gnss_receiver: TBW
         1. gyro_sensor: TBW
         1. magnetometer: TBW
         1. magnetorquer: TBW
         1. reaction wheel: TBW
         1. [reaction_wheel_jitter](./Specifications/Component/AOCS/Spec_RWJitter.md)
         1. [star sensor](./Specifications/Component/AOCS/Spec_STT.md)
         1. sun sensor: TBW

         </details>

      1. <details><summary> CDH (Command and Data Handling) </summary>

         - `cdh` directory manages components for CDH subsystem.

         1. OBC (Onboard Computer): TBW
         1. OBC C2A: TBW

         </details>

      1. <details><summary> Communication </summary>

         - `communication` directory manages components for communication of spacecraft and ground stations.

         1. Antenna: TBW
         1. GS calculator: TBW

         </details>

      1. <details><summary> Ideal Components </summary>

         - TBW

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


      1. <details><summary> Examples </summary>

         - `examples` directory manages example source codes to show how to make user defined components.
         - Please do not use these classes directory for your simulation analysis.

         1. Change structure: TBW
         1. I2C controller for HILS: TBW
         1. I2C target for HILS: TBW
         1. Serial communication HILS: TBW
         1. Serial communication OBC: TBW

         </details>

      </details>

   1. <details><summary> Disturbance </summary>

      1. Overview of disturbance calculation: TBW
      1. [GeoPotential](./Specifications/Disturbance/Spec_GeoPotential.md)
      1. [Gravity Gradient Torque](./Specifications/Disturbance/Spec_GGTorque.md)
      1. [Magnetic Disturbance Torque](./Specifications/Disturbance/Spec_MagDisturbance.md)
      1. [Surface force](./Specifications/Disturbance/Spec_SurfaceForce.md)
         1. [Air Drag](./Specifications/Disturbance/Spec_SurfaceForce_AirDrag.md)
         1. [Solar Radiation Pressure](./Specifications/Disturbance/Spec_SurfaceForce_SolarRadiation.md)
      1. [Third Body Gravity](./Specifications/Disturbance/Spec_ThirdBodyGravity.md)
      
      </details>

   1. <details><summary> Dynamics </summary>

      1. Attitude
         1. Overview of Attitude calculation: TBW
         1. [Attitude Dynamics](./Specifications/Dynamics/Spec_AttitudeDynamics.md)
         1. [Controlled Attitude](./Specifications/Dynamics/Spec_ControlledAttitude.md)
      1. Orbit
         1. [Overview of Orbit calculation](./Specifications/Dynamics/Spec_Orbit.md)
         1. [Kepler Orbit](./Specifications/Dynamics/Spec_KeplerOrbit.md)
         1. [RK4 Orbit Propagation](./Specifications/Dynamics/Spec_Rk4Orbit.md)
         1. [SGP4 Orbit Propagation with TLE](./Specifications/Dynamics/Spec_Sgp4.md)
         1. [ENCKE method](./Specifications/Dynamics/Spec_EnckeMethod.md)
         1. [Relative Orbit](./Specifications/Dynamics/Spec_RelativeOrbit.md)
      1. Thermal: not supported now.
      
      </details>

   1. <details><summary> Environment </summary>

      1. Overview of Environment calculation: TBW
      1. Global Environment
         1. Celestial Information: TBW
         1. [Celestial Rotation](./Specifications/Environment/Spec_CelestialRotation.md)
         1. Clock Generation: TBW
         1. [GNSS Satellites](./Specifications/Environment/Spec_GnssSatellites_en.md), ([Japanese version](./Specifications/Environment/Spec_GnssSatellites_ja.md))
         1. [Hipparcos Catalogue](./Specifications/Environment/Spec_HipparcosCatalogue_en.md), ([Japanese version](./Specifications/Environment/Spec_HipparcosCatalogue_ja.md))
         1. Physical Constants: TBW
         1. SimTime: TBW
      1. Local Environment
         1. [Atmosphere](./Specifications/Environment/Spec_Atmosphere.md)
         1. [Magnetic Environment](./Specifications/Environment/Spec_MagEnvironment.md)
         1. [Solar Radiation Pressure Environment](./Specifications/Environment/Spec_SRPEnvironment.md)

      </details>

   1. <details><summary> Interface </summary>

      1. Overview of Interface
      1. HILS In/Out
         1. Com port interface: TBW
         1. Hardware Message: TBW
         1. HILS port manager: TBW

      1. Initialize Input
         1. IniAccess: TBW

      1. Log Output
         1. Loggable: TBW
         1. Log Utility: TBW
         1. Logger: TBW

      1. <details><summary> Spacecraft In/Out</summary>

         1. Ports
            1. GPIO Port: TBW
            1. I2C Port: TBW
            1. [Power Port](./Specifications/Interface/Spec_PowerPort.md)
            1. SCI Port: TBW
         1. Utils
            1. ITCTMChannel: TBW
            1. Ring Buffer: TBW

         </details>

      
      </details>

   1. <details><summary> Library </summary>

      1. Geodesy
         1. Geodetic Position: TBW
      1. Orbit
         1. Kepler Orbit: TBW
         1. Orbital Elements: TBW
      1. Relative Orbit
         1. Relative Orbit Models: TBW
      1. IGRF (International Geomagnetic Reference Field): TBW
      1. inih: TBW
      1. <details><summary> math </summary>

         1. GlobalRand (Global Randomize control): TBW
         1. MatVec (Matrix and Vector) : TBW
         1. Matrix: TBW
         1. NormalRand (Normal Randomization): TBW
         1. ODE (Ordinaly Differential Equation): TBW
         1. Quantization: TBW
         1. Quaternion: TBW
         1. Ran0 and Ran1: TBW
         1. Random Walk: TBW
         1. Vector: TBW
         1. s2e_math: TBW

         </details>
      1. nrlmsise00: TBW
      1. optics
         1. Gaussian Beam Base: TBW
      1. sgp4: TBW
      1. utils
         1. Macros: TBW
         1. Endian: TBW
         1. SLIP: TBW
      
      </details>

   1. <details><summary> Simulation </summary>

      1. Case: TBW
      1. Ground Station: TBW
      1. Inter Satellite Communication: TBW
      1. [MCSim (Monte Carlo Simulation)](./Specifications/Simulation/Spec_MonteCarloSimulation.md)
      1. Spacecraft: TBW
         1. Installed Components: TBW
         1. Spacecraft: TBW
         1. Structure: TBW
      
      </details>
