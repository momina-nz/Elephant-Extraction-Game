# Elephant Extraction

## Overview
Elephant Extraction is a **C-based** simulation program designed to model the movement of elephants across a grid based on the placement of bait. The elephants move strategically to consume bait and retrace their steps back when no more bait is available.

## Objective
- Provide additional **practice with dynamic memory allocation** in C.
- Implement **Array Lists** and **Stacks** in C.
- Work with **grids and movement logic**.

## Problem Statement
The town is represented as a **2D grid (R x C)**. The initial positions of the elephants are known. Elephants will move towards adjacent intersections with the most bait (watermelons). If no bait remains, they retrace their steps back home.

The simulation follows a series of **commands**:
- `BAIT R C A` → Places `A` watermelons at `(R, C)`.
- `HOUR` → Advances the simulation by an hour.
- `QUIT` → Ends the simulation and outputs the final positions of elephants.

## Files in the Repository
| File          | Description |
|--------------|-------------|
| `eleMain.c`  | Main C program implementing the simulation logic. |
| `Elephant_Extraction.pdf` | Problem statement and requirements document. |

## Installation and Compilation
### Prerequisites
- **C Compiler (gcc recommended)**

### Compilation
Compile the program using:
```sh
gcc -std=gnu11 -o elephant_sim eleMain.c -lm
```

### Running the Program
```sh
./elephant_sim < input.txt
```

## Input Format
1. First line: **`N`** (Number of elephants)
2. Next `N` lines: Each contains **two integers (`R` `C`)** representing an elephant's initial position.
3. Subsequent lines contain one of the commands: `BAIT`, `HOUR`, or `QUIT`.

### Example Input
```
3
1 4
7 3
10 8
BAIT 2 1 10
BAIT 1 3 5
HOUR
BAIT 1 4 2
HOUR
HOUR
QUIT
```

### Example Output
```
5
2
0
1 3
7 3
10 8
```

## How It Works
1. **Elephant Movement:**
   - Moves towards the adjacent intersection with the most bait.
   - If multiple choices exist, they prioritize based on the order: **North, South, West, East**.
2. **Bait Consumption:**
   - Elephants consume all bait at their final destination at each hour.
3. **Backtracking:**
   - If no bait is left, elephants retrace their steps back home, even if it brings them to the same location.

## Data Structures Used
- **2D Integer Array** → Stores the grid and bait quantities.
- **Stack (Linked List Implementation)** → Stores movement history for each elephant.

## Key Functions
| Function | Description |
|----------|-------------|
| `createNode(int row, int col)` | Creates a node for stack operations. |
| `push(Stack *stk, int row, int col)` | Pushes a new position onto the elephant's stack. |
| `pop(Stack *stk)` | Removes the last visited position. |
| `top(Stack *stk, int *row_ptr, int *col_ptr)` | Retrieves the top position without removing it. |
| `addBait(int **grid, int row, int col, int amt)` | Adds bait to the grid at a given location. |
| `eatBait(int **grid, int row, int col)` | Returns the number of bait consumed. |
| `move(Elephant *ele_ptr, int **grid)` | Moves an elephant based on available bait. |
| `progress_hour(Elephant *ele_arr, int num_ele, int **grid)` | Progresses the simulation by one hour. |

## Notes
- The program **does not** prompt for input; it reads directly from `stdin`.
- **No labeled output** (e.g., `Final Positions:`) – just raw numbers as per the problem statement.
- Ensures **efficient memory management** through dynamic allocation and deallocation.
