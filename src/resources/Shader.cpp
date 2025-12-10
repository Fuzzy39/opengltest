#include <fuzzygl/resources/Shader.hpp>


Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath)
{
    std::string* vertexSource = readFile(vertexPath);
    if(vertexSource == nullptr)
    {
        std::cout<<"ERROR::SHADER::VERTEX::FILE_ERROR: Vertex Shader file '"+vertexPath+"' could not be read. Does it exist?\n";
        throw std::exception();
    }

    std::string* fragmentSource = readFile(fragmentPath);
    if(fragmentSource == nullptr)
    {
        std::cout<<"ERROR::SHADER::FRAGMENT::FILE_ERROR: Fragment Shader file '"+fragmentPath+"' could not be read. Does it exist?\n";
        throw std::exception();
    }


    if(!compileShaders(vertexSource, fragmentSource))
    {
        free(vertexSource);
        free(fragmentSource);

        throw std::exception();
    }

    free(vertexSource);
    free(fragmentSource);


}

std::string* Shader::readFile(const std::string &path)
{
    std::ifstream file(path);
    
    // check if file exists
    if(file.fail()) return nullptr;
   
    char buffer[128]; // arbitrary size array, go!

    std::string* contents = new std::string();

    while(!file.eof())
    {
        file.getline(buffer, sizeof(buffer)/sizeof(char));
        //std::cout<<"Got line: "<<buffer<<"\n";
        contents->append(buffer);
        contents->append("\n");
    }
    file.close();    
    //std::cout<<"Contents: "<<contents->c_str();
    return contents;
}


bool Shader::compileShaders(std::string* vertexShaderSource, std::string* fragmentShaderSource)
{
 
    // SETUP shaders
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // put our source in the shader and compile it.
    const char* vertSource = vertexShaderSource->c_str();
    glShaderSource(vertexShader, 1, &vertSource, NULL);
    glCompileShader(vertexShader);

    //check if comilation succeeded.
    int  success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }


    // fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // put our source in the shader and compile it.
    const char* fragSource = fragmentShaderSource->c_str();
    glShaderSource(fragmentShader, 1, &fragSource, NULL);
    glCompileShader(fragmentShader);

    // check if it worked.
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE)
    {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        glDeleteShader(vertexShader);
        return false;
    }

    // make a program
 
    handle = glCreateProgram();

    glAttachShader(handle, vertexShader);
    glAttachShader(handle, fragmentShader);
    glLinkProgram(handle);

    glGetProgramiv(handle, GL_LINK_STATUS, &success);
    if (success != GL_TRUE)
    {
        char infoLog[512];
        glGetProgramInfoLog(handle, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return false;
    }


    // wrap up.
    glUseProgram(handle);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    return true;
}

GLuint Shader::getHandle()
{
    return handle;
}

void Shader::use()
{
    glUseProgram(handle);
}

void Shader::setBool(const std::string &name, bool value) const
{ 
    int uniformLocation = glGetUniformLocation(handle, name.c_str());
    glUseProgram(handle);
    glUniform1i(uniformLocation, value);
}

void Shader::setInt(const std::string &name, int value) const
{
    int uniformLocation = glGetUniformLocation(handle, name.c_str());
    glUseProgram(handle);
    glUniform1i(uniformLocation, value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    int uniformLocation = glGetUniformLocation(handle, name.c_str());
    glUseProgram(handle);
    glUniform1f(uniformLocation, value);
}
