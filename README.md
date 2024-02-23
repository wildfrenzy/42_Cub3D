<div align="center">

# Cub3D

[About](#about-the-project) •
[Subject requirements](#subject-requirements) •
[Usage](#usage) •
[Useful links](#useful-links)

</div>

## About The Project
It is a group project, inspired by the world-famous **Wolfenstein 3D** game, which
was the first FPS ever.
Our goal is to make a dynamic view inside a maze, using ray-casting.

## Subject requirements

* You must use the **miniLibX**
* Display different wall textures that vary depending on which side the wall is facing (North, South, East, West).
* The left and right arrow keys of the keyboard must allow you to look left and
right in the maze.
* The W, A, S, and D keys must allow you to move the point of view through
the maze.
* Pressing ESC or on the red cross on the window’s frame must close the window and quit the program cleanly.
* Your program must take as a first argument a scene description file with the .cub extension.

 **Scene:**

 * The map must be composed of only 6 possible characters: 0 for an empty space, 1 for a wall, and N,S,E or W for the player’s start position and spawning orientation.
 * The map must be closed/surrounded by walls
 * Except for the map content which always has to be the last, each type of element can be set in any order in the file and separated by one or more empty line(s).
 * Each elements (except the map) first information is the type identifier, followed by all informations:
   * Texture:
     * **NO**, **SO**, **WE**, **EA** - North, South, West, East
       > ex: NO ./path_to_the_north_texture
   * Floor color:
     * identifier: **F**
     * **RGB** colors in range [0,255]: 0, 255, 255
       > ex: F 220,100,0
   * Ceiling color:
     * identifier: **C**
     * **RGB** colors in range [0,255]: 0, 255, 255
       > ex: C 225,30,0


## Usage

To start program:

0. Clone repo
1. Download and install MLX42 library inside of Cub3D repo: https://github.com/codam-coding-college/MLX42
2. ```sh
   make
   ./cub3D maps/0.cub
    ```

![cub3d example](https://i.imgur.com/vwV0K71.png)

## Useful links
1. https://lodev.org/cgtutor/raycasting.html
2. https://lodev.org/cgtutor/raycasting2.html
3. https://lodev.org/cgtutor/raycasting3.html
4. https://lodev.org/cgtutor/raycasting4.html
