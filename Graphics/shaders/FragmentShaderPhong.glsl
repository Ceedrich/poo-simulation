#version 330 core
in vec3 objectColor;
in vec3 Normal;
in vec3 FragPos;

struct Light {
    float ambient_intensity;
    float specular_intensity;
    float diffuse_intensity;
    float shininess;
    vec3 position;
    vec3 color;
};

uniform Light light;
uniform vec3 viewPos;

void main() {
    // Ambient lighting
    vec3 ambient = light.ambient_intensity * light.color;
    // Diffuse lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse_intensity * diff * light.color;
    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), max(light.shininess, 1));
    vec3 specular = light.specular_intensity * spec * light.color;

    //vec3 resultColor = (ambient) * objectColor;
    //vec3 resultColor = (diffuse) * objectColor;
    //vec3 resultColor = (specular) * objectColor;
    vec3 resultColor = (ambient + diffuse + specular) * objectColor;

    gl_FragColor = vec4(resultColor, 1.0);
}
