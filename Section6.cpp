//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//#include <iostream>
//using namespace std;
//
//int main() {
//
//	const char* vertexShader2Source = "#version 330 core\n"
//		"layout (location = 0) in vec3 aPos;\n"
//		"out vec4 vertexColor;\n"
//		"void main() {\n"
//		"	gl_Position = vec4(aPos, 1.0); //we give a vec3 to vec4's constructor\n"
//		"	vertexColor = vec4(0.5, 0.0, 0.0, 1.0); //output variable to dark red\n"
//		"}\0";
//
//	const char* fragmentShader2Source = "#version 330 core\n"
//		"out vec4 FragColor;\n"
//		"in vec4 vertexColor; // input variable from vertex shader (same name aand type)\n"
//		"void main() {\n"
//		"	FragColor = vertexColor;\n"
//		"}\0";
//
//	return 0;
//};