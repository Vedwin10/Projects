This projects carves images seam by seam by calculating a seam of "least significant" pixels. Here's how the algorithm works:

Images are in .ppm format, which specifices pixels by providing three rgb values from 0-255, separated by a space. For example, a red pixel would be: "255 0 0".
The 'Image' class and the 'Pixel' struct represent and store these .ppm images in code, and the image_processing.cc file contains several functions that modify the Image class. 

In order to carve out a seam, the energy of a pixel is calculated by adding up the squares of the differences between the top and bottom pixels, and doing the same for the
left and right pixels, and adding up those two values. In other words, the energy of a pixel is calculated by its surrounding pixels. A border pixels energy is set to 
a maximum constant. 
Next, we calculate the cost of a pixel by adding up the energy of itself, and the minimum of the top, top left, and top right pixels. 
The minimum seam if found by going down vertically and following the line of lowest cost. 

This project was inspired by and based on a project by: Josh Hug, Kevin Wayne, Maia Ginsburg, Georges Durand, and Jule Schatz. 