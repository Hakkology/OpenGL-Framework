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

//////////////////////////// 

/*
Camera/View Space

Camera processes the scene as seen in "View Space".
View space is the coordinate system with each vertex as seen from the camera.
Use a View matrix to convert from World Space to View Space
Required 4 values:
- Camera Position
- Direction
- Right
- Up

Camera position: position of the camera.
direction: the direction camera is looking in.
direction vector points in opposite direction of the intuitive direction.

Right means multiply camera by cross product of [0, 1, 0]
Up means multiply camera by cross product of Direction and right vectors.

glm::mat4 viewMatrix;
glm::lookAt(position, target, up)

to use view Matrix: 
1- bind it to a uniform on the shader.
2- Apply it between the projection and model matrices.
3- Order in shader matters, usually projection - view - model.

Input: Moving the Camera

GLFW: glfw GetKey(window, GLFW_KEY_W)
Add the value to camera position while key held.
To fix computer speeds and track it by fps:

Input: Delta Time
Check how much time passed since last loop, apply maths based on this to keep consistent speeds.

deltaTime = currentTime - lastTime;
lastTime = currentTime;

Input: Turning

Angles for turning:
- Pitch: looking up and down (axis relative to the yaw)
- Yaw: looking left and right (around x-axis)
- Roll: like a plane doing a barrel roll

Input: Turning- Pitch
y = sin(pitch);
x = cos(pitch);
z = cos(pitch);

Input: Turning- Yaw
x = cos(yaw);
z = sin(yaw);

GLFW: glfwSetCursorPosCallback (window, callback);
Store old mouse position, compare to new position, Use diff to decide pitch/yaw change.

*/

//////////////////////////// 

/*
Textures

Textures are images used to add extra detail to an object. Textures can also be used to hold generic data.
Usually 2D but can also have 1D and 3D textures.
Points on textures are texels, not pixels. Texels are defined between 0 and 1, bound to vertices with interpolated values.

To sample a point at the top-middle you reference texel (0.5,1).
Map texels to vertices. Interpolation over each fragment will calculate appropriate texels in between the assigned texels.

glGenTextures (1, &texture);
glBindTexture(GL_TEXTURE_2D, texture);
- Different type of textures for 1D and 3D

glTexImage2D (GL_TEXTURE2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data)

- Texture target.
- Mipmap level, resolution limitations for textures, handling level of detail.
Create multiple version of image at different resolutions and switch when needed.
- Format of stored data. RGB is red green blue. Also RGBA which has alpha channel, transparency.
- Width and height of the texture with 4 and 5.
- Texture borders, always 0.
- Format of the loaded data (not stored).
- The data type of the values.
- The data itself.

Texture parameters:
Render off center of texels ?
- Nearest - use the texel with most overlap
- Linear - Use a weighted average of surrounding texels

glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

Texture filtering changes how texels are blended
Nearest to give more pixelated look, linear to give more blended look;
Outside (0,1) range;
- Repeat the texture,
- Repeat a mirrored form of the texture,
- Extend pixels at the edge,
- Apply a coloured border.
glTexParameter helps with this.

Texture wrapping changes how textures are handled for texel values outside 0,1.
GL_TEXTURE_WRAP_S > Wrapping on x-axis
GL_TEXTURE_WRAP_T > Wrapping on y-axis

GL_REPEAT: Repeat texture.
GL_MIRRORED_REPEAT: Repeat and mirror texture.
GL_CLAMP_TO_EDGE: Extend pixels at edge.
GL_CLAMP_TO_BORDER: Apply coloured border.

Image loader libraries:
SOIL Library (Simple OpenGL Image Library)
stb_image
#define STB_IMAGE_IMPLEMENTATION
unsigned char* data=
stbi_load("image.jpg", &width, &height, &bitDepth, 0);
Might need to flip image.
stbi_set_flip_vertically_on_load(true);

- Texture in Shaders are accessed via "Samplers" with IDs.
- Textures are attached to a "Texture Unit".
- Samplers access textures attached to their Texture Unit.
- In shader, use "sampler2D" type.
- To get the value of a texel, use GLSL "texture" function.
- texture(textureSampler, TexCoord);
- textureSampler: the sampler2D Object.
- TexCoord: interpolated texel coordinate in fragment shader.

Bind texture to desired Texture Unit:
- glActiveTexture (GL_TEXTURE0);
- glBindTexture (GL_TEXTURE_2D, textureID);
Ensure sampler2D variables know which Texture Unit to access:
- glUniform1i(uniformTextureSampler, 0);
Value attached to Uniform is the Texture Unit Number.

Textures can be retrieved from Texturer.com

*/
