#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;


// callback function to set viewport/render window size based on actual window size
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
};

// input control function: returns whether key is currently being pressed
// glfwGetKey() returns GLFW_RELEASE if escape key is not pressed
// if user did press escape key, then we close GLFW by setting its
// WindowShouldClose property to true with "glfwSetWindowShouldClose"
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}


int main() {
	glfwInit(); // initializing GLFW

	// create window
	GLFWwindow* window = glfwCreateWindow(800, 600, "Section 4.5 Practice", NULL, NULL);
	if (window == NULL) {
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	// set rendering window size for OpenGL
	glViewport(0, 0, 800, 600);
	// callback function to set rendering window/viewport size based on the actual window
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// render loop
	while (!glfwWindowShouldClose(window)) {

		// can clear screen's color buffer here at start of frame to avoid seeing results from previous frame
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // specifying color to clear to the screen (State-setting function)
		glClear(GL_COLOR_BUFFER_BIT); // filling color buffer with specified color to clear it; pass in buffer bits to specify which buffer to clear (State-using function)

		// calling process input every render loop iteration
		// this gives an easy way to check for specific key presses and react
		// accordingly every frame/render loop iteration (more commonly called a frame)
		processInput(window);

		// check and call events and swap the buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}




	glfwTerminate(); // terminating GLFW
	return 0;
}