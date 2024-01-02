#include "vertx/EBO.hpp"

/*
 * EBO Constructor
 * \desc Generates a EBO and binds it to the GL_ELEMENT_ARRAY_BUFFER
 * \param GLfloat *indices - pointer to vertices array
 * \param GLsizeiptr size - size of indices array
 */
EBO::EBO(GLuint *indices, GLsizeiptr size) {
  glGenBuffers(1, &this->ID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

/*
 * EBO Bind
 * \desc Binds the EBO to the GL_ELEMENT_ARRAY_BUFFER
 */
void EBO::Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID); }

/*
 * EBO Unbind
 * \desc Unbinds the EBO from the GL_ELEMENT_ARRAY_BUFFER
 */
void EBO::Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

/*
 * EBO Delete
 * \desc Deletes the EBO
 */
void EBO::Delete() { glDeleteBuffers(1, &this->ID); }

/*
 * EBO getID
 * \desc Returns the ID of the EBO
 */
GLuint EBO::getID() { return this->ID; }
