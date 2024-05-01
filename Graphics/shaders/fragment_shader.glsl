#version 330 core
in vec3 objectColor;
in vec3 Normal;
in vec3 FragPos;

struct Light {
    float ambient_intensity;
    vec3 position;
    vec3 specular;
    vec3 color;
};

uniform Light light;

void main() {
    // Ambient lighting
    vec3 ambient = light.ambient_intensity * light.color;
    // Diffuse lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light.color;

    vec3 resultColor = (ambient + diffuse) * objectColor;

    gl_FragColor = vec4(resultColor, 1.0);
}
