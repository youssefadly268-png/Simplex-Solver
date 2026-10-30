# Simplex-Solver

A custom, from-scratch implementation of the Primal Simplex Method in C++. Built entirely with raw memory management (`vector<double*>`) without external math libraries, driven purely by first principles and operations research theory.

## 📁 Project Structure
- `test.txt`: Includes 4 validated working test cases.
- `tests_Log_Across_versions.txt`: Tracks the architectural evolution and test logs across versions (from v1 to v3).

## ⚙️ How It Works & Usage
1. Transform your maximization problem into standard form.
2. Enter the number of decision variables and constraints.
3. Input the coefficients for the objective function and constraints matrix, including the RHS values.
4. The solver computes and prints every iteration from the initial tableau up to the optimal solution.

## ⚠️ Disclaimer & Performance
- **Zero Dependencies:** Built purely using standard C++ (`vector`, `iostream`, `cmath`) and raw pointers.
- **No Input Validation:** Garbage in, garbage out. Input your data carefully!
- **Infinite Loop Warning:** If execution exceeds 10 seconds, you've hit a degeneracy or infinite loop. Terminate the process—your CPU, your responsibility! ⚡