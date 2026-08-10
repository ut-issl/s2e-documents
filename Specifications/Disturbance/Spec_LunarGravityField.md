# Specification of Lunar Gravity Field Calculation

## 1. Overview

### 1. Functions

- The `LunarGravityField` class calculates the non-spherical lunar gravity acceleration with the GRGM1200A gravity-field model.
- It reads normalized spherical-harmonic coefficients up to the user-selected degree and order and evaluates the acceleration in the Moon-Centered Moon-Fixed (MCMF) frame.
- It converts the calculated acceleration to the J2000 inertial frame and provides it to an orbit propagator as a disturbance acceleration.
- The central point-mass gravity term is not included in this disturbance because it is already calculated by the orbit propagator.

This feature was introduced in [PR #464](https://github.com/ut-issl/s2e-core/pull/464). The GRGM1200A model was developed from Gravity Recovery and Interior Laboratory (GRAIL) mission data and supports degree and order up to 1200.

### 2. Files

- [`lunar_gravity_field.cpp`](https://github.com/ut-issl/s2e-core/blob/v8.0.4/src/disturbances/lunar_gravity_field.cpp), [`lunar_gravity_field.hpp`](https://github.com/ut-issl/s2e-core/blob/v8.0.4/src/disturbances/lunar_gravity_field.hpp): Definition and declaration of the `LunarGravityField` class
- [`gravity_potential.cpp`](https://github.com/ut-issl/s2e-core/blob/v8.0.4/src/math_physics/gravity/gravity_potential.cpp), [`gravity_potential.hpp`](https://github.com/ut-issl/s2e-core/blob/v8.0.4/src/math_physics/gravity/gravity_potential.hpp): Generic normalized spherical-harmonic gravity calculation
- [`disturbances.cpp`](https://github.com/ut-issl/s2e-core/blob/v8.0.4/src/disturbances/disturbances.cpp): Creation of `LunarGravityField` when the simulation center body is the Moon
- [`disturbance.ini`](https://github.com/ut-issl/s2e-core/blob/v8.0.4/settings/sample_satellite/disturbance.ini): Example initialization file
- [`ExtLibraries/lunar_gravity_field/CMakeLists.txt`](https://github.com/ut-issl/s2e-core/blob/v8.0.4/ExtLibraries/lunar_gravity_field/CMakeLists.txt): Download and installation of the GRGM1200A coefficient file

The common normalized spherical-harmonic algorithm is described in detail in [Specification of Geopotential Calculation](./Spec_GeoPotential.md).

### 3. How to use

- Set `center_object = MOON` in the `[CELESTIAL_INFORMATION]` section of `sample_simulation_base.ini`.
- Include `EARTH` and `MOON` in the selected celestial bodies and configure Moon rotation. For GRGM1200A, the DE430 Principal Axis-oriented `SIMPLE` Moon rotation mode is the intended setting. See [Specification of Moon Rotation](../Environment/Spec_MoonRotation.md).
- Select an orbit propagator that includes disturbance acceleration, such as `RK4` or `ENCKE`.
- Enable the calculation and set the degree and coefficient-file path in the `[LUNAR_GRAVITY_FIELD]` section of `disturbance.ini`.
- Ensure that the GRGM1200A coefficient file has been downloaded and installed. The S2E CMake configuration downloads `gggrx_1200a_sha.tab` from the PDS Geosciences node into `settings/environment/gravity_field`.

`LunarGravityField` is instantiated only when the center body is `MOON`. The INI setting alone does not activate it for an Earth-centered or other-body-centered simulation.

### 4. Initialization parameters

```ini
[LUNAR_GRAVITY_FIELD]
calculation = ENABLE
logging = ENABLE
degree = 10
coefficients_file_path = SETTINGS_DIR_FROM_EXE/environment/gravity_field/gggrx_1200a_sha.tab
```

| Parameter | Unit | Description |
| --- | --- | --- |
| `calculation` | - | Enables or disables the lunar gravity-field disturbance calculation. |
| `logging` | - | Enables or disables logging of the calculated MCMF acceleration. |
| `degree` | - | Maximum spherical-harmonic degree and order. Values greater than 1200 are limited to 1200. Values less than or equal to 1 select degree 0. |
| `coefficients_file_path` | - | Path to the GRGM1200A SHA coefficient file. |

The calculation cost increases with the selected degree. Use the lowest degree that provides sufficient accuracy for the target orbit analysis.

## 2. Explanation of algorithm

### 1. Coefficient initialization

#### 1. Overview

The GRGM1200A SHA file is a comma-separated coefficient table. Its first line provides the model reference radius and gravitational constant. The remaining lines provide

```text
degree, order, normalized_Cnm, normalized_Snm, ...
```

up to degree and order 1200. S2E reads the coefficients required for the configured degree into two triangular arrays.

The degree-zero coefficient is explicitly set to

```math
\bar{C}_{0,0} = 0.
```

In the original gravity model, $\bar{C}_{0,0}=1$ represents the central point-mass term. S2E sets it to zero here because the central lunar gravity $-\mu_M\boldsymbol{r}/r^3$ is already included in the orbit dynamics. This class therefore returns only the non-spherical correction.

If the coefficient file cannot be opened, the class reports an error and changes its internal degree setting to zero.

### 2. Spherical-harmonic gravity field

The lunar gravitational potential represented by the normalized coefficients has the form

```math
U(r,\phi,\lambda) = \frac{\mu_M}{r}
\sum_{n=0}^{N}\left(\frac{R_M}{r}\right)^n
\sum_{m=0}^{n}
\bar{P}_{n,m}(\sin\phi)
\left(\bar{C}_{n,m}\cos m\lambda
    + \bar{S}_{n,m}\sin m\lambda\right),
```

where

- $\mu_M$ is the lunar gravitational constant read from the coefficient file.
- $R_M$ is the GRGM1200A reference radius read from the coefficient file.
- $r$, $\phi$, and $\lambda$ are the spacecraft spherical coordinates in MCMF.
- $\bar{P}_{n,m}$ is the normalized associated Legendre function.
- $N$ is the configured maximum degree.

`GravityPotential` evaluates the gradient of this potential using normalized recursive functions. The same implementation is used by the Earth geopotential calculation with a different coefficient model.

### 3. `Update` function

The coordinate flow is

```text
Moon-centered J2000 position
    -> MCMF position
    -> MCMF non-spherical gravity acceleration
    -> J2000 disturbance acceleration
```

The calculations are

```math
\begin{align}
\boldsymbol{r}_{MCMF}
  &= \boldsymbol{C}_{J2000\rightarrow MCMF}\boldsymbol{r}_{MCI}, \\
\boldsymbol{a}_{MCMF}
  &= \operatorname{GravityPotential}(\boldsymbol{r}_{MCMF}), \\
\boldsymbol{a}_{MCI}
  &= \boldsymbol{C}_{J2000\rightarrow MCMF}^{T}\boldsymbol{a}_{MCMF}.
\end{align}
```

The J2000-to-MCMF DCM is obtained from `MoonRotation`. The resulting inertial acceleration is accumulated with the other disturbance accelerations and supplied to the orbit propagator.

### 4. Model assumptions and limitations

- The coefficient model and the Moon-fixed coordinate frame must be consistent. GRGM1200A uses the DE430 lunar frame; an idle Moon rotation produces physically incorrect high-order gravity acceleration as the Moon rotates relative to J2000.
- The implementation assumes that the orbit position is Moon-centered. This is ensured when `center_object = MOON` and the normal dynamics initialization is used.
- Only the selected maximum degree and all orders up to that degree are supported; degree and order cannot be set independently.
- Tidal time variation and uncertainty of the gravity coefficients are not modeled.
- The complete degree-1200 coefficient file is large and requires network access during its initial CMake download.

### 5. Log output

When logging is enabled, the component outputs

- `lunar_gravity_acceleration_mcmf_m_s2`: non-spherical lunar gravity acceleration in MCMF [m/s^2]

The inertial acceleration applied to the orbit is maintained by the `Disturbance` base class but is not included in this component's dedicated log header.

## 3. Results of verifications

PR #464 compared S2E with an independent reference implementation at three positions in the Moon-fixed frame. The calculation used degree and order 10. The standalone validation included the $C_{0,0}$ central term in both calculations; the production disturbance implementation removes that term to avoid duplicating the central gravity in the orbit propagator.

| Case | Position in MCMF [km] | S2E acceleration [m/s^2] | Reference acceleration [m/s^2] | Difference [m/s^2] |
| --- | --- | --- | --- | --- |
| 1 | `(2000, 2000, 2000)` | `(-0.2358674, -0.2358886, -0.2359072)` | `(-0.2358674, -0.2358886, -0.2359072)` | `(-1.679e-10, -4.212e-10, 1.3332e-9)` |
| 2 | `(-2000, 2000, -1000)` | `(0.36318726, -0.3632152, 0.18164362)` | `(0.36318726, -0.3632152, 0.18164362)` | `(-2.454e-10, -3.234e-10, -1.219e-9)` |
| 3 | `(1000, -1500, -1000)` | `(-0.5595179, 0.83934119, 0.55972176)` | `(-0.5595179, 0.83934119, 0.55972175)` | `(2.0208e-10, 3.7713e-9, -5.092e-9)` |

The maximum absolute difference in these cases is approximately $5.1\times10^{-9}$ m/s^2. This confirms that the normalized GRGM1200A coefficient reading and spherical-harmonic acceleration calculation agree with the reference implementation for the evaluated degree and positions.

## 4. References

1. [S2E-core PR #464: Add lunar gravity field disturbance](https://github.com/ut-issl/s2e-core/pull/464)
2. E. Mazarico, [“Lunar Gravity Field: GRGM1200A”](https://pgda.gsfc.nasa.gov/products/50), NASA Goddard Planetary Geodynamics Data Archive.
3. O. Montenbruck and E. Gill, *Satellite Orbits: Models, Methods, and Applications*, Springer, 2000.
