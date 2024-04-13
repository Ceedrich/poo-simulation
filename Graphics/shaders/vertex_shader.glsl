#version 330 core

attribute vec3 aPos;
attribute vec3 color;
attribute vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 objectColor;
out vec3 Normal;
out vec3 FragPos;

void main() {
    //Normal = mat3(transpose(inverse(model))) * aNormal;
    Normal = aNormal;
    FragPos = vec3(model * vec4(aPos, 1.0));
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    objectColor = color;
}
