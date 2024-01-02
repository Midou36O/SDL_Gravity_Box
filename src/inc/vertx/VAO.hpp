
#pragma once

#include "glad/glad.h"
#include "vertx/VBO.hpp"

class VAO {
public:
  VAO();
  void LinkVBO(VBO VBO, GLuint layout);
  void Bind();
  void Unbind();
  void Delete();

  GLuint getID();

private:
  GLuint ID;
};
