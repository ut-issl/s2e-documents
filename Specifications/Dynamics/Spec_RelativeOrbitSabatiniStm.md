# Format to write specification documents

## 0. General rule
- The file name should be `Spec_CamelCase.md` in the Specifications directory. 
- Please use the markdown format.
- Because GitHub started to support math description ([link](https://github.blog/2022-05-19-math-support-in-markdown/)), we need to describe equations suit with the rule of GitHub and [MathJax](https://www.mathjax.org/).

## 1.  Overview
### 1. Features
- Write an overview of features to be realized using the class or library here clearly.

### 2. Related files
- Enumerate all related codes and input files here

### 3. How to use
- Write how to use the class or functions


## 2. Explanation of Algorithm
Write important algorithms for the class, the library, or each function. Please use equations, figures, reference papers for easy understanding.

### 1. Name of class, structure, and function
#### 1. Overview
- Please summarize the 

#### 2. Inputs and Outputs
- Please list up inputs and outputs

#### 3. Algorithm
- Please use math description when you need as follows
$$\dot{\boldsymbol{x}}=f(\boldsymbol{x},t)$$

```math
\dot{\boldsymbol{x}}=f(\boldsymbol{x},t)
```
- you can also use inline equation as $x=y$

#### 4. Note

### 2. Name of function
#### 1. Overview
#### 2. Inputs and Outputs
#### 3. Algorithm
#### 4. Note

### 3. Name of function
#### 1. Overview


## 3. Results of verifications
### 1. Name of verification case
#### 1. Overview
- please write a reason why the author does the verification

#### 2. conditions for the verification
- input files
- initial values

#### 3. result
- please use figures to show the results clearly
- Upload the figure files in `figs` directory
  - **Note:** the figure size should be smaller than several hundred K Bytes
    - Smaller is better 
  - Link the figure file with **relative path**
      
        
## 4. References

1. 
