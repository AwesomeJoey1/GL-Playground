#version 430

in vec3 Position;
in vec3 Normal;

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

layout(location=0) out vec4 FragColor;

vec3 phong(in vec3 position, in vec3 normal)
{
	vec3 n = normalize(normal);
	vec3 s = normalize(vec3(Light.Position) - position);
	vec3 v = normalize(-position);
	vec3 h = normalize(v + s);

	vec3 ambient = Material.Ka * Light.La;
	vec3 diffuse = Material.Kd * Light.Ld * max(dot(s, normal), 0.0);
	vec3 specular = Material.Ks * Light.Ls * pow(max(dot(h,n), 0.0), Material.Shininess);
	
	return ambient + diffuse + specular;
}

void main() {
	FragColor = vec4(phong(Position, Normal), 1.0);
}