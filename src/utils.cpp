#include "utils.hpp"

#include <glad/glad.h>
#include <iostream>

void DebugGL::CheckOpenGLError(const char *stmt, const char *fname, int line) {
  GLenum err = glGetError();
  // Describe the error.
  // Replace codes with the proper error messages.

  if (err != GL_NO_ERROR) {
    std::cerr << "OpenGL error " << err << ", at " << fname << ":"
              << line - 1 // because the line is off by 1
              << " - for " << stmt << std::endl;
    DebugGL::GLClearError();
  }
}

void DebugGL::GLClearError() {
  while (glGetError() != GL_NO_ERROR)
    ; // Do nothing
}
