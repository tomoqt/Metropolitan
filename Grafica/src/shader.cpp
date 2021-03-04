#include <shader/shader.h>

Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
    string vertexCode;
    string fragmentCode;
    string geometryCode;
    ifstream vShaderFile, fShaderFile, gShaderFile;
    vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    gShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        if (geometryPath != nullptr)
        {
            gShaderFile.open(geometryPath);
            stringstream gShaderStream;
            gShaderStream << gShaderFile.rdbuf();
            gShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (ifstream::failure e)
    {
        cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    unsigned int vertex, fragment, geometry;
    
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileError(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileError(fragment, "FRAGMENT");

    if (geometryPath != nullptr)
    {
        const char* gShaderCode = geometryCode.c_str();
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &gShaderCode, NULL);
        glCompileShader(geometry);
        checkCompileError(geometry, "GEOMETRY");
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    if (geometryPath != nullptr)
        glAttachShader(ID, geometry);
    glLinkProgram(ID);
    checkCompileError(ID, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if (geometryPath != nullptr)
        glDeleteShader(geometry);
}
void Shader::use()
{
    glUseProgram(ID);
}
/*
void Shader::set(const string& name, bool value) const //bool
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);    //bool1
}
void Shader::set(const string& name, int value) const                                   //int1
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::set(const string& name, int valuex, int valuey) const                      //int2
{
    glUniform2i(glGetUniformLocation(ID, name.c_str()), valuex, valuey);
}
void Shader::set(const string& name, int valuex, int valuey, int valuez) const          //int3
{
    glUniform3i(glGetUniformLocation(ID, name.c_str()), valuex, valuey, valuez);
}
void Shader::set(const string& name, int valuex, int valuey, int valuez, int valuew) const //int4
{
    glUniform4i(glGetUniformLocation(ID, name.c_str()), valuex, valuey, valuez, valuew);
}
void Shader::set(const string& name, float value) const                                         //float1
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::set(const string& name, float valuex, float valuey) const                          //float2
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), valuex, valuey);
}
void Shader::set(const string& name, float valuex, float valuey, float valuez) const            //float3
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), valuex, valuey, valuez);
}
void Shader::set(const string& name, float valuex, float valuey, float valuez, float valuew) const//float4
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), valuex, valuey, valuez, valuew);
}
void Shader::set(const string& name, const glm::vec2& value) const   //vec2
{
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::set(const string& name, const glm::vec3& value) const   //vec3
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::set(const string& name, const glm::vec4& value) const   //vec4
{
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::set(const string& name, const glm::mat2& value) const   //mat2x2
{
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
void Shader::set(const string& name, const glm::mat3& value) const   //mat3x3
{
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
void Shader::set(const string& name, const glm::mat4& value) const   //mat4x4
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
*/

void Shader::checkCompileError(unsigned int shader, string type) const
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}