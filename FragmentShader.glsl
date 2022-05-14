#version 410 core
out vec4 FragColor;

in vec4 vertexColor; // input variable from vertex shader (same name and type)

void main() {
	
	FragColor = vertexColor;

}