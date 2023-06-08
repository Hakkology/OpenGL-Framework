#ifndef UTILITY_H
#define UTILITY_H

#include <GL/glew.h>

#include <glm/glm.hpp>

class Utility{

public:

    void CalculateAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount, 
                                unsigned int vLength, unsigned int normalOffset);

private:

#endif

};