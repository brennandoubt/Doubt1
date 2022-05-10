#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
};

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
};

int main() {
	cout << "Terminal doubt<><><><>" << endl;
	
	// init GLFW
	glfwInit();

	// create window
	GLFWwindow* window = glfwCreateWindow(800, 600, "Section 5, Exercise 2", NULL, NULL);
	if (window == NULL) {
		cout << "Error creating GLFW window." << endl;
		return 1;
	}
	glfwMakeContextCurrent(window);

	// init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initialize GLAD." << endl;
		return 1;
	}

	// set rendering window size
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// source code for shaders
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main() {\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main() {\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";
	
	// setting up vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int vsuccess;
	char vinfoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vsuccess);
	if (!vsuccess) {
		glGetShaderInfoLog(vertexShader, 512, NULL, vinfoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << vinfoLog << endl;
	}

	// setting up fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	int fsuccess;
	char finfoLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fsuccess);
	if (!fsuccess) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, finfoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << finfoLog << endl;
	}

	// setting up program to attach and link shaders with
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	int psuccess;
	char pinfoLog[512];
	glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &psuccess);
	if (!psuccess) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, pinfoLog);
		cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << endl;
	}

	// deleting shader objects after linking to program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Goal: Draw two triangles side-by-side using two different VBOs and VAOs for their data.
	
	// triangle 1
	float vertices1[] = {
		-0.7f, -0.8f, 0.0f,
		-0.1f, -0.8f, 0.0f,
		-0.4f, 0.0f, 0.0f
	};
	// triangle 2
	float vertices2[] = {
		0.7f, -0.8f, 0.0f,
		0.1f, -0.8f, 0.0f,
		0.4f, 0.0f, 0.0f
	};

	// A vertex array object(VAO) also keeps track of EBO bindings, so the last EBO bound while a VAO is bound, is stored as the
	// VAO's EBO; a VAO stores the glBindBuffer calls when the buffer target is GL_ELEMENT_ARRAY_BUFFER (also stores its unbind calls)


	// first vao
	unsigned int VAO1;
	glGenVertexArrays(1, &VAO1);

	// first vbo
	unsigned int VBO1;
	glGenBuffers(1, &VBO1);

	// bind vao 1
	glBindVertexArray(VAO1);

	// bind vbo 1 to array buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	// copy triangle 1 vertices array into vbo 1
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

	// configure vbo 1 (set vertex attribute pointers)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// unbind vao 1
	glBindVertexArray(VAO1);


	// second vao
	unsigned int VAO2;
	glGenVertexArrays(1, &VAO2);

	// second vbo
	unsigned int VBO2;
	glGenBuffers(1, &VBO2);

	// bind vao 2
	glBindVertexArray(VAO2);

	// bind vbo 2 to array buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);

	// copy triangle 2 vertices array into vbo 2
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	// configure vbo 2 vertex attributes (tells OpenGL how to read each vertex attribute (each vertex attribute = 3 float-type graph positions x, y, and z))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// unbind vao 2
	glBindVertexArray(VAO2);


	// render loop
	while (!glfwWindowShouldClose(window)) {
		glUseProgram(shaderProgram);

		// bind vao 1 to draw triangle 1
		glBindVertexArray(VAO1);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// then bind vao 2 to draw triangle 2
		glBindVertexArray(VAO2);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		processInput(window);
		glfwPollEvents();
		glfwSwapBuffers(window); // (changes window from white to black)
	}




	glfwTerminate();
	return 0;
};