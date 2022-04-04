# Coding Convention of S2E

## Fomatter
- We use [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) for S2E. 
  - We selected `Google` base style with small modifications.
  - Details are written in [.clang-format](https://github.com/ut-issl/s2e-core/blob/develop/.clang-format).


## Naming Rules
- Now discussing)*
  - The following rules are follows until the naming rule is decided.

- Macro (define)
    - All capital letters, connect between words with _

- Name of the class
     CamelCase (capitalize only the beginning of words)

- Variable name
    - All lowercase letters, connect between words with _

- Constant name (not a define but a constant)
    - Add k at the beginning and the rest is CamelCase

- Member variables in the class
    - Lowercase letters, connect between words with _, end with _

- Methods (functions) in the class
    - CamelCase


## Documentation
- Use Doxygen
- Use Markdown for Doxygen
- Examples:
  - https://developer.lsst.io/cpp/api-docs.html


## Initialization files (`.ini` files)
- Comments
  - Use //