# Tower of Hanoi Visualization and Algorithm Analysis

## Overview

This project presents an interactive solution to the classic Tower of Hanoi problem, implemented in C. It includes:

- Recursive and iterative algorithms to solve the problem.
- Graphical visualization of the solution process using the Raylib library.
- Performance metrics, such as time complexity and move count, displayed during execution.

## Features

- **Interactive Simulation**: Select the number of disks and the algorithm (recursive or iterative) to observe the solution dynamically.
- **Graphical Visualization**: Disks and towers are visualized interactively, showing the movement of disks step-by-step.
- **Performance Analysis**:
  - Execution time displayed in milliseconds.
  - Total number of moves calculated and displayed.
- **Verification Algorithm**: Ensures the solution follows the rules of the Tower of Hanoi.

## Requirements

To compile and run the project, you will need:

- A C compiler (e.g., GCC).
- The [Raylib](https://www.raylib.com/) library for graphical rendering.
- Audio support for sound effects (optional but recommended).

## Installation

1. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/tower-of-hanoi-visualization.git
   cd tower-of-hanoi-visualization
   ```

2. Install Raylib:
   * For Linux:
     ```bash
     sudo apt install libraylib-dev
     ```
   * For Windows: Follow the instructions at Raylib Setup.

3. Compile the code:
   ```bash
   gcc -o hanoi main.c -lraylib -lm -ldl -lpthread
   ```

4. Run the executable:
   ```bash
   ./hanoi
   ```

## Usage

1. Launch the application.
2. Enter the number of disks (1–15) to simulate.
3. Choose the algorithm:
   * **Iterative**: Iteratively solve the Tower of Hanoi.
   * **Recursive**: Solve the problem recursively.
4. Watch the visualization as the disks move between towers.
5. View performance metrics at the bottom of the screen.
6. After completion, the verification process ensures correctness.

## Code Structure

* `main.c`: Entry point of the program. Handles user input, visualization, and algorithm selection.
* `recursive.c`: Recursive Tower of Hanoi solver.
* `iterative.c`: Iterative Tower of Hanoi solver.
* `Include/`: Contains utility headers for visualization and algorithms.

## Highlights

* Uses Raylib for smooth and interactive graphics.
* Dynamic disk movements with audio effects.
* Displays execution time, move count, and disk count during the process.

## Future Improvements

* Add a graphical UI for algorithm selection and parameter input.
* Support for larger numbers of disks with optimized memory usage.
* Comparative analysis graphs for iterative vs. recursive solutions.

## Credits

This project was deriged by me CHEMLI Ayoub. Special thanks to the Raylib community for providing an excellent library for graphics.

## License

This project is licensed under the MIT License. See the LICENSE file for details.
