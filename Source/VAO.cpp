#include <VAO.h>

VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}


void VAO::LinkAttrib
(
    VBO VBO,
    GLuint layout,
    GLuint numComponents,
    GLenum type,
    GLsizeiptr stride,
    void* offset
)
{
    VBO.Bind();
    // Configure the Vertex Attribute so that OpenGL know how to read the VBO
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    // Enable the vertex Attribute so that OpenGL know to use it
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}

void VAO::Bind()
{
    // Bind both the BAO and EBO to 0 so that we dont't accidentally modify the VAO
    glBindVertexArray(ID);
}

void VAO::Unbind()
{
    // Bind both the BAO and EBO to 0 so that we dont't accidentally modify the VAO
    glBindVertexArray(0);
}

void VAO::Delete()
{
    // Delete the objects we've created
    glDeleteBuffers(1, &ID);
}
