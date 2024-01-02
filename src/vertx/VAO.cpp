#include "vertx/VAO.hpp"

/*
 * VAO Constructor
 * \desc Generates a VAO and binds it
 */
VAO::VAO() { glGenVertexArrays(1, &this->ID); }

/*
 * VAO LinkVBO
 * Links a VBO to the VAO
 * \param VBO VBO - VBO to link
 * \param GLuint layout - layout of VBO
 */

void VAO::LinkVBO(VBO VBO, GLuint layout) {
  VBO.Bind();
  glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)0);
  glEnableVertexAttribArray(layout);
  VBO.Unbind();
}

/*
 * VAO Bind
 * Binds the VAO
 */
void VAO::Bind() { glBindVertexArray(this->ID); }

/*
 * VAO Unbind
 * \desc Unbinds the VAO
 */
void VAO::Unbind() { glBindVertexArray(0); }

/*
 * VAO Delete
 * \desc Deletes the VAO
 */
void VAO::Delete() { glDeleteVertexArrays(1, &this->ID); }

/*
 * VAO getID
 * \desc Returns the ID of the VAO
 */
GLuint VAO::getID() { return this->ID; }
