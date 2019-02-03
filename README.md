# RayTracer

## About the program
  It's just a naive Ray Tracer using no libraries
  The fov effect is implemented, You can change the angle (in deg) in the `main.c` line 18 `s.obs = ...` 4th argument.
  You only can add spheres, pushing back the `s.spheres` vector, in the `main.c` (same for lights and materials).
##
    1: sphere arguments : 1 : center (vector), 2 : radius, 3 : material index.
    2: material arguments : 1 : color (r,g,b), 2 : reflection, 3 : transparancy (not implemented yet).
    3: observator arguments : 1 : camera position, 2 : camera Z orientation, 3 : camera Y orientation, 4: Fov, 5&6 : width&height
    
##

I assume how this first version isn't such comfortable, at least to edit the scene. I will add xml parsing possibilities in future updates.

## Result with this scene configuration

![sample result of basic scene configuration](https://images-wixmp-ed30a86b8c4ca887773594c2.wixmp.com/intermediary/f/3bad3b3a-3db4-4a00-b8d9-0c35d1c1de9c/dcytjhp-098e5035-8a7b-40a0-99ba-7b8da2001a3c.png)
