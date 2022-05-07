//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//
//using namespace std;
//
//
//// behind the scenes OpenGL uses the data from glViewport to transform
//// the 2D coords it processed to coords on your screen
//// However, when a user resizes the window the viewport should be adjusted as well
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//	glViewport(0, 0, width, height);
//};
//
//
//int main_2() {
//
//	glfwInit(); // initializing GLFW
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // configuring GLFW
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	// creating window object to hold windowing data
//	// *required by most of GLFW's other functions
//	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
//	if (window == NULL) {
//		cout << "Failed to create GLFW window" << endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//
//
//	/*
//	* GLAD manages function pointers for OpenGL
//	* so want to initialize GLAD before we call any OpenGL function.
//	*/
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//		cout << "Failed to initialize GLAD" << endl;
//		return -1;
//	}
//
//	glViewport(0, 0, 800, 600); // telling OpenGL size of rendering window
//	// first two parameters set the lower left corner location of the window
//	// third and fourth parameter set the width and height of the rendering window in pixels,
//	// which we set equal to GLFW's window size
//
//	// we have to tell GLFW we want to call this function on every window resize by registering it
//	// when window is first displayed, framebuffer_size_callback gets called
//	// as well with the resulting window dimensions
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//	// there are many callback functions we can set to register our own functions, such as for
//	// processing joystick input changes, error messages, etc.
//	// *we register the callback functions after we've created the window and
//	// before the render loop is initiated
//
//	// 4.3: using while loops (called the render loop) for the app to keep drawing images/handling user
//	// input until the program has been explicitly told to stop
//	
//	// simple example of a render loop
//	while (!glfwWindowShouldClose(window)) {
//		glfwSwapBuffers(window); // swaps the large 2D color buffer used to render to during this render iteration and shows it as output to the screen
//		glfwPollEvents();// checks for triggered events (keyboard input, mouse movement, etc.)
//	}
//
//	// apps drawing an image could result in image flickering issues or containing artifacts
//	// to handle this, windowing apps apply a double buffer for rendering
//	// front buffer - contains final output image shown at the screen, while all
//	// rendering commands draw to the back buffer
//	// once the rendering commands are finished we swap the back buffer to the front buffer so the image can
//	// be displayed without still being rendered to, removing all aforementioned artifacts
//
//	// 4.4:  when exiting the render loop, we want to properly delete/clean all of GLFW's
//	// resources that were allocated
//	// we can do this using glfwTerminate function called at the end of the main function
//	glfwTerminate();
//	return 0;
//}
