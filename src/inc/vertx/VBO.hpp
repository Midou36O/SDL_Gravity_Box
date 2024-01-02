#pragma once

#include "glad/glad.h"
#include "utils.hpp"

class VBO {
public: // I keep forgetting classes are private by default.
  VBO(GLfloat *vertices, GLsizeiptr size);
  void Bind();
  void Unbind();
  void Delete();

  GLuint getID();

private:
  GLuint ID;
  DebugGL debugGL;
};
