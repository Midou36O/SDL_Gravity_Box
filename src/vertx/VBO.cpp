#include "vertx/VBO.hpp"

/*
 * VBO Constructor
 * \desc Generates a VBO and binds it to the GL_ARRAY_BUFFER
 * \param GLfloat *vertices - pointer to vertices array
 * \param GLsizeiptr size - size of vertices array
 */
VBO::VBO(GLfloat *vertices, GLsizeiptr size) {
  glGenBuffers(1, &this->ID);
  glBindBuffer(GL_ARRAY_BUFFER, this->ID);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
  // Check for errors
  DebugGL debugGL;
  debugGL.CheckOpenGLError("ERROR: Could not create VAO and VBO", __FILE__,
                           __LINE__);
}

/*
 * VBO Bind
 * Binds the VBO to the GL_ARRAY_BUFFER
 */
void VBO::Bind() { glBindBuffer(GL_ARRAY_BUFFER, this->ID); }

/*
 * VBO Unbind
 * Unbinds the VBO from the GL_ARRAY_BUFFER
 */
void VBO::Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

/*
 * VBO Delete
 * Deletes the VBO
 */
void VBO::Delete() { glDeleteBuffers(1, &this->ID); }

/*
 * VBO getID
 * Returns the ID of the VBO
 */
GLuint VBO::getID() { return this->ID; }
