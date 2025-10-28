# EECS 348 – Lab 9 (C++ Programming): Matrix Operations

This program loads two `N x N` matrices from a file and supports:
1) Loading/printing matrices with aligned columns  
2) A + B  
3) A * B  
4) Main & secondary diagonal sums  
5) Swap rows (0-indexed)  
6) Swap columns (0-indexed)  
7) Update a cell (0-indexed)  

## Build & Run

```bash
make            # builds `lab9`
make run        # runs with sample input.txt
./lab9          # prompts for filename (default: input.txt)
./lab9 input.txt
```

## Input Format

```
N
<Matrix A rows...>
<Matrix B rows...>
```

Example (`input.txt` is included and auto-created if missing):
```
4
01 02 03 04
05 06 07 08
09 10 11 12
13 14 15 16
13 14 15 16
09 10 11 12
05 06 07 08
01 02 03 04
```
