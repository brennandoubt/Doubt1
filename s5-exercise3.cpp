/*
* Brennan Allen
* LearnOpenGL Section 5.8, Exercise 3
* 
* Create two shader programs where the second program uses a different
* fragment shader that outputs the color yellow; use that to output one of the triangles
* with the color yellow.
*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
};

int main() {
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

	/* Adding another frag shader here for color yellow (red + green) */
	const char* fragmentShaderSource2 = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main() {\n"
		"	FragColor = vec4(0.8f, 0.8f, 0.1f, 1.0f);\n"
		"}\0";

	// init GLFW
	glfwInit();

	// create window
	GLFWwindow* window = glfwCreateWindow(800, 600, "Section 5.8, Exercise 3", NULL, NULL);
	if (window == NULL) {
		cout << "Failed to create GLFW window." << endl;
		return 1;
	}
	glfwMakeContextCurrent(window);

	// init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initialize GLAD." << endl;
		return 1;
	}

	// set rendering window size (necessary?)
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// setting up shaders
	GLuint vertexShader;
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
	GLuint fragmentShader;
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

	// attach and link shaders to new program
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	int psuccess;
	char pinfoLog[512];
	glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &psuccess);
	if (!psuccess) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, pinfoLog);
		cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << pinfoLog << endl;
	}

	/* Making first orange triangle */
	GLfloat vertices[] = {
		-0.8f, -0.9f, 0.0f,
		-0.2f, -0.9f, 0.0f,
		-0.5f, -0.1f, 0.0f
	};

	// generate and bind vao
	GLuint VAO1;
	glGenVertexArrays(1, &VAO1);
	
	glBindVertexArray(VAO1);

	// generate, bind, and store triangle vertex data in vbo
	GLuint VBO1;
	glGenBuffers(1, &VBO1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO1);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// give interpretation for vbo's vertex attributes (their graph coordinates) from glVertexAttribPointer() function
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// unbind vao
	glBindVertexArray(VAO1);



	/* Making second yellow triangle */

	// in render loop, use two different shader programs for each triangle

	// set up yellow frag shader
	GLuint fragmentShader2;
	fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
	glCompileShader(fragmentShader2);
	int f2success;
	char f2infoLog[512];
	glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &f2success);
	if (!f2success) {
		glGetShaderInfoLog(fragmentShader2, 512, NULL, f2infoLog);
		cout << "ERROR::SHADER::FRAGMENT_2::COMPILATION_FAILED\n" << f2infoLog << endl;
	}

	// then make second shader program for rendering yellow triangle
	GLuint shaderProgram2;
	shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);
	glLinkProgram(shaderProgram2);
	int p2success;
	char p2infoLog[512];
	glGetProgramiv(shaderProgram2, GL_COMPILE_STATUS, &p2success);
	if (!p2success) {
		glGetProgramInfoLog(shaderProgram2, 512, NULL, p2infoLog);
		cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << p2infoLog << endl;
	}

	// now generate new vao and vbo for second triangle

	GLfloat vertices2[] = {
		0.8f, -0.9f, 0.0f,
		0.2f, -0.9f, 0.0f,
		0.5f, -0.1f, 0.0f
	};

	GLuint VAO2;
	glGenVertexArrays(1, &VAO2);
	glBindVertexArray(VAO2);

	GLuint VBO2;
	glGenBuffers(1, &VBO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAO2);



	// render loop (I love wireframe mode)
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!glfwWindowShouldClose(window)) {

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO1);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgram2);
		glBindVertexArray(VAO2);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		processInput(window);
		glfwPollEvents();
		glfwSwapBuffers(window);
	}




	return 0;
};