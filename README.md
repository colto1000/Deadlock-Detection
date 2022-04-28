# Deadlock-Detection
Deadlock detection algorithm implemented in C++. CSCE 4600 Project Group 22.

### Compilation Instructions
Build with `make` \
or Manually with: `g++ main.cpp -std=c++11` \
Clean build directory with `make clean`

### Runtime Instructions
1. Run with `./deadlock-detect`
2. Enter input filename.
3. Sit back, relax, and enjoy.

### Input File Guidelines
The input file should match the following characteristics:
- Any lines with comments must start with a `%` at the position 0
- Each data should be on its own line, with no leading whitespace
- First data should be `num_processes=[##]`
- Second data should be `num_resources=[##]`
- Third data should be number of units per resource, like `#,#,#`
- Rest of file should be matrix, like:
```
#,#,#
#,#,#
#,#,#
```
