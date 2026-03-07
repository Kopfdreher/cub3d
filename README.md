*This project has been created as part of the 42 curriculum by aabelkis, sgavrilo.*

# cub3D

## Description

Cub3D is a 3D first-person maze game inspired by the world-famous 1992 classic, *Wolfenstein 3D*. The primary goal of this project is to create a dynamic 3D representation of a maze using pure mathematics and the **Ray-Casting** rendering technique.

By completing this project, we explored and mastered several low-level programming concepts, including:

* **Mathematics & Geometry:** Implementing the Digital Differential Analyzer (DDA) algorithm to calculate ray intersections and avoid fisheye distortion.
* **Graphics & Window Management:** Utilizing the MiniLibX graphic library to draw pixel-by-pixel to an image buffer and push frames to a window.
* **File Parsing:** Validating a highly specific `.cub` configuration file that dictates the player's spawn direction, ceiling/floor RGB colors, and the file paths to four distinct directional wall textures (North, South, East, West).
* **Physics:** Building a continuous-movement physics engine with independent axis checking to allow for smooth wall-sliding and prevent corner clipping.

## Features

* Smooth, continuous WASD movement and camera rotation.
* Continuous collision detection (wall sliding).
* Direction-dependent wall texturing (N, S, E, W).
* Dynamic floor and ceiling color rendering.
* Robust map validation and memory leak prevention.

## Instructions

### Prerequisites

To compile and run this project, you will need `make`, `cc`, and the dependencies required by the MiniLibX library on Linux:

```bash
sudo apt-get install gcc make xorg libxext-dev libbsd-dev

```

### Compilation

Clone the repository and compile the executable using the provided Makefile:

```bash
make

```

This will compile the `libft`, `minilibx`, and the core engine files, generating the `cub3d` executable.

### Execution

Run the game by passing a valid `.cub` map file as an argument:

```bash
./cub3d maps/example.cub

```

### Controls

* **W / S:** Move forward / backward
* **A / D:** Strafe left / right
* **Left / Right Arrows:** Rotate camera (look left/right)
* **ESC (or Red X):** Quit the game cleanly

## Resources

### Documentation & Tutorials

* [Lodev's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) - The holy grail for understanding the DDA algorithm and untextured/textured raycasting math.
* [MiniLibX Unofficial Documentation](https://harm-smits.github.io/42docs/libs/minilibx) - A comprehensive guide to understanding 42's graphics library, image buffers, and hooks.
* [3D Ray-Casting Game with cub3D](https://devabdilah.medium.com/3d-ray-casting-game-with-cub3d-7a116376056a) - Article explaining the structural breakdown of the project.
* [RGB to Hex Color Conversion](https://dev.to/therealowenrees/utilising-bitwise-operators-in-javascript-by-building-a-rgb-to-hex-colour-convertor-24ai) - Helpful logic for understanding bitwise color manipulation.
* [cub3D Map Parsing Guide](https://www.google.com/search?q=https://hackmd.io/%40nszl/H1LXByIE2%23:~:text%3DThe%2520map%2520must%2520be%2520composed,Ignore%2520all%2520leading%2520whitespaces.) - Edge cases and rules for parsing the `.cub` map file.

### AI Usage

Artificial Intelligence (Large Language Models) was used during the development of this project strictly as a tutor and pair-programming assistant. AI was specifically utilized for:

1. **Mathematical Debugging:** Explaining the underlying geometry of the DDA algorithm.
2. **Physics Refinement:** Diagnosing "corner clipping" bugs in the 2D grid movement and restructuring the collision logic to support independent axis checking (Wall Sliding).
3. **General Expalantions and Bugfixing.**
