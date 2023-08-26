#pragma once 



namespace constant {

    inline constexpr int width  = 700 ;
    inline constexpr int height = 700 ;
    inline constexpr float vertices[] = {
                                        // first triangle
                                        -1.0f, 1.0f, 0.0f, //top left 
                                         1.0f,-1.0f, 0.0f, //bottom right
                                        -1.0f,-1.0f, 0.0f, //bottom left
                                        // second triangle 
                                         1.0f, 1.0f, 0.0f

                                        
                                        
                                        } ;

    inline constexpr int indice[] = {
                                        // first triangle
                                        0, 1, 2,
                                        // second triangle 
                                        0, 1, 3,
                                        } ;

    inline constexpr char* ShaderNames[]    = {"FRAGMENT", "VERTEX"}        ;                    
    struct Mouse
    {   Mouse(double x, double y) : x(0), y(0){}
        double x, y;

    };
    
    inline  constexpr char * vertexShaderSource   = R"(
                                   #version 330 core
                                   layout (location = 0) in vec2 position ;

                                   uniform vec2 mouse ;
                                
                                   void main() {
                                   gl_Position = vec4(position.x  , position.y, 0.0, 1.0);})" ;

  
    inline  constexpr char *fragementShaderSource = R"(
                                   #version 330 core 
                                    out vec4 fragColor ;
				    uniform float radius ;
				    uniform vec4 Color ;
				    uniform float width ;
				    uniform float height ;
				    uniform vec2 mouse ;
				    void main(){


vec2 resolution = vec2(((width -gl_FragCoord.x)/width)*2-1.0 + mouse.x , ((height-gl_FragCoord.y)/height)*2-1 + mouse.y);
                                     if(length(resolution) <  radius) {
                                                        fragColor = 0.5*Color; 
                                                    }
                                     else fragColor = vec4(0.2f, 0.3f, 0.3f, 1.0f);
                                                    
                                                })" ;

}
//fragColor = Color ;
