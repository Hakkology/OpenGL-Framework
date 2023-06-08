#include <iostream>
#include <string.h>

#include "../Header/Mesh.h"

Mesh::Mesh(){

    VAO = 0;
    VBO = 0;
    IBO = 0;
    indexCount = 0;

};

void Mesh::Create3DMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices){

    indexCount = numOfIndices;

    // Generate vertex Arrays
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate vertex Buffers And indices
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW); //static draw means points do not change, dynamic draw is also available.

    // Enable vertex attribute pointers
    // to Enable all data in extures,
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 5));
    glEnableVertexAttribArray(2);

    // Release Vertex Array Binds
    glBindVertexArray(0);

    // Release Vertex Buffer Binds
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Mesh::Create2DMeshTriangle(GLfloat *vertices, unsigned int numOfVertices){

    // Generate vertex Arrays
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate vertex Buffers
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //static draw means points do not change, dynamic draw is also available.

    // Enable vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    // Release Vertex Buffer Binds
    glBindBuffer(GL_ARRAY_BUFFER,0);

    // Release Vertex Array Binds
    glBindVertexArray(0);
}

void Mesh::Render3DMesh(){
    
    if (indexCount>0)
    {
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}

void Mesh::Render2DMeshTriangle(){

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void Mesh::ClearMesh(){

    if (IBO != 0)
    {
        glDeleteBuffers(1, &IBO);
        IBO = 0;
    }

    if (VBO !=0)
    {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }

    if (VAO !=0)
    {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }

    indexCount = 0;
}

Mesh::~Mesh(){

    ClearMesh();    
}

