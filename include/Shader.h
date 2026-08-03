#ifndef SHOOTER_SHADER_H
#define SHOOTER_SHADER_H

#include <glad/glad.h>
#include <string>


class Shader {
public:
    //ID of the program compiled on the GPU
    unsigned int ID;

    //The constructor read and build the shader
    Shader(const char* vertexPath, const char* fragmentPath);

    void useShader();
    void deleteShader();
    void setFloat(const std::string &name, float value);
    void setVec4(const std::string &name, float x, float y, float z, float w);

private:
    //Function to check for compilation and linking errors
    static void checkCompileErrors(unsigned int shader, std::string type);
};
#endif //SHOOTER_SHADER_H
