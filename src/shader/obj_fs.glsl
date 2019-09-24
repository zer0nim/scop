#version 410 core
out vec4			fragColor;

struct Material {
	sampler2D		diffuse;
	sampler2D		specular;
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

struct SpotLight {
    vec3			position;
    vec3			direction;
	float			cutOff;
	float			outerCutOff;

    float			constant;
    float			linear;
    float			quadratic;

    vec3			ambient;
    vec3			diffuse;
    vec3			specular;
};

#define MAX_POINT_LIGHTS 8

in vec3				fragPos;
in vec3				normal;
in vec2				texCoords;
in vec3				color;

uniform vec3        viewPos;
uniform Material    material;
uniform DirLight	dirLight;
uniform int			nbPointLight;
uniform PointLight	pointLights[MAX_POINT_LIGHTS];
uniform SpotLight	spotLight;
uniform float		mix_val;

vec3 calcDirLight(DirLight light, vec3 norm, vec3 viewDir) {
	vec3	lightDir = normalize(-light.direction);
	// diffuse
	float	diff = max(dot(norm, lightDir), 0.0);
	// specular
	vec3	reflectDir = reflect(-lightDir, norm);
	float	spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	vec3	ambient = light.ambient * vec3(texture(material.diffuse, texCoords));
	vec3	diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoords));
	vec3	specular = light.specular * spec * vec3(texture(material.specular, texCoords));
	return (ambient + diffuse + specular);
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

vec3 calcSpotLight(SpotLight light, vec3 norm, vec3 fragPos, vec3 viewDir) {
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

	float 	theta = dot(lightDir, normalize(-light.direction));
	float 	epsilon = light.cutOff - light.outerCutOff;
	float 	intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
	ambient *= attenuation * intensity;
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;
	return (ambient + diffuse + specular);
}

void main() {
	vec3	norm = normalize(normal);
	vec3	viewDir = normalize(viewPos - fragPos);

	// phase 1: Directional lighting
	vec3 result = calcDirLight(dirLight, norm, viewDir);
	// phase 2: Point lights
	for (int i = 0; i < MAX_POINT_LIGHTS && i < nbPointLight; i++)
		result += calcPointLight(pointLights[i], norm, fragPos, viewDir);
	// phase 3: Spot light
	result += calcSpotLight(spotLight, norm, fragPos, viewDir);

	fragColor = mix(vec4(color / 255, 1.0), vec4(result, 1.0), mix_val);
}
