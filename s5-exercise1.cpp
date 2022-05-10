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
	if (fsuccess) {
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

	glUseProgram(shaderProgram);

	// *can now delete shader objects since they can now just be referenced from program?
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// first (left) triangles' vertices
	float vertices[] = {
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

	// generate vertex array object to store state configurations (vertex attribute configurations?)
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	// bind VAO to use it
	glBindVertexArray(VAO);

	// generating vertex buffer (object) to hold vertex data
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	// bind vertex buffer to array buffer target
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// add vertex data for first triangle to buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// set and enable vertex attributes as inputs to OpenGL so it can interpret the vertices' data as intended (only a blank window is outputted without this code)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// use shader program when we want to render an object
	glUseProgram(shaderProgram);

	/* Render Loop */
	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // clear window with this color generated (state-setting function)
		glClear(GL_COLOR_BUFFER_BIT); // fill color buffer with specified color to clear it (state-using function)

		// using shader program when rendering
		//glUseProgram(shaderProgram);
		// re-binding VAO here to use the preferred settings for triangles
		glBindVertexArray(VAO);
		// draws the primitives using currently active shader, vertex attributes, and vertex buffer's data (indirectly bound via vertex array object)
		glDrawArrays(GL_TRIANGLES, 0, 3);

		processInput(window);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
};

