#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <cmath>



// Function declaration
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void changeRenderTri(float verts[], int vertSize, unsigned int VBO, unsigned int VAO, unsigned int *refVBO, unsigned *refVAO);
std::string getShader(std::string filepath);
void compileShader(unsigned int &vramShaderLoc,const char* shaderPtr, GLenum shaderType);
void createShaderProgram(unsigned int shaderProgram, unsigned int vertexShader, unsigned int fragmentShader);

float Triangle[] = {
        //position           //color
        -0.9f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
        -0.0f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
        -0.45f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
         0.9f, -0.5f, 0.0f,  0.0f, 0.0f, 0.0f,
         0.45f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f
};

unsigned int indices[] = {
    0,2,1,
    1,2,4,
    4,1,3,
  
};

unsigned int indices2[] = {
     1,2,4,
};


 
int main() {
    std::string vertexString = getShader("shader/triTriangle.vertex");
    std::string orangeFragmentString = getShader("shader/orange.fragment");
    std::string yellowFragmentString = getShader("shader/yellow.fragment");
    const char* orangeFragmentShaderSource = orangeFragmentString.c_str();
    const char* yellowFragmentShaderSource = yellowFragmentString.c_str();
    const char* vertexShaderSource = vertexString.c_str();

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


    

 
    unsigned int vertexShader,orangeFragmentShader,yellowFragmentShader;

    compileShader(vertexShader,vertexShaderSource,GL_VERTEX_SHADER);
    compileShader(orangeFragmentShader,orangeFragmentShaderSource,GL_FRAGMENT_SHADER);
    compileShader(yellowFragmentShader,yellowFragmentShaderSource,GL_FRAGMENT_SHADER);
  

    int success;
    char infoLog[512];
    
    unsigned int orangeShaderProgram,yellowShaderProgram,blueShaderProgram;
    // load empty shader program object into it 
    
    orangeShaderProgram = glCreateProgram();
    yellowShaderProgram = glCreateProgram();

    createShaderProgram(orangeShaderProgram,vertexShader,orangeFragmentShader);
    createShaderProgram(yellowShaderProgram,vertexShader,yellowFragmentShader);
   // i need to understand this step more!

    // Uniform Code magic 

    

    unsigned int VBO[2], VAO[2], EBO[2]; 
    
    glGenVertexArrays(2,VAO);
    glGenBuffers(2,VBO);
    glGenBuffers(2,EBO);
    
    glBindVertexArray(VAO[0]);
    glBindVertexArray(VAO[1]);

    glBindBuffer(GL_ARRAY_BUFFER,VBO[0]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(Triangle),Triangle,GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER,VBO[1]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(Triangle),Triangle,GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices2),indices2,GL_STATIC_DRAW);
    

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6 * sizeof(float),(void*)0);   
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    
  // Update loop in which Input and Bufferswapping happens   
    while(!glfwWindowShouldClose(window))
{
    // input
    processInput(window);
    
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
    glUseProgram(yellowShaderProgram);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO[0]);
    glDrawElements(GL_TRIANGLES,9,GL_UNSIGNED_INT,0);
    glUseProgram(orangeShaderProgram);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO[1]);
    glDrawElements(GL_TRIANGLES,9,GL_UNSIGNED_INT,0);
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
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
          
    } 
     if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS){
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
    } 

      
}  
//Render Triangle

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

void createShaderProgram(unsigned int shaderProgram,unsigned int vertexShader, unsigned int fragmentShader){
    int success;
    char infoLog[512];
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram,GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram,512, NULL, infoLog);
        std::cout << "ERROR::SHADER::SHADER_PROGRAM::COMPILATION_FAILED\n";
        
    }
    // Delete the Shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}