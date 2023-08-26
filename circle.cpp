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




  // declaring EBO and VBO
  GLuint EBO, VBO, VAO ;
  // Creating ID's for  EBO, VBO and VAO
  glCreateVertexArrays(1, &VAO);
  glCreateBuffers(1, &EBO);
  glCreateBuffers(1, &VBO);
  // bindin/selcting the target 
  glBindVertexArray(VAO) ;
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO); 
  glBindBuffer(GL_ARRAY_BUFFER,VBO); 
  //sending the data to gpu 
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(constant::vertices), constant::vertices,GL_STATIC_DRAW);
  glBufferData(GL_ARRAY_BUFFER, sizeof(constant::indice), constant::indice,GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
  glEnableVertexAttribArray(VAO);


  //shaders vertex and fragment 
  GLuint VertexShader   = glCreateShader(GL_VERTEX_SHADER)  ;
  GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  // sourcing, compiling shaders and checking if shaders working
  glShaderSource(VertexShader, 1, &(constant::vertexShaderSource), NULL);
  glShaderSource(FragmentShader, 1, &(constant::fragementShaderSource), NULL);
  glCompileShader(VertexShader);
  ShaderCheck(VertexShader, "VERTEX") ;
  glCompileShader(FragmentShader);
  ShaderCheck(FragmentShader, "FRAGMENT") ;


  //deleting shaders, they not nedded after linkage
  glDeleteShader(VertexShader);
  glDeleteShader(FragmentShader) ;
  // program 
  GLuint program ;
  program =glCreateProgram();
  glAttachShader(program, VertexShader);
  glAttachShader(program, FragmentShader) ;
  glLinkProgram(program);
  programCheck(program) ;
  while(!glfwWindowShouldClose(window)){

    glClearColor(0.1,0.1,0.2,1.0) ;
    glClear(GL_COLOR_BUFFER_BIT) ;
    glfwPollEvents();
    glfwSwapBuffers(window) ;

  }
  
// deleting the program shader, not needed anymore
glDeleteProgram(program) ;
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


  int sucess ;
  char InfoLog[512];

  glGetShaderiv(shader, GL_COMPILE_STATUS, &sucess) ;
  if(!sucess) {
      glGetShaderInfoLog(shader, 512, NULL, InfoLog) ;
      if(shaderName==constant::ShaderNames[0])
        cout << shaderName <<"::SHADER::FAIL" << InfoLog << endl ;

  }
}

void programCheck(GLuint& program) {

  int sucess ;
  char InfoLog[512] ;
  glGetProgramiv(program, GL_LINK_STATUS, &sucess);
  glGetProgramInfoLog(program,1, NULL,InfoLog ) ;
  if(!sucess){

    cout <<"PROGRAM::SHADER::PROGRAM::FAIL" << InfoLog << endl ;

  }


}

void framebuffersize(GLFWwindow* window, int width, int height){

  glViewport(0,0, width, height) ;


}