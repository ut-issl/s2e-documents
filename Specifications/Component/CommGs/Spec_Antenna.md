# Specification for Antenna

## 1.  Overview
1. Functions
   - `Antenna` class emulates the radiation wave antenna on spacecraft and ground stations.

2. Related files
   - Main source codes: `Antenna.cpp`, `Antenna.h`
   - Initialize functions: `InitAntenna.hpp`, `InitAntenna.cpp`
   - Initialize files: `ANT.ini`, `ANT_SC.ini`, `ANT_GS.ini`

3. How to use
   - Make instance of this class at `SpacecraftComponents` and/or `GroundStationComponents` by `InitAntenna` function.
   - Set parameters in the antenna initialize files.

## 2. Explanation of Algorithm
1. `CalcTxEIRP`
    1. overview
       - Function to calculate transmit EIRP (Equivalent Isotropic Radiated Power).

    1. input and output
       - input
         + $\theta$: Angle from PZ axis on the antenna frame [rad]
         + $\phi$: Angle from PX axis on the antenna frame [rad]
           - Set $\phi = 0$ for axial symmetry pattern
       - output
         + Transmit EIRP [dBW]

    1. algorithm
       - $EIRP_{tx}$: Transmit EIRP [dBW]
       - $P_{tx}$: RF output power for transmission [W]
       - $L_{f_{tx}}$: Feeder loss [dB]
       - $L_{p_{tx}}$: Pointing loss [dB]
       - $G_{tx}(\theta, \phi)$: Antenna gain [dBi]
       - The constant value $\bar{EIRP}_{tx}$ is calculated at the `Constructor`
       - $G_{tx}(\theta, \phi)$ is calculated by `CalcAntennaGain` function
```math
       \begin{align*}
         EIRP_{tx} &= 10 \log_{10}{P_{tx}} + L_{ftx} + L_{ptx} + G_{tx}(\theta, \phi) \\
                   &= \bar{EIRP}_{tx} + G_{tx}(\theta, \phi)
       \end{align*}
```

1. `CalcRxGT`
    1. overview
       - Function to calculate receive G/T (Gain/Temperature).

    1. input and output
       - input
         + $\theta$: Angle from PZ axis on the antenna frame [rad]
         + $\phi$: Angle from PX axis on the antenna frame [rad]
           - Set $\phi = 0$ for axial symmetry pattern
       - output
         + Receive G/T [dB/K]

    1. algorithm
       - $G/T_{rx}$: Receive G/T [dB/K]
       - $L_{f_{rx}}$: Feeder loss [dB]
       - $L_{p_{rx}}$: Pointing loss [dB]
       - $T_{rx}$: System noise temperature [K]
       - $G_{rx}(\theta, \phi)$: Receiver antenna gain [dBi]
       - The constant value $\bar{G/T}_{rx}$ is calculated at the `Constructor`
       - $G_{rx}(\theta, \phi)$ is calculated by `CalcAntennaGain` function
```math
       \begin{align*}
         G/T_{rx} &= L_{frx} + L_{prx} - 10\log_{10}{T_{rx}} + G_{rx}(\theta, \phi)\\
                  &= \bar{G/T}_{rx} + G_{rx}(\theta, \phi)
       \end{align*}
```

1. `CalcAntennaGain`
    1. overview
       - Function to calculate antenna gain.
       - The antenna gain calculation method is changed by the following `AntennaGainModel`
         + `ISOTROPIC`: Ideal isotropic radiation pattern
           - Generally, the isotropic antenna gain is 0 dBi, but users can set other value for ideal analysis which are not depending on antenna pointing direction.
         + `RADIATION_PATTERN_CSV`: Arbitrary 3D radiation pattern defined in CSV file.
           - For details, please refer `AntennaRadiationPattern`.

    1. input and output
       - input
         + `AntennaParameters`
           - `AntennaGainModel`: Antenna gain model
           - `AntennaRadiationPattern`: Antenna radiation pattern information
         + $\theta$: Angle from PZ axis on the antenna frame [rad]
         + $\phi$: Angle from PX axis on the antenna frame [rad]
           - Set $\phi = 0$ for axial symmetry pattern
       - output
         + Antenna gain [dBi]

    1. algorithm
       - `ISOTROPIC` mode
         + The function just returns pre-defined antenna gain.
       - `RADIATION_PATTERN_CSV` mode
         + The function just returns `AntennaRadiationPattern::GetGain_dBi`

## 3. Results of verifications
- TBW


## 4. References
- NA

