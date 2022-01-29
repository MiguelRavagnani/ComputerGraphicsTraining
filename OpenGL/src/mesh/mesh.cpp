#include "mesh.h"

Mesh::Mesh() 
    : m_VAO (0), 
      m_VBO (0), 
      m_IBO (0), 
      m_index_count(0) {}

Mesh::~Mesh()
{
    this->ClearMesh();
}


void Mesh::CreateMesh(
    GLfloat *param_vertices,
    unsigned int *param_indices,
    unsigned int param_num_of_vertices,
    unsigned int param_num_of_indices)
{
    m_index_count = param_num_of_indices;

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(param_indices[0]) * param_num_of_indices,
        param_indices,
        GL_STATIC_DRAW);

    /* Binding the VBO in the previous VAO "scope"*/
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    
    glBufferData(
        GL_ARRAY_BUFFER, 
        sizeof(param_vertices[0]) * param_num_of_vertices, 
        param_vertices, 
        GL_STATIC_DRAW);

    glVertexAttribPointer(
        0, 
        3, 
        GL_FLOAT, 
        GL_FALSE, 
        sizeof(param_vertices[0]) * 8,
        0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1, 
        2, 
        GL_FLOAT, 
        GL_FALSE, 
        sizeof(param_vertices[0]) * 8,
        (void* )(sizeof(param_vertices[0]) * 3));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(
        2, 
        3, 
        GL_FLOAT, 
        GL_FALSE, 
        sizeof(param_vertices[0]) * 8,
        (void* )(sizeof(param_vertices[0]) * 5));
    glEnableVertexAttribArray(2);

    /* Uninding the VBO in the previous VAO "scope"*/
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Mesh::RenderMesh()
{
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

    glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::ClearMesh()
{
    if (m_IBO != 0)
    {
        glDeleteBuffers(1, &m_IBO);
        m_IBO = 0;
    }

    if (m_VBO != 0)
    {
        glDeleteBuffers(1, &m_VBO);
        m_VBO = 0;
    }

    if (m_VAO != 0)
    {
        glDeleteVertexArrays(1, &m_VAO);
        m_VAO = 0;
    }

    m_index_count = 0;
}