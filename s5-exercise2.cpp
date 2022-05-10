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





	glfwTerminate();
	return 0;
};