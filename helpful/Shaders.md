## What are Shaders?

Shaders are little programs on the GPU that are part of the graphics pipeline

When writing shaders we mainly write Vertex,Geometry and Fragment Shader.
Shaders are written in a C-like language called GLSL. GLSL was specifically written with graphics programming
in mind and has alot of useful features targeted at vector and matrix manipulation.

The Basic GLSL Syntax is as follows:

Version declaration

In- and Output variables

uniforms

main function with return (return is send to next step in graphics pipeline)

## Input/Output Variables

when talking about the vertex shader, each variable is also known as a vertex attribute(position and rotation for example).
The maximum number of vertex attributes that we can declare is 16 on most GPUs and is limited by the GPUs hardware(some hardware may allow more).

## Data types 

GLSL has the Standard data-types common in most programming languages. it also has 2 container types that you need alot it graphics programming namely vectors and matrices.

## Swizzling 

GLSL vectors have a cool feature called swizzling which allows you access and return values by writing the components name after each other like this:

vec3 newVec = oldVec.xyz;

this would return a copy of the old vector

vec4 newVec = oldVec.xyzx;

this would return a 4-dimensional vector that has the old vectors x value as its fourth w value

vec2 newVec = oldVec.xx 

this would create a 2D-vector that has the old vectors x value as x and y value

## Ins and Outs

In the vertex shader the input is special as it comes from outside the pipeline in form of vertex data.
to know what vertex data is supposed to be accessed we declare a location before the in- and outputs (like location = 0)

in our program we need to tell OpenGl which location we use for out vertex data and we also need to enable which location we want to use.
we do that like this:

Tell OpenGL which location to store our data
> glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float),(void*)0); 
Enable this location  
> glEnableVertexAttribArray(0);


The fragment shader has also some quirks. it needs to have a vec4 as output since the output of the fragment shader is the final pixelcolor.

you can also send data from one shader to the following by declaring an out (sending site) and in (recieving site) variable. These are than linked together in the linking phase of creating a shader program. its important that these in and outputs have the same datatype.

## Uniforms

Uniforms are another way of passing data between our program running on the CPU to our shaders on the GPU. They are not the same as vertex attributes. They are global which means that they are accessible by any shader at any stage of the shader program.
