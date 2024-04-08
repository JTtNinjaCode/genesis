#version 460 core
uniform vec4 u_flat_color;
out vec4 fragment_color;

void main() {
    fragment_color = u_flat_color;
}