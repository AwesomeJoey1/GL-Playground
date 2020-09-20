#version 430

layout(location=0) in vec3 Position;
layout(location=1) in vec3 Normal;

out vec3 LightIntensity;

struct LightInfo
{
	vec4 Position;	// eye coords light position;
	vec3 La;		// ambient light intensity
	vec3 Ld;		// diffuse light intensity
	vec3 Ls;		// specular light intensity
};

uniform LightInfo Light;

struct MaterialInfo
{
	vec3 Ka;		// ambient reflectivity
	vec3 Kd;		// diffuse reflectivity
	vec3 Ks;		// specular reflectivity
	float Shininess;// specular shininess factor
};

uniform MaterialInfo Material;

uniform mat4 ModelViewMatrix;
uniform mat4 MVP;
uniform mat3 NormalMatrix;

void main() {

	vec3 tNormal = normalize(NormalMatrix * Normal);
	vec4 eyeCoords = ModelViewMatrix * vec4(Position, 1.0);
	vec3 s = normalize(vec3(Light.Position - eyeCoords));
	vec3 r = reflect(-s, tNormal);
	vec3 v = normalize(-eyeCoords.xyz);

	vec3 ambient = Material.Ka * Light.La;
	float sDotN = max(dot(s, tNormal), 0.0);
	vec3 diffuse = Material.Kd * Light.Ld * sDotN;
	vec3 specular = vec3(0);
	if (sDotN > 0.0)
	{
		specular = Material.Ks * Light.Ls * pow(max(dot(r,v), 0.0), Material.Shininess);
	}
	LightIntensity = ambient + diffuse + specular;
	
	gl_Position = MVP * vec4(Position, 1.0);
}