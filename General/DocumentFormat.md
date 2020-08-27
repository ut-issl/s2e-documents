# Format to write specification documents


## 0. General rule

- The file name should be "Spec_***.md"
- Please use the markdown format, which compatible with `Gitlab` web preview.
  - For equations, you should use KaTex format.
  - I recommend using `Visual Studio Code` with `Markdown+Math` extension  
    - you need to change the delimiter setup to use the same math format with `Gitlab`. 
- Please check the rendered document in `Gitlab` web page before merge requests.

## 1.  Overview

1. Functions
   
   - Write overview of functions to be realized using the class or library here clearly
2. Related files
   
   - Enumerate all related codes and input files here
3. How to use
   
   - Write how to use the class or functions
   
     

## 2. Explanation of Algorithm

  Write important algorithm for the class, the library, or the each function. Please use equations, figures, reference papers for easy understanding.

1. name of function

   1. overview

   2. inputs and outputs

   3. algorithm

      - please use equations as
        ```math
        \dot{\boldsymbol{x}}=f(\boldsymbol{x},t)
        ```
      - you can also use inline equation as $`x=y`$

   4. note

2. name of function

   1. overview
   2. inputs and outputs
   3. algorithm
   4. note

3. ...

   1. ...



## 3. Results of verifications

1. name of verification
   1. overview
      
      - please write a reason why you do the verification
   2. conditions for the verification
      1. input files
      2. initial values
   3. results

      - please use figures to clearly show the results

        - Upload the figure files in `figs` directory
    - **Note:** the figure size should be smaller than several hundred K Bytes
            - Smaller is better 
        - Link the figure file with **relative path**
      
        

## 4. References

1. 