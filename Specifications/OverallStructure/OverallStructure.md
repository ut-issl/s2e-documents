# Overall Structure of S2E

## 1. Overview
- This document explains overall structure of S2E.
- Supported version of this document
  - S2E_CORE_OSS:c4c7cf6567c077f0918f07a9a82c2d7e4531ceb7

## 2. Structure of S2E
- The following figure shows the structure of S2E.

<img src="./figs/S2E_structure.png" alt="S2EStructure" style="zoom: 90%;" />

### 2.1. Simulation Case
- The largest structure unit of S2E is the `Simulation Case`, which is defined in the `src/Simulation/Case/SimulationCase.cpp`.
- The `SimulationCase` always has `SimulationConfig` and `Global Environment`
   - `SimulationConfig` has basic information of the interface of the simulation such as `log output` and `initialize input` information
   - `GlobalEnvironment` is defined as the common environment for the whole simulation case. It includes time, celestial information, star catalogue, and so on.
- Users can make their own `SimulationCase` by inheriting the `SimulationCase` base class, and add simulation target objects (e.g. spacecraft and ground station) for their demand.
- The information of `SimulationConfig` and `GlobalEnvironment` can be used by the defined simulation objects.

### 2.2. Spacecraft
- The most important simulation object is the `Spacecraft`. 
- `Spacecraft` has the following features to simulate the behavior of spacecraft in the space.
   - `Structure`
      - This class handles the structure information of the spacecraft such as mass, inertia of tensor, surface information, and so on.
      - The information is used to calculate disturbance and propagate dynamics.
   - `LocalEnvironment`
      - This class handles space environment information around the spacecraft such as air density, magnetic field, solar energy, and so on.
      - The information is used to calculate disturbance and emulate environment sensors.
   - `Disturbance`
      - This class handles disturbances forces(accelerations) and torques.
      - The information is used to propagate dynamics.
   - `Dynamics`
      - This class handles dynamics calculation for attitude, orbit, and thermal.
      - This is the core of the numerical simulation
   - `Components`
      - This class emulates the behavior of components mounted on the spacecraft. By using the `components`, the spacecraft can measure the physical quantities and generate control output.
      - Only this class is not defined in the `Spacecraft` base class, and users have to define it by themselves
- Users can add multiple spacecraft into their `SimulationCase`, and these spacecraft can communicate via communication components.

### 2.3. Ground Station
- TBW

### 2.4. Structure of initialize files
- Basically, the structure of the initialize files follows the above figure.
- `SimBase.ini` sets the parameters for `SimulationCase`, and file paths to each simulation object.
- `Sat.ini` sets the parameters for `Spacecraft`, and file paths to each components.

## 3. Structure of spacecraft components
**Note:** the structure of components are implementing now. So the following figure is just an idea, and it may be modified.

<img src="./figs/Component_structure.png" alt="ComponentStructure" style="zoom: 90%;" />
- Each component can communicate with other components.
- All components have power wire and the switch is controlled by power control components.
