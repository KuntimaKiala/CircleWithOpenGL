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



  while(!glfwWindowShouldClose(window)){

    glfwPollEvents();
    glfwSwapBuffers(window) ;

  }


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