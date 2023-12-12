#pragma once

#include <string>

class Shader {
public: // Public values, exposable and usable by functions outside of the class
  // Get the path of the vertex shader file and the fragment shader file
  Shader(const char *vrtxPath, const char *frgmntPath);
  // Activate the shader
  void use();
  // Utility uniform functions
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
};

// #ifndef SHADER_HPP can also be used to prevent the header from being included
// twice.
// https://stackoverflow.com/questions/1143936/how-to-prevent-headers-from-being-included-twice
// It's a standard, and supported by all compilers. But pragma isn't. Eh, who
// cares?
