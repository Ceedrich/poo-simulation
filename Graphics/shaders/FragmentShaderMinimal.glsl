#version 330 core
in vec3 objectColor;

void main() {
    gl_FragColor = vec4(objectColor, 1.0);
}
