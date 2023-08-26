#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "constants.h"
#include <iostream> 


using std::endl ;
using std::cout ;


void init() ;
void framebuffersize(GLFWwindow* window, int width, int height ) ;
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
    goto Exit ; // its jumps to two lines before return 0;
  }

  
  

  while(!glfwWindowShouldClose(window)){

    glClearColor(0.1,0.1,0.2,1.0) ;
    glClear(GL_COLOR_BUFFER_BIT) ;
    glfwPollEvents();
    glfwSwapBuffers(window) ;

  }

Exit :
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


void framebuffersize(GLFWwindow* window, int width, int height){

  glViewport(0,0, width, height) ;


}