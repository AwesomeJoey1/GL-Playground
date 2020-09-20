#version 430

layout(location=0) in vec3 Position;
layout(location=1) in vec3 Normal;

uniform vec4 LightPosition;
uniform vec3 Ld;
uniform vec3 Kd;

uniform vec3 eye;
uniform mat4 ModelViewMatrix;
uniform mat4 MVP;
uniform mat3 NormalMatrix;

out vec3 LightIntensity;

void main() {
	vec3 tNormal = normalize(NormalMatrix * Normal);
	vec4 eyeCoords = ModelViewMatrix * vec4(Position, 1.0);
	
	vec3 s = normalize(vec3(LightPosition - eyeCoords));
	
	LightIntensity = Kd * Ld * max(dot(s, tNormal), 0.0);
	
	gl_Position = MVP * vec4(Position, 1.0);
}