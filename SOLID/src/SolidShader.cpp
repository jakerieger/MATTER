#include "SolidShader.hpp"

SolidShader::SolidShader(const char* shaderPath) {
    std::string shaderCode;
    std::ifstream shaderFile;

    shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try {
        shaderFile.open(shaderPath);
        std::stringstream shaderStream;

        shaderStream << shaderFile.rdbuf();

        shaderFile.close();

        shaderCode = shaderStream.str();
    } catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    std::string vertexCode;
    std::string fragmentCode;

    size_t vertStart = shaderCode.find("@VERTEX");
    size_t vertEnd = shaderCode.find("@ENDVERTEX");
    size_t fragStart = shaderCode.find("@FRAGMENT");
    size_t fragEnd = shaderCode.find("@ENDFRAGMENT");

    vertexCode = "#version 460 core\n" + shaderCode.substr(vertStart + 8, vertEnd - vertStart - 8);
    fragmentCode = "#version 460 core\n" + shaderCode.substr(fragStart + 9, fragEnd - fragStart - 9);

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, ECompileType::VERTEX);

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, ECompileType::FRAGMENT);

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, ECompileType::PROGRAM);

    glDeleteShader(vertex);
    glDeleteShader(fragment);   
}

SolidShader::~SolidShader() {
    glDeleteProgram(ID);
}

void SolidShader::Use() {
    glUseProgram(ID);
}

void SolidShader::Destroy() {
    glDeleteProgram(ID);
}

void SolidShader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}

void SolidShader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void SolidShader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void SolidShader::setVec2(const std::string &name, const glm::vec2 &value) const { 
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
}
void SolidShader::setVec2(const std::string &name, float x, float y) const { 
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); 
}

void SolidShader::setVec3(const std::string &name, const glm::vec3 &value) const { 
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
}
void SolidShader::setVec3(const std::string &name, float x, float y, float z) const { 
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); 
}

void SolidShader::setVec4(const std::string &name, const glm::vec4 &value) const { 
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
}
void SolidShader::setVec4(const std::string &name, float x, float y, float z, float w) const { 
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w); 
}

void SolidShader::setMat2(const std::string &name, const glm::mat2 &mat) const {
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void SolidShader::setMat3(const std::string &name, const glm::mat3 &mat) const {
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void SolidShader::setMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void SolidShader::checkCompileErrors(unsigned int shader, ECompileType type) {
    std::string typeStr[4] = { "VERTEX", "FRAGMENT", "GEOMETRY", "PROGRAM" };

    int success;
    char infoLog[1024];
    if (type != ECompileType::PROGRAM) {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << typeStr[type] << "\n" << std::string(infoLog) << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << typeStr[type] << "\n" << std::string(infoLog) << std::endl;
        }
    }
}