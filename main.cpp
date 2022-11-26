#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>



// Function declaration
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void changeRenderTri(float verts[], int vertSize, unsigned int VBO, unsigned int VAO, unsigned int *refVBO, unsigned *refVAO);
std::string getShader(std::string filepath);
void compileShader(unsigned int &vramShaderLoc,const char* shaderPtr, GLenum shaderType);

float Triangle[] = {
 // first triangle
        -0.9f, -0.5f, 0.0f,  // left 
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top 
        // second triangle
         0.0f, -0.5f, 0.0f,  // left
         0.9f, -0.5f, 0.0f,  // right
         0.45f, 0.5f, 0.0f   // top 
};



 
int main() {
    std::string vertexString = getShader("shader/vertexShader.ukalus");
    std::string fragmentString = getShader("shader/fragmentShader.ukalus");
    const char* fragmentShaderSource = fragmentString.c_str();
    const char* vertexShaderSource = vertexString.c_str() ;

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
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnGl", NULL, NULL);
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


 
    unsigned int vertexShader,fragmentShader;

    compileShader(vertexShader,vertexShaderSource,GL_VERTEX_SHADER);
    compileShader(fragmentShader,fragmentShaderSource,GL_FRAGMENT_SHADER);
  

    int success;
    char infoLog[512];
    
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
    // Delete the Shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


   // i need to understand this step more!
    unsigned int VBO, VAO; 
    
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(Triangle),Triangle,GL_STATIC_DRAW);

    
    glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,3 * sizeof(float),(void*)0);   
    glEnableVertexAttribArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // Update loop in which Input and Bufferswapping happens   
    while(!glfwWindowShouldClose(window))
{
    // input
    processInput(window);
    
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

    glUseProgram(shaderProgram);
 
    glDrawArrays(GL_TRIANGLES,0,6);

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
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }   
}  
//Render Triangle

// Doesnt work
void changeRenderTri(float verts[],int vertSize,unsigned int VBO,unsigned int VAO,unsigned int *refVBO,unsigned int *refVAO)
{
    glGenVertexArrays(1,refVBO);
    glGenBuffers(1,refVAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,vertSize,verts,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
}

std::string getShader(std::string filepath)
{
    std::ifstream shaderFile;
    std::string shaderString;
    shaderFile.open(filepath);
    if(shaderFile.is_open()){
        std::string line;
        while(getline(shaderFile,line)){
            shaderString = shaderString + line + "\n";
        }
        shaderFile.close();

    }
    std::cout << "### SHADER LOADED ###" << std::endl << shaderString << std::endl;
    return shaderString;
}

void compileShader(unsigned int &vramShaderLoc,const char* shaderPtr, GLenum shaderType ){
    vramShaderLoc = glCreateShader(shaderType);
    glShaderSource(vramShaderLoc,1, &shaderPtr,NULL);
    glCompileShader(vramShaderLoc);

    int success;
    char infoLog[512];
    glGetShaderiv(vramShaderLoc, GL_COMPILE_STATUS, &success);
    // check if success is true 
    if(!success)
    {
        glGetShaderInfoLog(vramShaderLoc,512,NULL,infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n";
    }
}