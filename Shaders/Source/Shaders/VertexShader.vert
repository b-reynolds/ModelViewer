//vertex shader
#version 430 core

 uniform float angle;
 in vec3 VertexPosition;
 in vec3 VertexColor;

 out vec3 Color;

void main() {

	Color = VertexColor;
	//gl_Position = vec4(VertexPosition, 1.0);

	mat4 rotateZ = mat4(1.5);

	rotateZ[0][0] = cos(angle);
	rotateZ[1][1] = cos(angle);
	rotateZ[1][0] = -sin(angle);
	rotateZ[0][1] = cos(angle);
	rotateZ[2][2] = 1.0f;

	gl_Position = rotateZ * vec4(VertexPosition, 1.0);

};