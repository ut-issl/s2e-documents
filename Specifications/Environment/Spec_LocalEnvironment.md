# Specification for Local Environment

## 1.  Overview
### 1. Functions 
+ The `LocalEnvironment` class integrates all local environments.

### 2. Related files
+ `src/environment/local/local_environment.cpp, .hpp`
  + All local environment classes are initialized and updated here as a member variable.

### 3. How to use
+ When users make a new local environment class, users need to add the class as a member variable.

## 3. Explanation of Algorithm
### 1. `Update` function
#### 1. overview
- The environment calculations that depend on the spacecraft attitude are called when the spacecraft attitude is updated.
- The environment calculations that depend on the spacecraft position are called when the spacecraft position is updated.

## 4. Verification
- NA

## 5. References
- NA

