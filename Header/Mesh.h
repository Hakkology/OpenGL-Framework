#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>

class Mesh{

public:
    Mesh();
    ~Mesh();

    void Create3DMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
    void Create2DMeshTriangle(GLfloat *vertices, unsigned int numOfVertices);
    void Render3DMesh();
    void Render2DMeshTriangle();
    void ClearMesh();

private:
    GLuint VAO, VBO, IBO;
    GLsizei indexCount;

};

#endif