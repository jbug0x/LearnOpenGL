#include <VAO.h>

VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}


void VAO::LinkVBO(VBO VBO, GLuint layout)
{
    VBO.Bind();
    // Configure the Vertex Attribute so that OpenGL know how to read the VBO
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
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
