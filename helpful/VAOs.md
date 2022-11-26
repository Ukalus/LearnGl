## What is a  VAO

<br>
<br>

A **VAO** (Vertex Attribute Object) in an Object that contains one ore more VBOs (Vertex Buffer Object's) and the how the VBO data should be interpreted

How to set up a VAO:

<br>

First you create a variable to hold the ID

> unsigned int VAO;

Then you Create a Space on your GPUs VRAM like so:

> glGenBuffer(GL_ATTRIBUTE_ARRAY)