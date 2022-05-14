/*
* 6: Shaders are programs written in the OpenGL Shading Language (GLSL).
* 
* GLSL is a C-like language tailored for use with graphics and
* vector and matrix multiplication.
* 
* Shader code structure:
* 
* - version declaration
* 
* - list of input and output variables
* 
* - uniforms
* 
* - main function (shader's entry point to process any input variables and output the
* results in output variables)
*/

/*
* #version version_number
* in type in_variaable_name;
* in type in_variable_name;
*
* out type out_variable_name;
*
* uniform type uniform_name;
*
* void main() {
* 
* // process input and do graphics stuff
* ...
* 
* // output processed stuff to output variable
* out_variable_name = stuff_processed;
* }
*/

/*

For vertex shaders, each input variable is also known as a vertex attribute.

OpenGL guarantees at least 16 4-component vertex attributes available, but some hardware
may allow for more.

GLSL has most of the default basic types we know of from C: int, float, double, uint, and bool

GLSL also has two container types: vectors and matrices (matrices discussed later)

vector - component container for any of the basic data types above (default = "vecn" for a vector of 'n' floats)

Sending data from one shader to the other can be done by declaring an output in the sending
shader and a similar input in the receiving shader. OpenGL will link variables together when their
types and names are equal.


Uniforms - another way to pass data from our application on the CPU to the shaders on the GPU; global (unique per shader program object, and can be accessed from any shader at any
stage in the shader program); uniforms will keep they're values until they're reset or updated

declaring a uniform example: uniform vec4 ourColor;

(declaring a uniform that's not used anywhere in your GLSL code will result in the compiler
silently removing the variable from the compiled version which can cause many frustrating errors; keep in mind)


*/

