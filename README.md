# S2E-Documents
## Overview

- This repository summarizes documents of [S2E (Spacecraft Simulation Environment)](https://github.com/ut-issl/s2e-core/).
- The Documents should be 
  - written in English
  - written in markdown format
  - updated ASAP when the source codes are modified
- If you have any questions or comments for S2E, feel free to ask us on the [discussions page of s2e-core](https://github.com/ut-issl/s2e-core/discussions).

## Index

1. General Information
   1. [Coding Convention](./General/CodingConvention.md)
   2. [Format of Documents](./General/DocumentFormat.md)
   3. Mandatory set up and How to Build the S2E
	   1. [How to download CSPICE Library](./General/HowToDwnloadCSPCElibrary.md)
	   2. [How to download and make NRLMSISE00 Library](./General/HowToDownloadNRLMSISE00library.md)
	   3. [How to build with Visual Studio](./General/HowToCompileWithVisualStudio.md)
	   4. ~~[How to build with OSX](./General/HowToCompileWith_OSX.md)~~  
        This configuration doesn't work now since the OSX doesn't support 32bit applications.  
        Mac users can use Ubuntu in Docker.
	   5. [How to build with Ubuntu in Docker](./General/HowToCompileWithUbuntuInDocker.md) for **both Windows and Mac** users
	   6. How to build with other compilers will be written
2. Tutorials
   1. [Getting Started](./Tutorials/GettingStarted.md)
   2. [How To Make New Simulation Scenario](./Tutorials/HowToMakeNewSimulationScenario.md)
   3. [How To Add Components](./Tutorials/HowToAddComponents.md)
   4. [How To Make New Components](./Tutorials/HowToMakeNewComponents.md)
   5. [How To Use Monte Carlo Simulation](./Tutorials/HowToUseMonteCarloSimulation.md)
   6. [How To Add Control Algorithms](./Tutorials/HowToAddControlAlgorithms.md)
   7. [How To Integrate C2A](./Tutorials/HowToIntegrateC2A.md)
   8. [How To Perform HILS Test](./Tutorials/HowToUseSerialPortCommunication.md)
   9. [How to simulate multiple satellites](./Tutorials/HowToSimulateMultipleSatellites.md)
   10. TBW
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
         1. [Telescope](./Specifications/Component/Mission/Spec_Telescope_en.md)
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
         1. [Relative Orbit](./Specifications/Dynamics/Spec_RelativeOrbit.md)
      3. Thermal
   4. Environment
      1. [SRP Environment](./Specifications/Environment/Spec_SRPEnvironment.md)
      2. [Atmosphere](./Specifications/Environment/Spec_Atmosphere.md)
      3. [Magnetic Environment](./Specifications/Environment/Spec_MagEnvironment.md)
      4. [Hipparcos Catalogue](./Specifications/Environment/Spec_HipparcosCatalogue_en.md) [(Japanese)](./Specifications/Environment/Spec_HipparcosCatalogue_ja.md)
      5. [GNSS Satellites](./Specifications/Environment/Spec_GnssSatellites_en.md) [(Japanese)](./Specifications/Environment/Spec_GnssSatellites_ja.md)
      6. [Celestial Rotation](./Specifications/Environment/Spec_CelestialRotation.md)
   5. Interface
      1. [Power Port](./Specifications/Interface/Spec_PowerPort.md)
   6. Library
   7. Simulation
      1. [Monte Carlo Simulation](./Specifications/Simulation/Spec_MonteCarloSimulation.md)
