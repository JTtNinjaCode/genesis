#version 460 core
in vec2 a_uv;

uniform sampler2D u_texture;
uniform vec4 u_flat_color;

out vec4 fragment_color;

void main() {
    vec4 texture_color = texture(u_texture, a_uv);
    fragment_color = texture_color * u_flat_color;
}