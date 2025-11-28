#include <Shader.hpp>
#include <iostream>
#include <fstream> 

Shader::Shader(const std::string &vertexPath, const std::string &fragementPath)
{
    // do things, I guess
    // first, read from file.
    std::ifstream vertexFile(vertexPath);
    // check if file exists


}

GLuint Shader::getHandle()
{
    return GLuint();
}

void Shader::use()
{
}

void Shader::setBool(const std::string &name, bool value) const
{
}

void Shader::setInt(const std::string &name, int value) const
{
}

void Shader::setFloat(const std::string &name, float value) const
{
}
