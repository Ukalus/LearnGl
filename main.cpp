#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <cmath>

class UkalusShader{
    std::string filepath;
    std::string shaderString;
    GLenum shaderType;
    unsigned int vramShaderLoc;
    
    public:
    UkalusShader(std::string newFilepath,GLenum newShaderType){
        filepath = newFilepath;
        shaderType = newShaderType;
        std::ifstream shaderFile;
    shaderFile.open(filepath);
    if(shaderFile.is_open()){
        std::string line;
        while(getline(shaderFile,line)){
            shaderString = shaderString + line + "\n";
        }
        shaderFile.close();

    }
    std::cout << "### SHADER LOADED from Class ###" << std::endl << shaderString << std::endl;
    
    const char* shaderFileString = shaderString.c_str();
    
    
    vramShaderLoc = glCreateShader(shaderType);
    glShaderSource(vramShaderLoc,1, &shaderFileString,NULL);
    glCompileShader(vramShaderLoc);

    int success;
    char infoLog[512];
    glGetShaderiv(vramShaderLoc, GL_COMPILE_STATUS, &success);
    // check if success is true 
    if(!success)
    {
        glGetShaderInfoLog(vramShaderLoc,512,NULL,infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED in Class\n";
    }
    else{
        std::cout << "Shader compiled in class :)\n\n";
    }
    }
    unsigned int getShader(){
        return vramShaderLoc;
    }
   

};

class UkalusShaderProgram{
    int success;
    char infoLog[512];
    unsigned int vertexShader;
    unsigned int fragmentShader;

    public:
    unsigned int shaderProgram;


    public:
    UkalusShaderProgram(UkalusShader newVertexShader, UkalusShader newFragmentShader){
        shaderProgram = glCreateProgram();
        vertexShader = newVertexShader.getShader();
        fragmentShader = newFragmentShader.getShader();
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
    unsigned int getProgram(){
        return shaderProgram;
    }
};

class UkalusTexture{

};
// Function declaration
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void changeRenderTri(float verts[], int vertSize, unsigned int VBO, unsigned int VAO, unsigned int *refVBO, unsigned *refVAO);
void createShaderProgram(unsigned int shaderProgram, unsigned int vertexShader, unsigned int fragmentShader);

float Triangle[] = {
        //position           //color
        -0.45f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
        -0.45f,-0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
         0.45f,-0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
         0.45f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
};


unsigned int indices[] = {
     0,1,2,
     0,2,3
};


 
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

    // TEST AREA //

    UkalusShader ukalusShaderVert("shader/triTriangle.vertex",GL_VERTEX_SHADER);
    UkalusShader ukalusShaderFrag("shader/orange.fragment",GL_FRAGMENT_SHADER);
    
    UkalusShaderProgram ukalusShaderProgram(ukalusShaderVert,ukalusShaderFrag);

    unsigned int VBO, VAO, EBO; 
    
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(Triangle),Triangle,GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    
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
    glUseProgram(ukalusShaderProgram.shaderProgram);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
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
