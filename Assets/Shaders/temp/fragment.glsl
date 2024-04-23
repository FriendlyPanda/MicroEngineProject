#version 330 core
out vec4 FragColor;

uniform vec3 color;
uniform float transparency;

void main(){
    FragColor = vec4(color, transparency);
}