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
   2. [Format of S2E Documents](./General/DocumentFormat.md)
   3. Mandatory set up and How to Build the S2E  
	   1. [How to build with Visual Studio](./General/HowToCompileWithVisualStudio.md)
	   2. [How to build with Ubuntu in Docker](./General/HowToCompileWithUbuntuInDocker.md) for **both Windows and Mac** users
	   3. How to build with other compilers will be written
   4. Set up of External Libraries  
      **NOTE**: Currenly, this setting sequence is included in the mandatory setups described above. So users don't need to see the following documents.
      1. [How to download CSPICE Library](./General/HowToDwnloadCSPCElibrary.md)
	   2. [How to download and make NRLMSISE00 Library](./General/HowToDownloadNRLMSISE00library.md)
   5. Visulalization of Simulation Results
      1. [How to Visualize Simulation Results](./General/HowToVisualizeSimulationResults.md)
     

2. Tutorials  
   - We strongly recommend to sequencially follow the all tutorials at first.
   1. [Getting Started](./Tutorials/GettingStarted.md)
   2. [How To Make New Simulation Scenario](./Tutorials/HowToMakeNewSimulationScenario.md)
   3. [How To Add Components](./Tutorials/HowToAddComponents.md)
   4. [How To Make New Components](./Tutorials/HowToMakeNewComponents.md)
   5. [How To Use Monte Carlo Simulation](./Tutorials/HowToUseMonteCarloSimulation.md)
   6. [How To Add Control Algorithms](./Tutorials/HowToAddControlAlgorithms.md)
   7. [How To Integrate C2A](./Tutorials/HowToIntegrateC2A.md)
   8. [How To Perform UART HILS Test](./Tutorials/HowToPerformUartHilsTest.md)
   9. [How To Perform I2C HILS Test](./Tutorials/HowToPerformI2cHilsTest.md)
   10. [How to simulate multiple satellites](./Tutorials/HowToSimulateMultipleSatellites.md)
   11. TBW

3. Specifications
   1. [Overall Structure](./Specifications/OverallStructure/OverallStructure.md)

   1. <details><summary> Component </summary>
      
      1. Overview of Components: TBW
      1. <details><summary> Abstract </summary>

         1. [Component Base](./Specifications/Component/Abstract/Spec_ComponentBase.md)
         1. Examples: TBW
         1. I2C Controller Communication Base: TBW
         1. Tickable: TBW
         1. [OBC Communication Base](./Specifications/Component/Abstract/Spec_ObcCommunicationBase.md)
         1. OBC GPIO Base: TBW
         1. OBC I2C Target Communication Base: TBW
         1. [Sensor Base](./Specifications/Component/Abstract/Spec_SensorBase.md)
         1. Singleton: TBW
         1. StateMachine: TBW

         </details>

      1. <details><summary> AOCS (Attitude and Orbit Control System) </summary>

         1. GNSS Receiver: TBW
         1. Gyro sensor: TBW
         1. Magnetic sensor: TBW
         1. Magnetorquer: TBW
         1. [RW Jitter](./Specifications/Component/AOCS/Spec_RWJitter.md)
         1. RW (Reaction Wheel): TBW
         1. [STT](./Specifications/Component/AOCS/Spec_STT.md)
         1. Sun sensor: TBW

         </details>

      1. <details><summary> CDH (Command and Data Handling) </summary>

         1. OBC (Onboard Computer): TBW
         1. OBC C2A: TBW
         1. TMTC Interface: TBW

         </details>

      1. <details><summary> CommGS (Communication and Ground Station) </summary>

         1. Antenna: TBW
         1. GS calculator: TBW

         </details>

      1. <details><summary> Mission </summary>

         1. [Telescope](./Specifications/Component/Mission/Spec_Telescope_en.md) ([Japanese version](./Specifications/Component/Mission/Spec_Telescope_ja.md))

         </details>

      1. <details><summary> Power </summary>

         1. BAT (Battery): TBW
         1. CSV scenario interface: TBW
         1. [PCU](./Specifications/Component/Power/Spec_PCU.md)
         1. PCU Initial study: TBW
         1. SAP (Solar Array Paddle): TBW

         </details>

      1. <details><summary> Propulsion </summary>

         1. [SimpleThruster](./Specifications/Component/Propulsion/Spec_SimpleThruster.md)

         </details>

      1. Thermal: No components now.

      </details>

   2. <details><summary> Disturbance </summary>

      1. Overview of disturbance calculation: TBW
      1. [GeoPotential](./Specifications/Disturbance/Spec_GeoPotential.md)
      1. [Gravity Gradient Torque](./Specifications/Disturbance/Spec_GGTorque.md)
      1. [Magnetic Disturbance Torque](./Specifications/Disturbance/Spec_MagDisturbance.md)
      1. [Surface force](./Specifications/Disturbance/Spec_SurfaceForce.md)
         1. [Air Drag](./Specifications/Disturbance/Spec_SurfaceForce_AirDrag.md)
         1. [Solar Radiation Pressure](./Specifications/Disturbance/Spec_SurfaceForce_SolarRadiation.md)
      1. [Third Body Gravity](./Specifications/Disturbance/Spec_ThirdBodyGravity.md)
      
      </details>

   3. <details><summary> Dynamics </summary>

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

   4. <details><summary> Environment </summary>

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

   5. <details><summary> Interface </summary>

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

   6. <details><summary> Library </summary>

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

   7. <details><summary> Simulation </summary>

      1. [Monte Carlo Simulation](./Specifications/Simulation/Spec_MonteCarloSimulation.md)
      
      </details>
