#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

void CreateTriangle(GLuint&, GLuint&);
void AddShader(GLuint, const char*, GLenum);
void CompileShaders(GLuint&);

#endif
