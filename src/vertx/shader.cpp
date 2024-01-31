#include "vertx/shader.hpp"

#include <glad/glad.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

unsigned int ID;

// Get the path of the vertex shader file and the fragment shader file
Shader::Shader(const char *vrtxPath, const char *frgmntPath) {
  std::string vrtxCode;
  std::string frgmntCode;
  std::ifstream vrtxShaderFile;
  std::ifstream frgmntShaderFile;
  // Make sure ifstream objects can throw exceptions
  vrtxShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  frgmntShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  // Try to run this. Otherwise catch the error and print it.
  try {
    // Open files
    vrtxShaderFile.open(vrtxPath);
    frgmntShaderFile.open(frgmntPath);
    std::stringstream vrtxShaderStream, frgmntShaderStream;
    // Read file's buffer contents into streams
    vrtxShaderStream << vrtxShaderFile.rdbuf();
    frgmntShaderStream << frgmntShaderFile.rdbuf();
    // Close file handlers
    vrtxShaderFile.close();
    frgmntShaderFile.close();
    // Convert stream into string
    vrtxCode = vrtxShaderStream.str();
    frgmntCode = frgmntShaderStream.str();
  } catch (std::ifstream::failure const &) {
    std::cerr << "Error! Shader file not successfully read!" << std::endl;
  }
  // Convert string into char array.
  // c_str() returns a pointer to an array that contains a null-terminated
  // sequence of characters (i.e., a C-string) representing the current value of
  // the string object.
  const char *vrtxShaderCode = vrtxCode.c_str();
  const char *frgmntShaderCode = frgmntCode.c_str();

  // Compile shaders
  unsigned int vrtx, frgmnt;
  int success;
  char infoLog[512];
  // Vertex Shader
  vrtx = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vrtx, 1, &vrtxShaderCode, NULL);
  glCompileShader(vrtx);
  glGetShaderiv(vrtx, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vrtx, 512, NULL, infoLog);
    std::cerr << "Error! Vertex shader compilation failed!\n"
              << infoLog << "\n"
              << "[VRTX] filename: " << vrtxPath << "\n"
              << std::endl;
  }
  // Fragment Shader
  frgmnt = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frgmnt, 1, &frgmntShaderCode, NULL);
  glCompileShader(frgmnt);
  glGetShaderiv(frgmnt, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(frgmnt, 512, NULL, infoLog);
    std::cerr << "Error! Fragment shader compilation failed!\n"
              << infoLog << "\n"
              << "[FRAG] filename: " << frgmntPath << "\n"
              << std::endl;
  }
  // Shader Program
  // Right! I forgot that IDs are crucial for OpenGL. I'll have to remember that
  ID = glCreateProgram();
  glAttachShader(ID, vrtx);
  glAttachShader(ID, frgmnt);
  glLinkProgram(ID);
  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(ID, 512, NULL, infoLog);
    std::cerr << "Error! Shader program linking failed!\n"
              << infoLog << "\n"
              << "[FRAG] filename: " << frgmntPath << "\n"
              << "[VRTX] filename: " << vrtxPath << "\n"
              << std::endl;
  }
  // Time to yeet the shaders
  glDeleteShader(vrtx);
  glDeleteShader(frgmnt);
}

void Shader::use() {
  glUseProgram(ID);
} // "Use of undeclared identifier 'ID' -- The compiler is smoking crack again.

void Shader::setBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const {
  glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const std::string &name, float x, float y) const {
  glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
  glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string &name, float x, float y, float z) const {
  glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void Shader::setVec4(const std::string &name, const glm::vec4 &value) const {
  glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string &name, float x, float y, float z,
                     float w) {
  glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const {
  glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
                     &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const {
  glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
                     &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
  glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
                     &mat[0][0]);
}
