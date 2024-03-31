#version 460 core
layout(location = 0) in vec3 position;

uniform mat4 u_view_projection;
uniform mat4 u_model;

void main() {
    gl_Position = u_view_projection * u_model * vec4(position, 1.0);
}