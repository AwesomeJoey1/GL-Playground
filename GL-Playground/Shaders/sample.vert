#version 430

layout(location=0) in vec3 VertexPosition;
layout(location=1) in vec3 VertexNormal;

uniform mat4 ModelViewMatrix;
uniform mat4 MVP;
uniform mat3 NormalMatrix;

out vec3 Position;
out vec3 Normal;
out vec3 LightIntensity;

void main() {

	Normal = normalize(NormalMatrix * VertexNormal);
	Position = vec3(ModelViewMatrix * vec4(VertexPosition, 1.0));
	
	gl_Position = MVP * vec4(VertexPosition, 1.0);
}