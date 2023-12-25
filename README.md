# Matrix Expression Evaluator using Tree Data Structure.

## Overview

This tool processes scripts containing matrix definitions and operations, evaluates these expressions, and manages memory allocation and deallocation for the data structures used. It also performs basic linear algebra computations, including matrix addition, multiplication, and transpose.

### Key Features

- **Matrix Operations:** Capable of performing matrix addition, multiplication, and transpose.
- **Script Processing:** Parses and interprets scripts to define matrices and execute operations on them.
- **Memory Management:** Efficiently handles memory for dynamic allocation and deallocation of matrix data structures.

## Mathematical Operations

1. **Matrix Addition**
   - Adds corresponding elements of two matrices of the same size.
   - Syntax: `C = A + B`

2. **Matrix Multiplication**
   - Multiplies two matrices, resulting in a new matrix with the number of rows of the first matrix and the number of columns of the second matrix.
   - Syntax: `C = A * B`

3. **Matrix Transpose**
   - Transposes a matrix, flipping it over its diagonal, thus transforming rows to columns and vice versa.
   - Syntax: `B = A'`

## Script Format

Scripts contain commands to define matrices and perform operations on them. Each line of a script can either define a new matrix or create a new matrix from a formula involving operators. Example formats include:

- Defining a new matrix: `A = 3 2 [4 5; 19 -34; 192 -9110;]`
- Using a formula: `Z = (A + B)' * C * (D' + A)'`

## Examples

1. **Matrix Definition Example**
   ```text
   A = 2 3 [1 0 2; -1 3 1;]

2. **Complex Formulas**
   ```text
   Z = (A + B)' * C * (D' + A)'
**This will create a new matrix Z with the given calculation.**
