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

   1. Component
      1. Abstract
         1. [Component Base](./Specifications/Component/Abstract/Spec_ComponentBase.md)
         1. [OBC Communication Base](./Specifications/Component/Abstract/Spec_ObcCommunicationBase.md)
         1. [Sensor Base](./Specifications/Component/Abstract/Spec_SensorBase.md)
      2. AOCS
         1. [STT](./Specifications/Component/AOCS/Spec_STT.md)
         1. [RW Jitter](./Specifications/Component/AOCS/Spec_RWJitter.md)
      3. CDH
      4. Logic
      5. Mission
         1. [Telescope](./Specifications/Component/Mission/Spec_Telescope_en.md) ([Japanese version](./Specifications/Component/Mission/Spec_Telescope_ja.md))
      6. Power
         1. [PCU](./Specifications/Component/Power/Spec_PCU.md)
      7. Propulsion
         1. [SimpleThruster](./Specifications/Component/Propulsion/Spec_SimpleThruster.md)
      8. Thermal

   2. Disturbance
      1. [GeoPotential](./Specifications/Disturbance/Spec_GeoPotential.md)
      2. [Gravity Gradient Torque](./Specifications/Disturbance/Spec_GGTorque.md)
      3. [Magnetic Disturbance Torque](./Specifications/Disturbance/Spec_MagDisturbance.md)
      4. [Surface force](./Specifications/Disturbance/Spec_SurfaceForce.md)
         1. [Air Drag](./Specifications/Disturbance/Spec_SurfaceForce_AirDrag.md)
         2. [Solar Radiation Pressure](./Specifications/Disturbance/Spec_SurfaceForce_SolarRadiation.md)
      5. [Third Body Gravity](./Specifications/Disturbance/Spec_ThirdBodyGravity.md)

   3. Dynamics
      1. Attitude
         1. [Attitude Dynamics](./Specifications/Dynamics/Spec_AttitudeDynamics.md)
         2. [Controlled Attitude](./Specifications/Dynamics/Spec_ControlledAttitude.md)
      2. [Orbit](./Specifications/Dynamics/Spec_Orbit.md)
         1. [Kepler Orbit](./Specifications/Dynamics/Spec_KeplerOrbit.md)
         2. [RK4 Orbit Propagation](./Specifications/Dynamics/Spec_Rk4Orbit.md)
         3. [SGP4 Orbit Propagation with TLE](./Specifications/Dynamics/Spec_Sgp4.md)
         4. [ENCKE method](./Specifications/Dynamics/Spec_EnckeMethod.md)
         5. [Relative Orbit](./Specifications/Dynamics/Spec_RelativeOrbit.md)
      3. Thermal

   4. Environment
      1. [Solar Radiation Pressure Environment](./Specifications/Environment/Spec_SRPEnvironment.md)
      2. [Atmosphere](./Specifications/Environment/Spec_Atmosphere.md)
      3. [Magnetic Environment](./Specifications/Environment/Spec_MagEnvironment.md)
      4. [Hipparcos Catalogue](./Specifications/Environment/Spec_HipparcosCatalogue_en.md), ([Japanese version](./Specifications/Environment/Spec_HipparcosCatalogue_ja.md))
      5. [GNSS Satellites](./Specifications/Environment/Spec_GnssSatellites_en.md), ([Japanese version](./Specifications/Environment/Spec_GnssSatellites_ja.md))
      6. [Celestial Rotation](./Specifications/Environment/Spec_CelestialRotation.md)

   5. Interface
      1. [Power Port](./Specifications/Interface/Spec_PowerPort.md)

   6. Library
      - TBW

   7. Simulation
      1. [Monte Carlo Simulation](./Specifications/Simulation/Spec_MonteCarloSimulation.md)
