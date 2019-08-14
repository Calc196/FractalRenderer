# Fractal Renderer

Fractal Renderer is a lightweight hardware accelerated real time ray marching renderer capable of rendering complex shapes. Written in C++ and GLSL, the renderer can produce images of any shape you can define a distance function for - not just fractals. At the core of the renderer's magic lies the ray marching fragment shader which is adapted from [Sebastian Lague's Unity compute shader.](https://github.com/SebLague/Ray-Marching) This renderer is a work in progress developed by Callum Cartwright.

The images below are rendered using the Fractal Renderer. They depict a 3D fractal known as the mandlebulb.

![Mandlebulb](/Images/Mandlebulb1.png) ![Mandlebulb](/Images/Mandlebulb2.png) ![Mandlebulb](/Images/Mandlebulb3.png)

### Controls
The Fractal Renderer supports two types of camera movement: first person and third person (centred on the fractal).

* F - toggles the camera's viewing mode (first or third person)
* E - toggles locking the mouse, allowing movement of the camera's viewing angle
* ESC - quits the program
* W - move forward
* A - move left
* S - move backward
* D - move right
* SPACE - move up
* Z - move down
* K - quickly increases the power of the fractal
* L - quickly decreases the power of the fractal
* PERIOD (.) - slowly increases the power of the fractal
* COMMA (,) - slowly decreases the power of the fractal

### Dependencies

To use the Fractal Renderer you will need SDL2 (Simple Direct Media Layer) and OpenGL (v. 3+) and the headers from GLM (Graphics Library Maths). 

To get the project to run using Xcode, you will need to link the first of these two libraries in 'Build Phases' and show the compiler where to find the include paths for all three in 'Build Settings'. Finally you will need to change the project's working directory to equal the location of the project itself so that it can find and compile the shader files.
