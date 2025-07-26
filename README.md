# Multiple Linear Regression (C++)

This project implements Multiple Linear Regression from scratch in C++ using the Normal Equation. It includes custom matrix operations and reads input data from a CSV file.

## How It Works

1. Reads input features and output from `file.csv`.
2. Forms matrices `X` (features) and `Y` (target).
3. Computes coefficients using the Normal Equation:
   \[
   beta = (X^T X)^{-1} X^T Y
   \]
4. Uses β to predict new outputs.


## File Structure

- `main.cpp` – Driver code  
- `data.h` – CSV reader  
- `matrix.h` – Matrix operations  
- `linearRegression.h` – Core regression logic  
- `file.csv` – Input dataset  
- `CMakeLists.txt` – Build configuration  

## Build & Run

```bash
mkdir build && cd build
cmake ..
make
./MultipleLinearRegression

```
## Author

**Sejal Choudhari**  
GitHub: [@sejal-choudhari](https://github.com/sejal-choudhari)
