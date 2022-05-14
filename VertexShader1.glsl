//#version 330 core
//layout (location = 0) in vec3 aPos;
//
//void main() {
//	// a vector in GLSL has a max size of 4 with each value
//	// being vec.x, vec.y, vec.z, and vec.w respectively where each one represents a coordinate in space
//	// *vec.w (set to 1.0 here) isn't used as a position in space but rather for perspective division (discussed later)
//	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
//}
