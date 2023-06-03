// GLEW
// Open GL Extension Wrangler
// GL3W, glLoadGen, glad, glsdk, glbinding, libepoxy, Glee - some of the libraries

// #include <GL/glew.h>

// glewExperimental = GL_TRUE;
// glewinit();
// Should return GLEW_OK, otherwise error.
// glewGetErrorString(result);

// #include <GL/glfw.h>

// openGL Framework - window creation and control - input

// #include <GL/SDL.h> 

// Simple DirectMedia Layer
// GLFW + Audio, Threading, Filesystems, etc.
// Most popular
// SFML (Simple and Fast Multimedia Library) - Like SDL but even more features
// Win32 API is the origin
// Important for fundamental theory and building up GLFW / GLEW

////////////////////////////

// Rendering Pipelines
// SEries of stages that take place in order to render an image to the screen.
// Shaders are vertex shader, fragment shader, geometry shader, tesselation shader and compute shader.
/*
1- Vertex Specification
2- Vertex Shader
3- Tesselation
4- Geometry Shader
5- Vertex Post-Processing
6- Primitive Assembly
7- Rasterization
8- Fragment Shader
9- Per- Sample Operations
*/

/* 
1- Vertex Specification
A vertex is a point in space, usually defined with x, y and z co-ordinates. 
Vertex Specification uses these two features:
- VAO Vertex Array Objects - position, colour, texture, normals etc.
- VBO defines data itself
- Attribute pointers define where and how shaders can access vertex data.

Procedure through Code:
1- Generate a VAO ID
2- Bind the VAO with that ID
3- Generate a VBO ID
4- Bind the VBO with that ID, attaching VBO to VAO
5- Attach the vertex data to that VBO
6- Define the Attribute Pointer formatting
7- Enable the Attribute Pointer
8- Unbind the VAO and VBO, ready for the next object to be bound

** This procedure was used in triangle formations.

1- Activate Shader Program you want to use
2- Bind the VAO of object you want to draw
3- Call glDrawArrays, which initiates the rest of the pipeline

Vertex Shader handles vertices individually.
Stores data in gl_Position.
Fragment Shaders handles data for each fragment.
Vertex Post-Processing
- Transform Feedback
- Clipping

       Geometry Shader     Rasterization
Vertices =======> Primitives ======> Fragments
*/

//////////////////////////// 

// Vectors, Matrices and Uniform Variables

/*
GLm is used at OpenGL math operations, most importantly vectors and matrices.
Uniform variables pass global data to shaders.
Need to obtain a uniform's location then bind data to it.

glm:mat4 model;
glm::mat4 model(1.0f)
Correction on mat 4 using GLM.
*/