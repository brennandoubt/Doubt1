/*
* Brennan Allen
* Chapter 5
* 
* Working with EBOs and practice using index buffers.
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

	/*
	* For Section 6: Shaders
	* 
	* vertexColor object in fragment shader and vertex shader are linked since
	* they both have the same name and type
	* 
	* Color set to dark red color in the vertex shader, so the resulting fragments should be dark red
	* as well.
	*/
	const char* vertexShader2Source = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"out vec4 vertexColor;\n"
		"void main() {\n"
		"	gl_Position = vec4(aPos, 1.0); //we give a vec3 to vec4's constructor\n"
		"	vertexColor = vec4(0.5, 0.0, 0.0, 1.0); //output variable to dark red\n"
		"}\0";
	const char* fragmentShader2Source = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec4 vertexColor; // input variable from vertex shader (same name aand type)\n"
		"void main() {\n"
		"	FragColor = vertexColor;\n"
		"}\0";
	// Adding uniform type to fragment shader
	const char* fs3source = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"uniform vec4 ourColor; // we set this variable in the OpenGL code.\n"
		"void main() {\n"
		"FragColor = ourColor;\n"
		"}\0";

	// init GLFW
	glfwInit();

	int userw;
	int userh;
	//stringstream userSS;

	cout << "Please type window width: ";
	cin >> userw;
	cout << "Please type window height: ";
	cin >> userh;

	cout << "Width given: " << userw << "\nHeight given: " << userh << endl;


	// create window
	GLFWwindow* window = glfwCreateWindow(userw, userh, "Section 5.8, Exercise 3", NULL, NULL);
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
	glViewport(0, 0, userw, userh);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// setting up shaders
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShader2Source, NULL);
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
	glShaderSource(fragmentShader, 1, &fs3source, NULL);
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

	// triangles' vertices
	GLfloat vertices[] = {
		// makes equilateral triangle
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // upper corner

		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // inner down
	};
	
	// index order for draeing triangles correctly (drawing a triad?)
	GLuint indices[] = {
		0, 3, 5, // lower left triangle
		3, 2, 4, // lower right triangle
		5, 4, 1 // upper triangle
	};

	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO); // also using EBO here

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// now bind element buffer and copy indices array into it
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window)) {
		
		// updating uniform color
		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glUseProgram(shaderProgram);

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		processInput(window);

		// swap buffers and poll IO events
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwTerminate();

	return 0;
};