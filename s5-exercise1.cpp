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

	// generating vertex buffer (object) to hold vertex data
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	// bind vertex buffer to array buffer target
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// add vertex data for first triangle to buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// unbind buffer from array buffer target
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// set and enable vertex attributes as inputs to OpenGL so it can interpret the vertices' data as intended
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	/* Render Loop */
	while (!glfwWindowShouldClose(window)) {
		

		glDrawArrays(GL_TRIANGLES, 0, 3);

		processInput(window);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
};

