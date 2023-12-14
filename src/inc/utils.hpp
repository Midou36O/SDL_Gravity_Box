#pragma once

class DebugGL {
public:
  void CheckOpenGLError(const char *stmt, const char *fname, int line);
  void GLClearError();
};
