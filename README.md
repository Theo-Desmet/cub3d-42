#cub3D

cub3D is a small 3D game project developed as part of the 42 cursus. It's a labyrinth game in first-person view in which the player navigates through a maze. We had to use ray-casting to achieve the rendering.
Overview

The game is inspired by Wolfenstein 3D, using raycasting. It was created in C using the MiniLibX library.
Installation

Clone the repository including the MiniLibX and libft submodules:

# Clone this repository
git clone git@github.com:Theo-Desmet/cub3d-42.git

# Go into the repository
```cd cub3D-42```

Compile and Run

There are two versions of the projet, the mandatory part and the bonus part. The madatory version is simply a raycaster, while the bonus version adds a minimap, walls collisions, textured roof and ceil, animated sprites, "living" entity, fog effect and the ability to rotate the view by moving the mouse.

If you want to compile the 'mandatory' version, run:

```make```

If you prefer to compile the 'bonus' version, run:

```make bonus```

To run the program:

```./cub3D <path_to_map.cub> # Mandatory version```
# Or
```./cub3D_bonus <path_to_map.cub> # Bonus version```

The executable takes a map file as an argument. Here are some examples of maps in maps directory The 'bonus' maps won't work with mandatory version due to unrecognized symbols.
Controls

    W: Move forward
    S: Move backward
    A: Strafe left
    D: Strafe right
    left arrow: Rotate left
    right arrow: Rotate right
    mouse: Rotate by moving the mouse (only work on bonus part)
    CTRL: Play shooting animation (doesn't do anything, simply an animation, only work on bonus part)
