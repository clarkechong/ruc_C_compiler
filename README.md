Here's the updated README with the branches section added:

# IAC Compilers Coursework 2025 - `risky_unprotected_compiling`
**Team Members:** Clarke Chong & Kevin Aubeeluck  

---

## Table of Contents
1. [Project Structure](#project-structure)  
2. [Build Instructions](#build-instructions)  
3. [Usage](#usage)  
4. [Branch Structure](#branch-structure)  

---

## Project Structure

```
langproc-2024-cw-risky-unprotected-compiling/
├── 2025-langproc-cw-repo/    # Original skeleton repository
├── bin/                      # Compiled executables
├── build/                    # Intermediate build files
├── compiler_tests/           # Test cases
├── include/                  # Header files
├── scripts/                  # Testing/utility scripts
└── src/
    ├── ast-src/              # AST implementation
    ├── generated/            # Flex/Bison generated code
    ├── mains/                # Main driver programs
    ├── cli.cpp
    ├── lexer.flex
    └── parser.y
├── Dockerfile
├── Makefile
├── parser.sh
├── test.sh
├── .gitignore
```

- **2025-langproc-cw-repo/**: The skeleton repository originally provided for the coursework
- **bin/**: Contains all compiled executables (e.g., the main compiler binary)
- **build/**: Contains intermediate build artifacts (object files, etc.)
- **compiler_tests/**: Contains all test cases for the compiler
- **include/**: Contains all header files for the project
- **scripts/**: Contains utility scripts for testing and development
- **src/**: Main source code directory with:
  - **ast-src/**: Implementation of Abstract Syntax Tree components
  - **generated/**: Auto-generated files from Flex/Bison
  - **mains/**: Entry point programs
  - Core source files: lexer.flex, parser.y, and cli.cpp
- Root files: Dockerfile, Makefile, and various utility scripts (.sh files)

---

## Build Instructions

To build the project:
1. Clone the repository  
2. Install dependencies (make, gcc, flex, bison, etc)  
3. Run `make` in the root directory  

The main compiler executable will be built as `bin/c_compiler`.

Notes:
- The Makefile tracks all dependencies, so `make clean` is generally unnecessary unless making significant changes to header files
- For a complete rebuild, use `make clean` followed by `make`

Example:
```bash
git clone https://github.com/LangProc/langproc-2024-cw-risky_unprotected_compiling.git
make all # test.sh will also run make itself
./test.sh
```

---

## Usage

### Basic Compilation
```bash
bin/c_compiler -S <source-file> -o <output-file>
```

### Running Test Suite
The provided test suite can be executed with:
```bash
./test.sh
```

This will:
1. Automatically run `bin/c_compiler -S -o` for each test case in `compiler_tests/`
2. Compare outputs against expected results
3. Report success/failure for all 86 test cases

---

## Branch Structure

The project uses three main branches:

1. **main**: Contains the original attempted implementation.
2. **experimental**: A newer implementation using a more comprehensive context class and redesigned AST structure.
3. **experimental-v2**: Contains a refactored version of the context class with improved class organization and readability.

**Note:** The version submitted for marking is `experimental-v2`, which represents our most refined implementation. At submission, it successfully passed 75/86 test cases.