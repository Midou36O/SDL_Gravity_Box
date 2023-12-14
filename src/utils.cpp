#include "utils.hpp"

#include <glad/glad.h>
#include <iostream>

void DebugGL::CheckOpenGLError(const char *stmt, const char *fname, int line) {
  GLenum err = glGetError();
  if (err != GL_NO_ERROR) {
    std::cerr << "OpenGL error" << err << " , at " << fname << " : " << line
              << " - for " << stmt << std::endl;
    abort();
  }
}

void DebugGL::GLClearError() {
  while (glGetError() != GL_NO_ERROR)
    ; // Do nothing
}
