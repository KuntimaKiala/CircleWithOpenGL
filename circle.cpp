#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "constants.h"
#include <iostream> 


using std::endl ;
using std::cout ;


void init() ;
void framebuffersize(GLFWwindow* window, int width, int height ) ;
void ShaderCheck(GLuint&, const char*) ;
void programCheck(GLuint&) ;
int main(){

  /*initializing glfw and creating the window*/
  init();
  GLFWwindow* window = glfwCreateWindow(constant::width, constant::height, "circle", NULL, NULL) ;
  glfwMakeContextCurrent(window) ;
  glfwSetFramebufferSizeCallback(window, framebuffersize) ;

  // checking if openGL function are being called 
  int gladFailed = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) ;
  if (!gladFailed) {
    cout <<"GLAD::FAILURE"<<endl;
  
  }




  // program 
  
  //shaders vertex 
  GLuint vertexShader   = glCreateShader(GL_VERTEX_SHADER)  ;
  // sourcing, compiling shaders and checking if shaders working
  glShaderSource(vertexShader, 1, &(constant::vertexShaderSource), NULL);
  glCompileShader(vertexShader);
  ShaderCheck(vertexShader, "VERTEX") ;
  
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &(constant::fragementShaderSource), NULL);
  glCompileShader(fragmentShader);
  ShaderCheck(fragmentShader, "FRAGMENT") ;

  GLuint shaderProgram =glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader) ;
  glLinkProgram(shaderProgram);
  programCheck(shaderProgram) ;
  
  //deleting shaders, they not nedded after linkage
  //glDeleteShader(vertexShader);
  //glDeleteShader(fragmentShader) ;


  // declaring EBO and VBO
  GLuint EBO, VBO, VAO ;
  // Creating ID's for  EBO, VBO and VAO
  glCreateVertexArrays(1, &VAO);
  glCreateBuffers(1, &VBO);
  glCreateBuffers(1, &EBO);
  

  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(VAO) ;
  // bindin/selcting the target  sending the data to gpu 
  glBindBuffer(GL_ARRAY_BUFFER,VBO); 
  glBufferData(GL_ARRAY_BUFFER, sizeof(constant::vertices), constant::vertices,GL_STATIC_DRAW);
   // bindin/selcting the target  sending the data to gpu 
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO); 
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(constant::indices), constant::indices,GL_STATIC_DRAW);
  
  
  
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER ,0);
  glBindVertexArray(0); 
  


  // get the location for every uniform data, shader look constants.h, shaders, -->glsl
  GLuint radiusLocation = glGetUniformLocation(shaderProgram, "radius");
  GLuint colorLocation  = glGetUniformLocation(shaderProgram, "Color");
  GLuint widthLocation  = glGetUniformLocation(shaderProgram, "width");
  GLuint heightLocation = glGetUniformLocation(shaderProgram, "height");  
  GLuint mouseLocation = glGetUniformLocation(shaderProgram,  "mouse");
  
  while(!glfwWindowShouldClose(window)){

    glClearColor(0.1,0.1,0.2,1.0) ;
    glClear(GL_COLOR_BUFFER_BIT) ;
    
    
    glUseProgram(shaderProgram);
    glUniform1f(radiusLocation, constant::radius);
    glUniform4f(colorLocation,  constant::color->red, constant::color->green, constant::color->blue, constant::color->alpha);
    glUniform1f(widthLocation,  static_cast<GLfloat>(constant::width));
    glUniform1f(heightLocation, static_cast<GLfloat>(constant::height));
    glUniform2f(mouseLocation, 0.0f,0.0f) ;
    

    

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 ) ;
    
    //glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    //glBindVertexArray(0);
    
    glfwPollEvents();
    glfwSwapBuffers(window);
    

  }

// deleting the program shader, not needed anymore
glDeleteProgram(shaderProgram) ;
glfwTerminate();
return 0 ;

}


void init(){

  cout << "Nous sommes Ubuntu" << endl;
  
  glfwInit() ;
  glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE) ;
  


}

void ShaderCheck(GLuint& shader, const char* shaderName) {


  int sucess =0;
  char InfoLog[512];

  glGetShaderiv(shader, GL_COMPILE_STATUS, &sucess) ;
  if(!sucess) {
      glGetShaderInfoLog(shader, 512, NULL, InfoLog) ;
      cout << shaderName <<"::SHADER::FAIL\n" << InfoLog << endl ;

  }
}

void programCheck(GLuint& program) {

  int success ;
  char InfoLog[512] ;

  glGetProgramiv(program, GL_LINK_STATUS, &success);
  glGetProgramInfoLog(program,512, NULL, InfoLog ) ;
  if(!success){
    cout <<"ERROR::PROGRAM::SHADER::LINKING_FAILED\n" <<success << InfoLog << endl ;

  }


}

void framebuffersize(GLFWwindow* window, int width, int height){

  glViewport(0,0, width, height) ;


}