#pragma once
#include <common_includes.hpp>

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
    void setMat4(const std::string &name, glm::mat4 value) const;

private:
    std::string* readFile(const std::string &path);
    bool compileShaders(std::string* vertexShaderSource, std::string* fragmentShaderSource);

};