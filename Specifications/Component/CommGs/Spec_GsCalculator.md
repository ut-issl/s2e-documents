# Specification for GsCalculator

## 1.  Overview
1. Functions
   - `GsCalculator` class emulates communication analysis between spacecraft and Ground Stations.
   - **NOTE**: The description of `GsCalculator` suits with current naming rule, but there are still old description as `GScalculator` in the codes. In this documents, we use `GsCalculator`.
   - **NOTE**: The current `GsCalculator` is in the `Component` directory but doesn't inherit `ComponentBase`. We need to newly make `Analysis` directory and move `GsCalculator` to the directory.

1. Related files
   - Main source codes: `GsCalculator.cpp`, `GsCalculator.h`
   - Initialize functions: `InitGsCalculator.hpp`, `InitGsCalculator.cpp`
   - Initialize files: `GsCalculator.ini`

1. How to use
   - Make instance of this class at `GsComponents` by `InitGsCalculator` function.
   - Set parameters in the initialize file.
   - Call the `Update` function in the user defined `GroundStation` calculation class.

## 2. Explanation of Algorithm
1. `CalcCn0OnGs`
    1. overview
       - Function to calculate $CN_{0}$ (Carrier to Noise density ratio) of received signal at the ground station.

    1. input and output
       - input
         + dynamics: Dynamics information of spacecraft to get spacecraft position
         + sc_tx_ant: TX antenna mounted on the spacecraft
         + ground_station: Ground station information to get ground station position
         + gs_rx_ant: RX antenna mounted on the ground station
       - output
         + $CN_{0}$ [dB]

    1. algorithm
       - Calculation of free space path loss $L_{fs}$ dB
         - $D_{sc-gs}$: Distance between spacecraft and ground station [km]
         - $f_{tx}$: TX signal frequency [MHz]
```math
         L_{fs} = -20\log_{10}{\left(\frac{4\pi D_{sc-gs}}{\frac{300}{1000}f_{tx}}\right)}
```
       - Calculation of ground station direction on the spacecraft TX antenna frame
         - $\boldsymbol{r}_{sc-gs}^{tx}$: Direction vector from spacecraft to ground station at the TX antenna frame
```math
         \begin{align*}
         \boldsymbol{r}_{sc-gs}^{tx} &= \begin{bmatrix}
                                         x_{sc-gs}^{tx} \\
                                         y_{sc-gs}^{tx} \\
                                         z_{sc-gs}^{tx} \\
                                        \end{bmatrix}\\
         \theta_{tx} &= \cos^{-1}(z_{sc-gs}^{tx})\\
         \phi_{tx} &= \cos^{-1}\left(\frac{x_{sc-gs}^{tx}}{\sin{\theta_{tx}}}\right)
         \end{align*}
```
       - Calculation of spacecraft direction on the ground station RX antenna frame
         - $\boldsymbol{r}_{sc-gs}^{rx}$: Direction vector from ground station to spacecraft at the RX antenna frame
```math
         \begin{align*}
         \boldsymbol{r}_{sc-gs}^{rx} &= \begin{bmatrix}
                                         x_{sc-gs}^{rx} \\
                                         y_{sc-gs}^{rx} \\
                                         z_{sc-gs}^{rx} \\
                                        \end{bmatrix}\\
         \theta_{rx} &= \cos^{-1}(z_{sc-gs}^{rx})\\
         \phi_{rx} &= \cos^{-1}\left(\frac{x_{sc-gs}^{rx}}{\sin{\theta_{rx}}}\right)
         \end{align*}
```
       - Calculation of $CN_{0}$
         - $EIRP_{tx}(\theta_{tx}, \phi_{tx})$: Transmit EIRP calculated by `Antenna` class including TX antenna gain [dB]
         - $L_{fs}$: Free space path loss[dB]
         - $L_{pl}$: Polarization loss[dB]
         - $L_{at}$: Atmospheric loss[dB]
         - $L_{rf}$: Rain fall loss[dB]
         - $L_{ot}$: Other loss[dB]
         - $GT_{rx}(\theta_{rx}, \phi_{rx})$:  Receive G/T calculated by `Antenna` class including RX antenna gain [dB/K]
         - $k_{B}$: Boltzmann constant [J/K] 
```math
         CN_{0} = EIRP_{tx}(\theta_{tx}, \phi_{tx}) + L_{fs} + L_{pl} + L_{at} + L_{rf} + L_{ot} + GT_{rx}(\theta_{rx}, \phi_{rx}) - 10\log_{10}{k_{B}}
```

1. `CalcMaxBitrate`
    1. overview
       - Function to calculate maximum bitrate for downlink.

    1. input and output
       - input
         + dynamics: Dynamics information of spacecraft to get spacecraft position
         + sc_tx_ant: TX antenna mounted on the spacecraft
         + ground_station: Ground station information to get ground station position
         + gs_rx_ant: RX antenna mounted on the ground station
       - output
         + $R_{max}$: Maximum bitrate [Mbps]

    1. algorithm
       - $E_{b}N_{0}$: Energy per bit to Noise density ratio [dB]
       - $L_{hw}$: Hardware deterioration [dB]
       - $G_{code}$: Coding gain [dB]
       - $M_{rq}$: Margin requirement [dB]
```math
       \begin{align*}
       M_{bitrate} &= CN_{0} - (E_{b}N_{0} + L_{hw} + G_{code}) - M_{req} \\
       R_{max} &= \frac{1}{1000000} 10^{\frac{M_{bitrate}}{10}}
       \end{align*}
```

1. `CalcReceiveMarginOnGs`
    1. overview
       - Function to calculate receive margin at the ground station.

    1. input and output
       - input
         + dynamics: Dynamics information of spacecraft to get spacecraft position
         + sc_tx_ant: TX antenna mounted on the spacecraft
         + ground_station: Ground station information to get ground station position
         + gs_rx_ant: RX antenna mounted on the ground station
       - output
         + $M_{rex}$: Receive margin [dB]

    1. algorithm
       - $E_{b}N_{0}$: Energy per bit to Noise density ratio [dB]
       - $L_{hw}$: Hardware deterioration [dB]
       - $G_{code}$: Coding gain [dB]
       - $R_{tx}$: TX bit rate[bps]
```math
       \begin{align*}
       CN_{req} &= E_{b}N_{0} + L_{hw} + G_{code} + 10\log_{10}{R_{tx}} \\
       M_{rec} &= CN_{0} - CN_{req}
       \end{align*}
```

1. `Update`
    1. overview
       - Function to update the following states in `GsCalculator`.
         + $M_{rex}$: Receive margin [dB]
         + $R_{max}$: Maximum bitrate [Mbps]
       - The states are calculated when the spacecraft is visible from the ground station. When it is invisible, the states are set as meaning less value.

    1. input and output
       - input
         + dynamics: Dynamics information of spacecraft to get spacecraft position
         + sc_tx_ant: TX antenna mounted on the spacecraft
         + ground_station: Ground station information to get ground station position
         + gs_rx_ant: RX antenna mounted on the ground station
       - output
         + NA

    1. algorithm
       - Call `CalcReceiveMarginOnGs` and `CalcMaxBitrate` when the spacecraft is visible.

## 3. Results of verifications
- TBW


## 4. References
- NA

