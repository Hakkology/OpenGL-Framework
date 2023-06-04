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

OpenGL transformations should be used by the right order.
If we move something and then rotate it, it will be rotating based on the or the point of the origin point as opposed to its own origin.

Transform functions are:
model = glm::translate(model, glm::vec3(triOffset, triOffset/2, 0.0f));
model = glm::rotate(model, currentAngle * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::scale(model, glm::vec3(currentSize, currentSize, 1.0f));
*/

//////////////////////////// 

// Interpolation, Indexed Draws and Projections

/*
Vertex attributes are interpolated using other values on the primitive.
Weighted average of the three vertices on a triangle is passed on.
Fragment shader uses interpolated values.

Indexed Draws:
1- Define vertices to draw a cube.
2- Cube will consist of 12 triangles, two for each face.
3- 12 x 3 vertices per triangle = 36 vertices.
4- But a cube has 8 vertices.
5- Some vertices will be used multiple times.

Projections
1- User to convert from "View Space" to "Clip Space".
2- Can be used to give the scene a '3D' look through depth.
3- Alternatively can be used to create 2D style for projects.
4- Works on coordinate systems.

Local space: raw position of each vertex relative to origin.
World space: position of vertex in the world itself if came is assumed to be position at the origin.
View space: position of vertex in the world relative to camera position and orientation.
Clip space: position of vertex in the world relative to the came position and orientation, as viewed in the are not to be "clipped" from the final output.
Screen space: after clipping takes place, final image is created and placed.

- Orthographic Projection used in 2D Applications
- Perspective Projection used in 3D Applications

glm::mat4 proj = glm::perspective(fov, aspect, near, far)
fov => field of view,
aspect => aspect ratio of the viewport
near => distance of the near plane
far => distance of the far plane
Bind the given matrix to a uniform in the shade as:
gl_position = projection * view * model * vec (pos, 1.0)
*/