//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//#include <iostream>
//using namespace std;
//
//
////// callback function to set viewport/render window size based on actual window size
////void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
////	glViewport(0, 0, width, height);
////};
////
////// input control function: returns whether key is currently being pressed
////// glfwGetKey() returns GLFW_RELEASE if escape key is not pressed
////// if user did press escape key, then we close GLFW by setting its
////// WindowShouldClose property to true with "glfwSetWindowShouldClose"
////void processInput(GLFWwindow* window) {
////	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
////		glfwSetWindowShouldClose(window, true);
////	}
////}
//
//
//int main_i() {
//	glfwInit(); // initializing GLFW
//
//	// create window
//	GLFWwindow* window = glfwCreateWindow(800, 600, "Practice", NULL, NULL);
//	if (window == NULL) {
//		cout << "Failed to create GLFW window" << endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//
//	// initialize GLAD
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//		cout << "Failed to initialize GLAD" << endl;
//		return -1;
//	}
//
//	// set rendering window size for OpenGL
//	glViewport(0, 0, 800, 600);
//	// callback function to set rendering window/viewport size based on the actual window
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//
//
//
//
//
//	/*
//	* 5.3: Take source code for vertex shader and store it in a const C string at top of code file for now.
//	*/
//	const char* vertexShaderSource = "#version 330 core\n"
//		"layout (location = 0) in vec3 aPos;\n"
//		"void main() {\n"
//		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//		"}\0";
//
//	// three vertices stored for 2D triangle (so z-axis is 0 for each vertex)
//	float vertices[] = {
//	-0.5f, -0.5f, 0.0f,
//	0.5f, -0.5f, 0.0f,
//	0.0f, 0.5f, 0.0f
//	};
//
//	// generating a VBO
//	unsigned int VBO;
//	glGenBuffers(1, &VBO);
//	// binding the VBO to its buffer type called GL_ARRAY_BUFFER (also coded later down)
//	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
//	// copies vertex data into buffer's memory (also coded later down)
//	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	// vertex shader object with reference ID
//	unsigned int vertexShader;
//	vertexShader = glCreateShader(GL_VERTEX_SHADER);
//
//	// attach source code to shader object and compile shader
//	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//	glCompileShader(vertexShader);
//
//	// checking for shader compile-time errors
//	int success;
//	char infoLog[512]; // to store error messages (if any)
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); // checks if compilation successful or failed
//	// if failed, retrieve and print error message
//	if (!success) {
//		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
//	}
//
//
//
//
//
//	/*
//	* 5.4: Fragment Shader - for calculating color output of pixels
//	* 
//	* Colors in computer graphics are represented as an array of 4 values - RGBA (red, green, blue,
//	* and alpha (opacity) components) with the strength of each one set to a value between 0.0 and 1.0 in OpenGL/GLSL
//	* (ex. setting red to 1.0 and green to 1.0 gives the color yellow)
//	*/
//
//	const char* fragmentShaderSource = "#version 330 core\n"
//		"out vec4 FragColor;\n"
//		"void main() {\n"
//		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//		"}\0";
//
//	unsigned int fragmentShader;
//	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//	glCompileShader(fragmentShader);
//
//	int fsuccess;
//	char finfoLog[512];
//	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fsuccess);
//	if (!success) {
//		glGetShaderInfoLog(fragmentShader, 512, NULL, finfoLog);
//		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << finfoLog << endl;
//	}
//
//
//
//	// both the vertex and fragment shaders have compiled successfully at this point!
//
//	// Only thing left is to link the shader objects into a shader program that we can use for rendering.
//
//	// linking shaders into a program links the outputs of each shader to the inputs of the next shader
//	// will get linking errors if outputs and inputs don't match
//
//	// can then activate the shader program when rendering objects
//	// the activated shader program's shaders will be used when we issue render calls
//
//	// creating program
//	unsigned int shaderProgram;
//	shaderProgram = glCreateProgram(); // also returns ref ID to program object
//
//	// attaching shaders to program object
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//
//	// linking shaders
//	glLinkProgram(shaderProgram);
//
//	// check for program compile-time errors
//	int psuccess;
//	char pinfoLog[512];
//	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &psuccess);
//	if (!psuccess) {
//		glGetProgramInfoLog(shaderProgram, 512, NULL, pinfoLog);
//		cout << "ERROR::SHADER::LINK::COMPILATION_FAILED\n" << pinfoLog << endl;
//	}
//
//	// linked shaders into program compilation successful!
//
//	// every shader and rendering call after glUseProgram will now use this program object (and thus the shaders) (also coded later down)
//	//glUseProgram(shaderProgram);
//	
//	// shader objects no longer needed since they're linked into the program object, so can delete them
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//
//	// right now, we sent the input vertex data to the GPU and instructed the GPU how it should process the vertex data within a vertex and fragment shader
//	
//	// OpenGL still needs to know how to interpret the vertex data in memory, and
//	// how it should connect the vertex data to the vertex shader's attributes.
//
//	/*
//	* 5.5: Linking Vertex Attributes
//	* 
//	* (vertex buffer data figure on page 34)
//	* 
//	* Vertex shader allows us to specify input in the form of vertex attributes, so
//	* we have to manually specify what part of our input data goes to which vertex attribute in the vertex shader.
//	* 
//	* Each vertex attribute takes its data from memory managed by a VBO.
//	* - the exact VBO is determined by the VBO currently bound to GL_ARRAY_BUFFER when calling glVertexAttribPointer
//	* (the previously defined VBO is still bound before calling glVertexAttribPointer, vertex attribute 0 is now associated with its vertex data)
//	*/
//
//	/*
//	* glVertexAttribPointer: function to tell OpenGL how it should interpret the vertex data(per vertex attribute)
//	*	arg 1 - specifies which vertex attribute we want to configure by its location(which we set for the position vertex attribute with layout(location = 0))
//	*	arg 2 - size of the vertex attribute(a 'vec3' composed of 3 values)
//	*	arg 3 - data type(which is GL_FLOAT - a vec * in GLSL consists of floating point values)
//	*	arg 4 - specifies if we want the data to be normalized(ex.inputting integer data types could be normalized to 0 (or -1 for signed data) and 1 when converted to float); this isn't relevant for us, so we'll leave it at GL_FALSE instead of GL_TRUE
//	*	arg 5 - the stride; tells us space between consecutive vertex attributes(since the next set of position data is exactly 3 times the size of a float away we specify that value as the stride); you could also set this to 0 to let OpenGL determine the stride when the values are tightly packed
//	*	arg 6 - offset of where position data begins in the buffer(since position data is at the start of the data array this value is just 0); has void* type, so here it needs the cast to void*
//	* 
//	* This function specifies how OpenGL should interpret the vertex data.
//	*/	
//	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//
//	// enabling vertex attribute (arg = vertex attribute location); vertex attributes are disabled by default
//	//glEnableVertexAttribArray(0);
//
//	// Now we have everything set up! Initialized vertex data in a buffer using a VBO, set up a vertex and fragment shader and told OpenGL how to link the vertex data to the vertex shader's attributes!
//
//	
//
//	// Drawing an object in OpenGL now looks like this... (this process must be repeated every time we want to draw an object)
//
//	//// 0. copy vertices array in a buffer for OpenGL to use
//	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	//
//	//// 1. then set the vertex attribute pointers
//	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	//glEnableVertexAttribArray(0);
//	//
//	//// 2. use our shader program when we want to render an object
//	//glUseProgram(shaderProgram);
//
//	// 3. now draw the object with some other function
//
//	
//	/*
//	* Vertex Array Object (VAO) - store state configurations into a VAO so that when configuring vertex attribute pointers, you only have to make those calls once
//	* 
//	* - when drawing the object, we can also just bind the corresponding VAO
//	* 
//	* - can be bound just like a vertex buffer object and any subsequent vertex attribute calls will then be stored inside the VAO
//	* 
//	* This makes switching between different vertex data and attribute configurations as easy as binding a different VAO.
//	* All the state we just set is stored inside the VAO.
//	* 
//	* Core OpenGL requires us to bind a VAO so it knows what to do with our vertex inputs.
//	* If we fail to bind a VAO, OpenGL will most likely refuse to draw anything.
//	* 
//	* A VAO stores:
//	* 
//	* - calls to glEnableVertexAttribArray or glDisableVertexAttribArray
//	* 
//	* - vertex attribute configurations via glVertexAttribPointer
//	* 
//	* - vertex buffer objects (VBOs) associated with vertex attributes by calls to glVertexAttribPointer
//	*/
//	
//	// generating VAO (similar to generating a VBO)
//	unsigned int VAO;
//	glGenVertexArrays(1, &VAO);
//
//	// to use a VAO, all you have to do is bind the VAO using glBindVertexArray
//	// then we should bind/configure the corresponding VBO(s) and attribute pointer(s) and then unbind the VAO for later use.
//	// When we want to draw an object, we bind the VAO with the preferred settings before drawing the object and that's it.
//
//
//	// Now drawing an object in code would look like this... (same code with later additions implemented below)
//
//	//// *Inititalization code (done once unless your object frequently changes)*
//	//// 1. binding VAO to use it
//	//glBindVertexArray(VAO);
//	//
//	//// 2. copy vertices array in a buffer for OpenGL to use
//	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	//
//	//// 3. then set the vertex attribute pointers
//	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	//glEnableVertexAttribArray(0);
//
//	//// [...]
//	//// 4. Draw the object (coded in render loop below)
//
//
//	/*
//	* 5.6: Element Buffer Objects (EBO)
//	*
//	* You can draw a rectangle using two triangles (OpenGL mainly works with triangles) as shown in
//	* the 'vertices2' array. However, this causes some overlap on the vertices (such as specifying 'bottom right' and 'top left' twice)
//	* - this is an overhead of 50% since the same rectangle could only be specified with 4 vertices instead of 6
//	* 
//	* A better solution is to store only the unique vertices and then specify the order to
//	* draw them in.
//	* - in this case we'd only have to store 4 vertices for the rectangle
//	* 
//	* This is how EBOs work - a buffer that stores indices that OpenGL uses to decide what vertices to draw.
//	* - this solution is also called indexed drawing
//	* 
//	* To do indexed drawing:
//	* 
//	* - specify unique vertices and the indices to draw them as a rectangle
//	*/
//
//	// Vertices for drawing 2D rectangle (using two triangles) - non indexed drawing (has overlapping vertices)
//	float vertices2[] = {
//		// first triangle
//		0.5f, 0.5f, 0.0f, // top right
//		0.5f, -0.5f, 0.0f, // bottom right
//		-0.5f, 0.5f, 0.0f, // top left
//		// second triangle
//		0.5f, -0.5f, 0.0f, // bottom right
//		-0.5f, -0.5f, 0.0f, // bottom left
//		-0.5f, 0.5f, 0.0f // top left
//	};
//
//	// Vertices for drawing 2D rectangle - indexed drawing (unique vertices from drawing two triangles to represent rectangle)
//	float vertices2u[] = {
//		0.5f, 0.5f, 0.0f, // top right
//		0.5f, -0.5f, 0.0f, // bottom right
//		-0.5f, -0.5f, 0.0f, // bottom left
//		-0.5f, 0.5f, 0.0f // top left
//	};
//	// order/indices to draw each vertex in, in order to draw them as a rectangle
//	unsigned int indices[] = {
//		0, 1, 3, // first triangle
//		1, 2, 3 // second triangle
//	};
//
//	// Now creating/generating the element buffer object
//	unsigned int EBO;
//	glGenBuffers(1, &EBO);
//
//	// Bind EBO and copy the indices into the buffer with glBufferData (buffer target = GL_ELEMENT_ARRAY_BUFFER) (also coded below)
//	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	// Last step is drawing rectangle (coded in the render loop below)
//	/*
//	* glDrawElements: function that takes its indices from the EBO currently bound to buffer target
//	* - this means we would have to bind the corresponding EBO each time we want to render an object with indices
//	* - but a vertex array object (VAO) also keeps track of EBO bindings, so the last EBO bound while a VAO is bound, is stored as the
//	* VAO's EBO; a VAO stores the glBindBuffer calls when the buffer target is GL_ELEMENT_ARRAY_BUFFER (also stores its unbind calls)
//	* 
//	* * binding to a VAO automatically binds the currently-bound EBO *
//	* 
//	* ** don't unbind the element array buffer before unbinding your VAO, otherwise it doesn't have an EBO configured **
//	*
//	*
//	* arg 1 - mode to draw in
//	* arg 2 - number of elements to draw (6 indices specified = drawing 6 vertices in total)
//	* arg 3 - data type of the indices
//	* arg 4 - can specify an offset in the EBO or an index array when not using EBOs, but we're just leaving it at 0 here
//	*/
//
//	// Now the initialization and drawing code looks like this...
//
//	// 1. bind VAO
//	glBindVertexArray(VAO);
//	// 2. copy vertices array in a vertex buffer for OpenGL to use
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2u), vertices2u, GL_STATIC_DRAW);
//
//	// 3. copy index array in an element buffer for OpenGL to use
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	// 4. then set the vertex attributes pointers
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	// [...]
//
//	// 5. drawing code (in render loop)
//
//
//
//	// render loop
//	while (!glfwWindowShouldClose(window)) {
//
//		// can clear screen's color buffer here at start of frame to avoid seeing results from previous frame
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // specifying color to clear to the screen (State-setting function)
//		glClear(GL_COLOR_BUFFER_BIT); // filling color buffer with specified color to clear it; pass in buffer bits to specify which buffer to clear (State-using function)
//
//		// *Drawing code (in render loop)*
//		// 4. draw the object
//		glUseProgram(shaderProgram);
//		glBindVertexArray(VAO); // same 'bind' function unbinds the VAO after drawing object
//		/*
//		* To draw an object, OpenGL has the glDrawArrays function that draws primitives using the currently active shader,
//		* the previously defined vertex attribute configuration, and with the VBO's vertex data (indirectly bound via the VAO).
//		*/
//		//glDrawArrays(GL_TRIANGLES, 0, 3);
//
//		// drawing rectangle in wireframe mode (drawing triangles' lines only to show the rectangles' two triangles it consists of)
//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//		// For drawing rectangle: replace the glDrawArrays call with glDrawElements to indicate we're rendering the triangles from an index buffer using the indices provided in the currently-bound EBO		
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//		// to set the rendering of triangles back to its default mode (filling triangles back in)
//		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//
//		// calling process input every render loop iteration
//		// this gives an easy way to check for specific key presses and react
//		// accordingly every frame/render loop iteration (more commonly called a frame)
//		processInput(window);
//
//		// check and call events and swap the buffers
//		glfwPollEvents();
//		glfwSwapBuffers(window);
//	}
//
//
//
//	glfwTerminate(); // terminating GLFW
//	return 0;
//}