#version 460 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;

uniform mat4 u_view_projection;
uniform mat4 u_model;

out vec2 a_uv;
void main() {
    gl_Position = u_view_projection * u_model * vec4(position, 1.0);
    a_uv = uv;
}