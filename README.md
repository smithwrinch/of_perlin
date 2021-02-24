
# Learning OpenFrameworks: Realtime Perlin Noise Vector Fields

This repo was created to learn more about how to use Openframeworks, as well as generate some cool generative art using Perlin Noise Fields.

## The process

I used the ofxVectorField add-on by Jeremy Rotsztain (which can be found [here](https://github.com/mantissa/ofxVectorField)).

#### Iteration 1
![alt text](1.png)
As you can see there were some unwanted straight line artefacts when the particles went off screen
#### Iteration 2
![alt text](2.png)
Removed this artefacts by not updating the paths when the particles left the screen.
#### Iteration 3
![alt text](3.png)
Added controls such that you could generate a new field, toggle rendering of particles (not seen in the images), and toggling rendering the vector field that the particles follow.
#### Iteration 4
![alt text](4.png)
![alt text](5.png)
Extended controls to allow for resetting the particles to their original positions. Added a lifetime to the particles.
#### Iteration 5
![alt text](8.png)
![alt text](9.png)
![alt text](10.png)
Adjusted the field generation.
