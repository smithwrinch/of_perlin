# Particle Simulation on Custom Vector Fields
This is the Git repository for the Creative Coding 2 Project.
![](bin/data/img/spider.jpg)
### Overview
The software was written in C++ using the OpenFrameworks library. I wanted to be able to create cool generative art through particles interacting with a vector field. The plan was to build on my work [here](https://youtu.be/sq7wbopaGDY) taking inspiration from the oFxVectorField Addon by [Jeremy Rotsztain](https://github.com/mantissa/ofxVectorField). In order to allow the user to create vector field generative images with as much control as possible, it was important to develop a sophisticated vector field generator as well as a scene where they could add particles dynamically. This would be done on the CPU as well as on the GPU using shaders - although with less functionality. After building a very rudimentary "scene" manager, the software is split up into three scenes.

## Features
### Main Scene (CPU)
![](bin/data/img/m2.jpg)
- Can add Particles with a "brush" using the mouse. Adds particles within the radius of the brush to a desired thickness, which can both be chosen in the GUI.
- You can change the amount of particles (too high will induce lag).
- The length of time the particle is active (the lifetime) can be selected. The default 0 means that they stop when their speed is below a certain level.
- The size and speed of particles may also be chosen as well as their colour and whether they are rendered.
- The particle paths can be toggled (if it gets too laggy, I recommend turning this off until the movement has finished).
- The colour and width of the path may also be selected.
- The particles will follow a field that is supplied (default is perlin noise).
- You can toggle the rendering of the field with 'f'.
- This field can be loaded with 'l' from a file saved in the vector field creator scene.
- To clear the scene press 'c' and to save an image press 'x'.
- The background colour may also be selected.
- If the scene gets laggy, you have the option to rasterise (saves the scene as an image and sets it as the background).
### Vector Field creator
![](bin/data/img/field.png)


### GPU Scene (Beta)
