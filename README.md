# Particle Simulation on Custom Vector Fields
This is the Git repository for the Creative Coding 2 Project.
![](bin/data/img/spider.jpg)
### Overview
The software was written in C++ using the OpenFrameworks library. I wanted to be able to create cool generative art through particles interacting with a vector field. The plan was to build on my work [here](https://youtu.be/sq7wbopaGDY) taking inspiration from the oFxVectorField Addon by [Jeremy Rotsztain](https://github.com/mantissa/ofxVectorField). In order to allow the user to create vector field generative images with as much control as possible, it was important to develop a sophisticated vector field generator as well as a scene where they could add particles dynamically. This would be done on the CPU as well as on the GPU using shaders - although with less functionality. After building a very rudimentary "scene" manager, the software is split up into three scenes.

![](bin/data/img/nice3.jpg)
## Features
![](bin/data/img/nice2_.jpg)
### Main Scene (CPU)
![](bin/data/img/m2.jpg)
- Can add Particles with a "brush" using the mouse. Adds particles within the radius of the brush to a desired thickness, which can both be chosen in the GUI.
- You can change the amount of particles (too high will induce lag).
- The length of time the particle is active (the lifetime) can be selected. The default 0 means that they stop when their speed is below a certain level.
- The size and speed of particles may also be chosen as well as their colour and whether they are rendered.
- The particle paths can be toggled (if it gets too laggy, I recommend turning this off until the movement has finished).
- The colour and width of the path may also be selected.
- The particles will follow a field that is supplied (default is perlin noise).
- Toggle the rendering of the field with 'f'.
- This field can be loaded with 'l' from a file saved in the vector field creator scene.
- To clear the scene press 'c' and to save an image press 'x'.
- The background colour may also be selected.
- If the scene gets laggy, you have the option to rasterise (saves the scene as an image and sets it as the background).
### Vector Field creator
![](bin/data/img/field.png)
- The field is rendered through lines representing velocity. The bluer the line colour the greater the magnitude.
- Adjust the scale of the vector field.
- With right mouse click add a source to a desired strength. Set this strength to a negative value to add a sink.
- With left mouse click smudge the field attractively (positive smudge strength) or repulsively (negative smudge strength).
- These can be supplied within a brush with defined radius (radius of 0 affects the whole field).
- Save and load field to and from a file.
- Generate Perlin noise to a defined scale. This is seeded through customisable x and y parameters.
- Add a custom equation to the field. This may be applied to all or through the brush and middle click.
- Smooth the field subject to a desired kernel and sigma.
- Normalise the field by pressing the button.
- Divide all field strengths through a custom number,
- Clear the field (all velocities 0) or reset (uniform flow).
- Send the field to the main or the gpu.
### GPU Scene
![](bin/data/img/gpu1.png)
- Similarly add one particle or through a brush of a defined radius and thickness.
- Change the speed/timestep/size of each particle.
- Change the colour of the particles.
- Load a texture for each particle (in a similar format to the one provided for best results).
- Toggle glow effect (additive blending).
- Toggle trail.
- Save image.
- Reset and clear the scene.

### Video Demonstration
[![video](https://img.youtube.com/vi/A9vMts4HsMY/0.jpg)](https://www.youtube.com/watch?v=A9vMts4HsMY)
## The Process
In this section I will briefly (and very disjointly) mention the development process of the software including some technical challenges I experienced. I am not used to C++ so this was a good learning exercise, especially in understanding how OOP is applied in this language.
\
\
I decided to rewrite the VectorField code from scratch so it could fit into the final work more readily.
![](bin/data/img/img1.png)
\
Adding particle paths using ofPath in the Particle class. With each update it curves to the new particle's position.
![](bin/data/img/img2.png)
\
The first brush iteration (just a line). Eventually this just iterated over a square of brush radius *2 and checked whether the distance of the indices was within the radius.
![](bin/data/img/wb3.png)
\
Using ofxGUI added some controls.
![](bin/data/img/c3.jpg)
\
Since adding all of the particles within the brush seemed unnessasary (and caused lag, 1200 particles for a radius of size 20), I added a brush thickness. This just affects the step size in the iteration.
![](bin/data/img/c_thickness.jpg)
\
Adding more controls in speed, lifetime, and colour. Also added functionality to save the vector field in the generator. At first I saved to an XML file and gave all the attributes tags. This, however, took too long to save and load so I decided to encode the width,height, spacing, and all of the co-ordinates into a text file (interlaced xyxy).
![](bin/data/img/nice5.jpg)
\
The field scene had a few teething issues.
![](bin/data/img/lol2.jpg)
\
But eventually I could add sources/sinks (using equations [here](https://web.mit.edu/16.unified/www/FALL/fluids/Lectures/f15.pdf) as well as perlin noise and other controls. Below is a source in the main scene followed by a source/sink combination in a uniform flow, also known as a doublet, in the field scene.
![](bin/data/img/source.jpg)
![](bin/data/img/sourcesinkcombo.jpg)
\
These vector fields could also be sent directly to the main scene without having to save and load them.
![](bin/data/img/coolcombined.jpg)
\
Adding the capability to apply equations to the field using [exprtk](https://github.com/ArashPartow/exprtk) library. This parses the text and evaluates an output.
![](bin/data/img/sin.jpg)
\
Inspired by the vector field of a magnet, I added a smudge affect. The effect is proportional to the reciprocal to the distance squared. This gives the user the ability to draw on the field.
![](bin/data/img/draw.jpg)
\
After adding some extra features such as smoothing I decided to work on the GPU rendering. I would need a way to keep track of the particle positions for the shaders. For this I used ping pong rendering. In order to get the field data into the shader I decided to encode the field into an image and then texture. This created some very cool results.
![](bin/data/camo.png)
![](bin/data/sink.png)
![](bin/data/trippy.png)
![](bin/data/circles.png)
![](bin/data/ssource.png)
![](bin/data/nice.png)
![](bin/data/smoothedperlin.png)
![](bin/data/normalised.png)
\
Similar controls to the main scene were then implemented.

![](bin/data/circles.jpg)
\
![](bin/data/img/nice6.jpg)
\
