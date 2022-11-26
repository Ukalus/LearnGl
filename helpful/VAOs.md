## What is a  VAO

<br>
<br>

A **VAO** (Vertex Attribute Object) in an Object that contains one ore more VBOs (Vertex Buffer Object's) and the how the VBO data should be interpreted

How to set up a VAO:

<br>

First you create a variable to hold the ID

> unsigned int VAO;

Then you generate space on your GPUs VRAM and safe the ID of that space like so:

> glGenVertexArray(VAO);

Then you bind configure it like this:

> glVertexAttribPointer(0,3,GL_FLOAT,GL_FLASE, 3* sizeof(float),(void*)0)