#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


// Function "heads"
// TODO what does it do exactly?
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
// All hardcoded data

// Raw vertex data 

float vertices[] = {
    -0.5f,-0.5f,0.0f,
     0.5f,-0.5f,0.0f,
     0.0f, 0.5f,0.0f
};
// Vertex shader pre-compiled
    const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
        "gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
    "}\n"
    ";\0";

 // Fragment Shader pre-compiled
    const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"

    "void main()\n"
    "{\n"
        "FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
    "};\0";

int main() {

    // Initialize glfw
    glfwInit();

    // Setting the correct opengl version in glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Setting the opengl profile  to core in glfw
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    // important for apple? seems to enable foreward compatibility? not sure what that means
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
    // creating a glfw window object 
    GLFWwindow* window = glfwCreateWindow(1200, 800, "LearnOpenGL", NULL, NULL);
    // check if window could be created. if not: close 
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // make context current? seems like you can have multiple windows and switch them in and out?
    glfwMakeContextCurrent(window);
    // check if the window context could be created. if not: close
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // a callback function that runs everytime the size of the window is changed
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    // OpenGl Code 

    // create a glviewport? what is the difference between glViewport and the glfw window?
    glViewport(0, 0, 800,800);
    // create vertex buffer object
    unsigned int VBO;
    // generate VBO + Id on some sort of memory?
    glGenBuffers(1,&VBO);
    // bind VBO to GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    // no clue what this does?
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);


    // Shaders
    int success;
    char infoLog[512];
    // Compiling Vertex Shader 
    
    // create space for vertex shader
    unsigned int vertexShader;
    // load an unconfigured vertex shader object into it
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // load our raw vertex data into the vertexshader object 
    glShaderSource(vertexShader,1,&vertexShaderSource, NULL);
    // compile this vertex shader object
    glCompileShader(vertexShader);

    // load compile status of the vertex shader object into success variable 
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    // check if success is true 
    if(!success)
    {
        glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n";
    }

    //Compiling fragment shader 
    // same as fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    if(!success)
    {
        glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n";
    }
    
    //Linking shader object

    //Create shader program
    unsigned int shaderProgram;
    // load empty shader program object into it 
    shaderProgram = glCreateProgram();
    // attach the compiled vertex and fragment object to the shader object 
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // link the shader program... but to what?
    glLinkProgram(shaderProgram);
    // check if linking was successful
    glGetProgramiv(shaderProgram,GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram,512, NULL, infoLog);
        std::cout << "ERROR::SHADER::SHADER_PROGRAM::COMPILATION_FAILED\n";
        
    }
    // Use program? how?
    glUseProgram(shaderProgram);
    // Delete the Shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    // something to do with the spacing of the raw vertice data?
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float),(void*)0);
    // honestly no idea but 0 is the id of the object that is being enabled?
    glEnableVertexAttribArray(0);


    
  // Update loop in which Input and Bufferswapping happens   
    while(!glfwWindowShouldClose(window))
{
    // input
    processInput(window);
    // swap buffer
    glfwSwapBuffers(window);
    // dont know?
    glfwPollEvents();    
}
// exit program
glfwTerminate();
return 0;

//function definitions

// resizing viewport
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
// process input
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}  