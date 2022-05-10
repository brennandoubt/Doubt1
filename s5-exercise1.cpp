#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;

// set render window size based on actual window size
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
};

// 'Esc' key closes window
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
};


int main() {
	glfwInit();

	// create window
	GLFWwindow* window = glfwCreateWindow(800, 600, "Exercise 1, Chapter 5", NULL, NULL);
	if (window == NULL) {
		cout << "Failed to create GLFW window." << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initialize GLAD." << endl;
	}

	// setting render window
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// vertex shader source code as a const string
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main() {\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	// fragment shader source code as a const string
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main() {\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";

	// creating vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// vertex shader error handling
	int vsuccess;
	char vinfolog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vsuccess);
	if (!vsuccess) {
		glGetShaderInfoLog(vertexShader, 512, NULL, vinfolog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << vinfolog << endl;
	}

	// creating fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// fragment shader error handling
	int fsuccess;
	char finfolog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fsuccess);
	if (!fsuccess) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, finfolog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << finfolog << endl;
	}


	// now link shaders into a shader program

	// creating program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram(); // also returns ID to reference program object

	// attaching shaders to program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// linking shaders attached to program
	glLinkProgram(shaderProgram);

	// shader program error handling
	int psuccess;
	char pinfolog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &psuccess);
	if (!psuccess) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, pinfolog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << pinfolog << endl;
	}
	
	// can now delete shaders after attaching them to shader program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float vertices[] = {
		// first triangle
		-0.7f, -0.8f, 0.0f,
		-0.1f, -0.8f, 0.0f,
		-0.4f, 0.0f, 0.0f,

		// second triangle
		0.7f, -0.8f, 0.0f,
		0.1f, -0.8f, 0.0f,
		0.4f, 0.0f, 0.0f
	};

	// first (left) triangles' vertices
	float vertices1[] = {
		-0.7f, -0.8f, 0.0f, // bottom left ((-1.0f, -1.0f, 0.0f) normalized would be the very bottom left corner coordinate of render window)
		-0.1f, -0.8f, 0.0f, // bottom right
		-0.4f, 0.0f, 0.0f // top vertex
	};
	// essentially mirroring previous triangles' vertices
	float vertices2[] = {
		1.1f, -1.0f, 0.0f,
		0.1f, -1.0f, 0.0f,
		0.6f, 0.0f, 0.0f
	};

	// To use a VAO, all you have to do is bind the VAO using glBindVertexArray.
	// Then we should bind/configure the corresponding VBO(s) and attribute pointer(s) and then unbind the VAO for later use.
	// When we want to draw an object, we bind the VAO with the preferred settings before drawing the object and that's it.
	

	// generate vertex array object to store state configurations (vertex attribute configurations?)
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	// bind VAO to use it
	glBindVertexArray(VAO); // no triangle is drawn without this code; only the background for the window is drawn

	// generating vertex buffer (object) to hold vertex data
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	// bind vertex buffer to array buffer target
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// add vertex data for first triangle to buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/*
	* @glVertexAttribPointer: function to tell OpenGL how it should interpret the vertex data(per vertex attribute)
	*	arg 1 - specifies which vertex attribute we want to configure by its location(which we set for the position vertex attribute with layout(location = 0))
	*	arg 2 - size of the vertex attribute(a 'vec3' composed of 3 values)
	*	arg 3 - data type(which is GL_FLOAT - a vec * in GLSL consists of floating point values)
	*	arg 4 - specifies if we want the data to be normalized(ex.inputting integer data types could be normalized to 0 (or -1 for signed data) and 1 when converted to float); this isn't relevant for us, so we'll leave it at GL_FALSE instead of GL_TRUE
	*	arg 5 - the stride; tells us space between consecutive vertex attributes(since the next set of position data is exactly 3 times the size of a float away we specify that value as the stride); you could also set this to 0 to let OpenGL determine the stride when the values are tightly packed
	*	arg 6 - offset of where position data begins in the buffer(since position data is at the start of the data array this value is just 0); has void* type, so here it needs the cast to void*
	*/

	// set and enable vertex attributes as inputs to OpenGL so it can interpret the vertices' data as intended (only a blank window is outputted without this code)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	

	//// binding the second triangle's vertices to a vertex buffer, and binding it to the array buffer target
	//unsigned int VBO2;
	//glGenBuffers(1, &VBO2);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);


	// unbinding VAO here for later use; when drawing an object, we can now just bind the VAO with the preferred settings before drawing
	glBindVertexArray(VAO);

	/* Render Loop */
	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // clear window with this color generated (state-setting function)
		glClear(GL_COLOR_BUFFER_BIT); // fill color buffer with specified color to clear it (state-using function)

		// using shader program when rendering an object (since it refers to our vertex and fragment shaders attached to it as well)
		glUseProgram(shaderProgram); // (a white triangle is drawn without this code)

		// binding the VAO we made with our preferred settings here before triangle is drawn
		glBindVertexArray(VAO); // binding or unbinding the VAO doesn't seem to affect the window output here, why?
		
		// draws the primitives using currently active shader, vertex attributes, and vertex buffer's data (indirectly bound via vertex array object)
		// change size parameter to 6 to draw 6 vertices in vertices array (3 per triangle)
		glDrawArrays(GL_TRIANGLES, 0, 6);

		processInput(window);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
};

