#pragma once
#include 
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <string>

class Shader
{
private:
    GLuint handle;

public:
    Shader(const std::string &vertexPath, const std::string &fragementPath);
    
    GLuint getHandle();
    void use();
    
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;

}