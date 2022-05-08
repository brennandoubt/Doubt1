//#include <glad/glad.h>
//#include <GLFW/glfw3.h>

//#include <iostream>
//using namespace std;
/*
* 5: showing  3D items to screen involves transforming
* 3D coords to 2D pixels that fit to your screen
* 
* This transformation process is managed by the graphics pipeline of OpenGL.
* graphics pipeline involves:
* 1) transforming 3D coords into 2D coords
* 2) transforming 2D coords into actual colored pixels
* 
* Graphics cards today have thousands of small processing cores to quickly process
* data within the graphics pipeline.
* These cores run small programs on the GPU for each step of the
* pipeline. These small programs are called shaders.
* 
* Many shaders are written in the OpenGL Shading Language (GLSL), 
* and some of them are configurable by the developer so we can write our own shaders.
* 
* Pipeline parts:
* 
* vertex shader - takes a single vertex; 3D coords -> different 3D coords (more on this later)
* 
* primitive assembly - takes all vertices from vertex shader that form a primitive (ex. triangle)
* and assembles all points into the primitive shape given
* 
* geometry shader - takes primitive assembly's output and can generate other shapes by emitting
* new vertices to form new (or other) primitives (such as turning the original bigger triangle primitive
* into two triangles with a new vertex splitting the larger triangle)
* 
* rasterization stage - takes geometry shader's output; maps
* the resulting primitive(s) to the corresponding pixels on the final screen, resulting in
* fragments for the fragment shader to use.
* 
* clipping - occurs before the fragment shaders run; discards all fragments
* that are outside of your view, increasing performance
* 
* (fragment - all data required for OpenGL to render a single pixel)
* 
* fragment shader - contains data about the 3D scene
* (lights, shadows, color of the light, etc.); uses this data to 
* calculate the final color of a pixel
* 
* After all these corresponding values are determined, the final
* object passes through one more stage called the alpha test and blending stage.
* 
* alpha test and blending - checks depth (and stencil) value of the fragment to check
* if the resulting fragment is in front or behind other objects and should be discarded accordingly;
* also checks for alpha values (these define the opacity of an object) and blends the objects
* accordingly
* 
* In modern OpenGL we are required to define at least a vertex and fragment shader ourselves. The others
* have default shaders on the GPU.
*/

/*
* 5.1: Vertex input
* 
* Normalized Device Coordinates (NDC) - range of -1.0 and 1.0 on 
* all three axes (x, y, and z) for coords; all coords within this range
* will end up visible on your screen
* 
* Vertex Input:
* 
* triangle - three vertices, each with 3D positions
* 
* 
* Differences from usual screen coords:
* 
* - positive y-axis points in the up-direction and (0, 0) coord
* refers to center of the graph
* 
* 
*/

//// Vertex shader stored as a const char C string; OpenGL must dynamically compile the shader at runtime from the source code
//const char* vertexShaderSource = "#version 330 core\n"
//	"layout (location = 0) in vec3 aPos;\n"
//	"void main() {\n"
//	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//	"}\0";
//
//int main_5() {
//
//	// Vertex input for triangle defined in NDC
//	// z-coord is 0.0  for each vertex since this is a 2D triangle but OpenGL works in 3D space
//	// this ensures the depth of the triangle remains the same to make it look 2D
//	float vertices[] = {
//		-0.5f, -0.5f, 0.0f,
//		0.5f, -0.5f, 0.0f,
//		0.0f, 0.5f, 0.0f
//	};
//
//	/*
//	* Now we send this vertex data as input to the vertex shader
//	* by creating memory on the GPU to store the vertex data, configure
//	* how OpenGL interprets the memory, and specify how to send the data to the
//	* graphics card.
//	* 
//	* This memory is managed using "vertex buffer objects" (VBO) that
//	* can store a large number of vertices in the GPU's memory.
//	* 
//	* Advantage of these buffers: can send large batches of data all at once
//	* to the graphics card (preferred since sending data from CPU
//	* to graphics card is relatively slow) instead of one vertex at a time
//	* 
//	* VBOs are OpenGL objects with unique IDs corresponding to that buffer.
//	*/
//
//	// generating a VBO
//	unsigned int VBO;
//	glGenBuffers(1, &VBO);
//	// binding the VBO to its buffer type called GL_ARRAY_BUFFER
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
//	// now any buffer calls to this target are used to configure the currently bound buffer VBO
//
//	// copies vertex data into buffer's memory
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	/*
//	* glBufferData - function used to copy user-defined data into buffer
//	* 
//	* arg 1 = buffer type to copy data into
//	* arg 2 = size of data in bytes to pass to buffer
//	* arg 3 = actual data we want to send
//	* arg 4 = specifies how we want the graphics card to manage given data
//	* - three forms for arg 4:
//	*		- GL_STREAM_DRAW: data is set only once and used by GPU at most a few times
//	*		- GL_STATIC_DRAW: data is set only once and used many times
//	*		- GL_DYNAMIC_DRAW: data is changed a lot and used many times
//	* 
//	* For triangle, the position data of the triangle does not change, is used a lot, and
//	* stays the same for every render call so its best usage type should be GL_STATIC_DRAW
//	*/
//
//	/*
//	* 5.2: Vertex shader
//	*/
//
//	// create shader object with reference ID
//	unsigned int vertexShader;
//	vertexShader = glCreateShader(GL_VERTEX_SHADER);
//
//	// attach source code to the shader object and compile shader
//	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//	glCompileShader(vertexShader);
//
//
//
//
//	return 0;
//}
