# Documents_OSS
## Overview

- This is the repository for documents of S2E (Spacecraft Simulation Environment) CORE OSS.
- Every ISSL_OSS members can see the documents in this repository.
  - Documents only for ISSL project members should be stored in [Documents](https://gitlab.com/ut_issl/s2e/documents "Documents") repository.
- The Documents should be 
  - written clearly
  - written in English
  - written as mark down format
  - updated ASAP when the source codes are modified

## Index

1. General Information
   1. [Coding Convention](./General/CodingConvention.md)
   2. [Format of Documents](./General/DocumentFormat.md)
   3. Mandatory set up and How to Compile the S2E
	   1. [How to download CSPICE Library](./General/HowToDwnloadCSPCElibrary.md)
	   2. [How to download and make NRLMSISE00 Library](./General/HowToDownloadNRLMSISE00library.md)
	   3. [How to compile with Visual Studio](./General/HowToCompileWithVisualStudio.md)
	   4. [How to compile with OSX](./General/HowToCompileWith_OSX.md)
	   5. [How to compile with Ubuntu in Docker](./General/HowToCompileWithUbuntuInDocker.md) for **both Windows and Mac** users
	   6. How to compile with other compilers will be written
2. Tutorials
   1. [Getting Started](./Tutorials/GettingStarted.md)
   2. [How To Make New Simulation Scenario](./Tutorials/HowToMakeNewSimulationScenario.md)
   3. [How To Add Components](./Tutorials/HowToAddComponents.md)
   4. [How To Make New Components](./Tutorials/HowToMakeNewComponents.md)
   5. [How To Use Monte Carlo Simulation](./Tutorials/HowToUseMonteCarloSimulation.md)
   6. [How To Add Control Algorithms](./Tutorials/HowToAddControlAlgorithms.md)
   7. [How to integrate C2A](./Tutorials/HowToIntegrateC2A.md)
   8. TBW
3. Specifications
     1. Component
        1. Abstract
        2. AOCS
        3. CDH
        4. Logic
        5. Mission
           1. [Telescope](./Specifications/Component/Mission/Spec_Telescope_en.md)
        6. Power
        7. Propulsion
        8. Thermal
     2. Disturbance
          1. [GeoPotential](./Specifications/Disturbance/Spec_GeoPotential.md)
          2. [Gravity Gradient Torque](./Specifications/Disturbance/Spec_GGTorque.md)
          3. [Magnetic Disturbance Torque](./Specifications/Disturbance/Spec_MagDisturbance.md)
          4. [Surface force](./Specifications/Disturbance/Spec_SurfaceForce.md)
             1. [Air Drag](./Specifications/Disturbance/Spec_SurfaceForce_AirDrag.md)
             2. [Solar Radiation Pressure](./Specifications/Disturbance/Spec_SurfaceForce_SolarRadiation.md)
          5. [Third Body Gravity](./Specifications/Disturbance/Spec_ThirdBodyGravity.md)
          6. TBW
     3. Dynamics
          1. Attitude
             1. [Attitude Dynamics](./Specifications/Dynamics/Spec_AttitudeDynamics.md)
             2. [Controlled Attitude](./Specifications/Dynamics/Spec_ControlledAttitude.md)
          2. [Orbit](./Specifications/Dynamics/Spec_Orbit.md)
     4. Environment
        1. [SRP Environment](./Specifications/Environment/Spec_SRPEnvironment.md)
        2. [Atmosphere](./Specifications/Environment/Spec_Atmosphere.md)
        3. [Magnetic Environment](./Specifications/Environment/Spec_MagEnvironment.md)
        4. [Hipparicos Catalogue](./Specifications/Environment/Spec_HipparcosCatalogue_en.md)
     5. Interface
     6. Library
     7. Simulation
          1. [Monte Carlo Simulation](./Specifications/Simulation/Spec_MonteCarloSimulation.md)