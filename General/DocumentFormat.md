# Format to write specification documents

## 0. General rule
- The file name should be "Spec_***.md" in the Specifications directory. 
- Please use the markdown format.
- The markdown files are converted to a book with [mdBook](https://rust-lang.github.io/mdBook/) and published in Github Pages.
  - The equations are rendered with [MathJax](https://www.mathjax.org/)
    - e.g., Please use `\boldsymbol` for bold characters instead of `\bm`.
- So, please follow the writing rules of mdBook and MathJax.

## 1.  Overview
1. Functions
   - Write an overview of functions to be realized using the class or library here clearly.

2. Related files
   - Enumerate all related codes and input files here

3. How to use
   - Write how to use the class or functions


## 2. Explanation of Algorithm
  Write important algorithms for the class, the library, or each function. Please use equations, figures, reference papers for easy understanding.

1. Name of function
   1. Overview

   2. Inputs and Outputs

   3. Algorithm
      - MathJax description
        - please use equations as

          \\[
          \dot{\boldsymbol{x}}=f(\boldsymbol{x},t)
          \\]
        - you can also use inline equation as \\( x=y \\)

      - Following description is automatically converted to the above style, but do not use this for new files.
      
        ```math
        \dot{\boldsymbol{x}}=f(\boldsymbol{x},t)
        ```
        - inline equation: $`x=y`$


   4. Note

2. Name of function

   1. Overview
   2. Inputs and Outputs
   3. Algorithm
   4. Note

3. ...

   1. ...


## 3. Results of verifications
1. Name of verification case
   1. Overview
      - please write a reason why the author does the verification

   2. conditions for the verification
      1. input files
      2. initial values

   3. results
      - please use figures to show the results clearly
        - Upload the figure files in `figs` directory
    - **Note:** the figure size should be smaller than several hundred K Bytes
            - Smaller is better 
        - Link the figure file with **relative path**
      
        
## 4. References

1. 