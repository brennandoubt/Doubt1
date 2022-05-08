#version 330 core
// output variable: vector of size 4 defining final color output that we should calculate ourselves
out vec4 FragColor;

void main() {
	// vec4 assigned to output as an orange-ish color with alpha value of 1.0 (completely opaque)
	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}