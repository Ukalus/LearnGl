# About this project

This repo tracks my progress in understanding OpenGl by completing the "Learn OpenGl" tutorial by Joe de Vries on this really helpful website:

https://learnopengl.com


## Depedencies:

Libaries needed 

**openGl**
<br>
**glad**
<br>
**glfw**

Opengl itself is just a specification, there is no real "OpenGl Library" that stores specific function definitions. The functions can differ on each graphicscard(newer features, new algorithims, etc.), so **OpenGl** just specifies their rough layout in form of a wrapper library.

We would have to wrap each function manually, which would not be fun, thats why we use a Library called **GLAD** to wrap the functions automatically.

We also need a window and user input, for that we use the **GLFW** library.

i strongly recommend to read the chapter about how to create a window before compiling:

https://learnopengl.com/Getting-started/Creating-a-window

https://www.glfw.org
https://glad.dav1d.de/

this link also helped me compile glfw:
https://www.glfw.org/docs/3.3/compile.html

## Tips for compilation:

through alot of trial and error i have found numerous ways on how to **_not_** compile a OpenGl project. Here are a few tips that might help you, to not want to bash you head against a wall :).

- while compiling **glfw** you need to go through 3 steps:
    1. > cmake build => creates your makefiles
    2. > make => compiles the library 
    3. > make install => installs the library on your system (dont forget this step!)

- after downloading **glad** (on linux) make sure you you have the right permissions set for the library files else your compiler or IDE wont be able to use them to compile your project.

- dont use **gcc** when compiling a .cpp file ;) use **g++** 

this is how your compile command could look:

> g++ ./main.cpp ./glad/src/glad.c -lm -lGL -lglfw3 -o run 

