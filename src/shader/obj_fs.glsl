#version 410 core
out vec4			fragColor;

struct Material {
	sampler2D		diffuse;
	sampler2D		specular;
	sampler2D		emission;
	float			shininess;
};

struct DirLight {
    vec3			direction;

    vec3			ambient;
    vec3			diffuse;
    vec3			specular;
};

struct PointLight {
    vec3			position;

    float			constant;
    float			linear;
    float			quadratic;

    vec3			ambient;
    vec3			diffuse;
    vec3			specular;
};
#define NR_POINT_LIGHTS 4

in vec3				fragPos;
in vec3				normal;
in vec2				texCoords;

uniform vec3        viewPos;
uniform Material    material;
uniform DirLight	dirLight;
uniform PointLight	pointLights[NR_POINT_LIGHTS];

vec3 calcDirLight(DirLight light, vec3 norm, vec3 viewDir) {
	vec3	lightDir = normalize(-light.direction);
	// diffuse
	float	diff = max(dot(norm, lightDir), 0.0);
	// specular
	vec3	reflectDir = reflect(-lightDir, norm);
	float	spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	// emission
	vec3	emission = vec3(texture(material.emission, texCoords));

	vec3	ambient = light.ambient * vec3(texture(material.diffuse, texCoords));
	vec3	diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoords));
	vec3	specular = light.specular * spec * vec3(texture(material.specular, texCoords));
	return (ambient + diffuse + specular + emission);
}

vec3 calcPointLight(PointLight light, vec3 norm, vec3 fragPos, vec3 viewDir) {
	vec3    lightDir = normalize(light.position - fragPos);
	// diffuse
	float	diff = max(dot(norm, lightDir), 0.0);
	// specular
	vec3	reflectDir = reflect(-lightDir, norm);
	float	spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	// attenuation
	float	distance = length(light.position - fragPos);
	float	attenuation = 1.0 / (light.constant + light.linear * distance + \
	light.quadratic * (distance * distance));

	vec3	ambient = light.ambient * vec3(texture(material.diffuse, texCoords));
	vec3	diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoords));
	vec3	specular = light.specular * spec * vec3(texture(material.specular, texCoords));
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	return (ambient + diffuse + specular);
}

void main() {
	vec3	norm = normalize(normal);
	vec3	viewDir = normalize(viewPos - fragPos);

	// phase 1: Directional lighting
	vec3 result = calcDirLight(dirLight, norm, viewDir);
	// vec3 result = vec3(0.0f);
	// phase 2: Point lights
	for (int i = 0; i < NR_POINT_LIGHTS; i++)
		result += calcPointLight(pointLights[i], norm, fragPos, viewDir);
	// phase 3: Spot light
	//result += calcSpotLight(spotLight, norm, fragPos, viewDir);

	fragColor = vec4(result, 1.0);
}
