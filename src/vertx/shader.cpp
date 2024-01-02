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
              << infoLog << std::endl;
  }
  // Fragment Shader
  frgmnt = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frgmnt, 1, &frgmntShaderCode, NULL);
  glCompileShader(frgmnt);
  glGetShaderiv(frgmnt, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(frgmnt, 512, NULL, infoLog);
    std::cerr << "Error! Fragment shader compilation failed!\n"
              << infoLog << std::endl;
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
              << infoLog << std::endl;
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
