# Specification for Antenna

## 1.  Overview
1. Functions
   - `Antenna` class emulates the radiation wave antenna on spacecraft and ground stations.

2. Related files
   - `Antenna.cpp`, `Antenna.h`
   - `ANT.ini`
   - `SampleAntennaRadiationPattern.csv`

3. How to use
   - Set t

## 2. Explanation of Algorithm
1. `CalcTxEIRP`
    1. overview
       - Function to calculate transmit EIRP (Equivalent Isotropic Radiated Power).

    1. input and output
       - input
         + theta: Target directions [rad]
       - output
         + Transmit EIRP [dBW]

    1. algorithm
       - $P_{tx}$: RF output power for transmission [W]
       - $G_{tx}$: Transmit maximum gain [dBi]
       - $L_{f_{tx}}$: Feeder loss [dB]
       - $L_{p_{tx}}$: Pointing loss [dB]
       - $EIRP_{tx}$: Transmit EIRP [dBW]
       ```math
       EIRP_{tx} = 10 \log_{10}{P_{tx}} + G_{tx} + L_{ftx} + L_{ptx}
       ```

1. `CalcRxGT`
    1. overview
       - Function to calculate receive G/T (Gain/Temperature).

    1. input and output
       - input
         + theta: Target directions [rad]
       - output
         + Receive G/T [dB/K]

    1. algorithm
       - $G_{rx}$: Transmit maximum gain [dBi]
       - $L_{f_{rx}}$: Feeder loss [dB]
       - $L_{p_{rx}}$: Pointing loss [dB]
       - $T_{rx}$: System noise temperature [K]
       - $G/T_{rx}$: Receive G/T [dB/K]
       ```math
       G/T_{rx} = G_{rx} + L_{frx} + L_{prx} - 10\log_{10}{T_{rx}}
       ```
## 3. Results of verifications
- In this section, jitter output when the RW is rotated at a constant speed is verified.
    1. 


## 4. References
    1. 

