# Rover Run - TI301 Project

## Overview

This project was developed as part of the TI301 - Algorithms and Data Structures 2 course during the academic year 2024-2025. The objective is to design a pathfinding algorithm for the Mars Rover MARC (Mars Rover Cartograph), which has suffered damage from a solar storm. The project involves programming movement and decision-making algorithms to guide MARC back to its base station on Mars.

### Context of the Mission

The year is 2028, and the rover MARC, which was performing a cartographic mission on Mars, experienced critical system failures after an intense solar storm. These failures affected its movement and guidance systems, making it necessary for a new software solution to guide MARC back to its base station for repairs.

MARC runs on a Linux-based system, and its software is written in C. The rover can identify its position and orientation (North, South, East, West), and its radar and gyroscope still function, allowing it to detect its surroundings.

### Objective

Your mission is to design a program that enables MARC to navigate Mars, avoid dangerous terrain, and return to its base station. The primary challenge is to develop an efficient pathfinding algorithm, utilizing a decision tree to minimize the cost of movements and overcome various terrain obstacles.

## Features

- **Movement Options**: MARC can perform several unitary movements:
    - Move forward by 10m, 20m, or 30m.
    - Reverse by 10m.
    - Turn left or right by 90 degrees.
    - Perform a U-turn.

- **Randomized Phases**: Movement happens in phases, where MARC must choose 5 movements from 9 randomly generated possibilities. The selection of movements is critical for efficiency and safety.

- **Terrain Considerations**: The Martian landscape includes various terrain types that affect movement:
    - **Plain**: No effect on movement.
    - **Erg** (Dusty ground): Reduces the effectiveness of movements.
    - **Reg** (Rough ground): Limits movement options.
    - **Crevasse**: A deadly terrain that terminates MARC's mission if entered.
    - **Slope**: Moves MARC one additional space in the direction of the slope.

- **Pathfinding Algorithm**: The algorithm seeks to minimize the cost of movement by traversing the grid in an optimal manner, avoiding hazards like crevasses and reducing unnecessary movements.

## Learning Outcomes

This project helps students to master several key concepts:

- **Tree Structures**: Understanding and implementing N-ary trees, where each node represents a movement decision and the optimal path is found through tree traversal.
- **Pathfinding Algorithms**: Designing algorithms that minimize cost functions based on terrain and movement constraints.
- **Randomization and Probability**: Handling randomized movement options and dynamically adjusting probabilities during execution.
- **Performance Optimization**: Measuring execution time and efficiency of both tree construction and pathfinding algorithms.

## Compilation and Execution

### Prerequisites

- **GNU GCC Compiler**: The project is written in C, so you need a GCC compiler to compile the code.
- **CMake**: CMake is used to manage the build process. Make sure CMake is installed on your system.

### Compilation Instructions

1. Clone the repository:
   ```bash
   git clone https://github.com/eliott-belinguier/MARC-Rover.git
   cd MARC-Rover
   ```
2. Create a build directory and run CMake:
   ```bash
   mkdir build
   cd build
   cmake ..
   ```
3. Compile the code:
   ```bash
   make
   ```
4. Run the executable:
   ```bash
   cd RoverRun
   ./RoverRun
   ```

### Testing and Examples

The repository includes several test cases representing different maps and terrains on Mars. You can create your own maps to test how well MARC navigates various terrains.

## Future Extensions
- **Terrain Expansion**: Additional terrain types like slippery or rocky surfaces can be added to increase complexity.
- **Graphical Interface**: A graphical representation of the rover's journey across Mars would provide better insight into its movements.
- **AI Optimization**: Implementing machine learning algorithms to improve MARC's decision-making process in real-time could be an interesting future challenge.
