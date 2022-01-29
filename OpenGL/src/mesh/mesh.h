#ifndef _MESH_
#define _MESH_

#include <GL/glew.h>

class Mesh
{
public:
    Mesh();
    ~Mesh();

    void CreateMesh(
        GLfloat *param_vertices,
        unsigned int *param_indices,
        unsigned int param_num_of_vertices,
        unsigned int param_num_of_indices);

    void RenderMesh();

    void ClearMesh();

private:
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_IBO;

    GLsizei m_index_count;
};


#endif //_MESH_