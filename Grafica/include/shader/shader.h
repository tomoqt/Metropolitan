#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;
class Shader
{
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
    void use();
    //void set(const string& name, bool value) const;             //bool
    //void set(const string& name, int value) const;                                                  //int1
    //void set(const string& name, int valuex, int valuey) const;                                     //int2
    //void set(const string& name, int valuex, int valuey, int valuez) const;                         //int3
    //void set(const string& name, int valuex, int valuey, int valuez, int valuew) const;             //int4
    //void set(const string& name, float value) const;                                                //float1
    //void set(const string& name, float valuex, float valuey) const;                                 //float2
    //void set(const string& name, float valuex, float valuey, float valuez) const;                   //float3
    //void set(const string& name, float valuex, float valuey, float valuez, float valuew)const;      //float4
    //void set(const string& name, const glm::vec2& value) const;    //vec2
    //void set(const string& name, const glm::vec3& value) const;   //vec3
    //void set(const string& name, const glm::vec4& value) const;   //vec4
    //void set(const string& name, const glm::mat2& value) const;   //mat2x2
    //void set(const string& name, const glm::mat3& value) const;   //mat3x3
    //void set(const string& name, const glm::mat4& value) const;   //mat4x4

private:
    void checkCompileError(unsigned int shader, string type) const;
};

#endif