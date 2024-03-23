#version 460 core
in vec2 a_uv;
uniform sampler2D tex;
out vec4 fragment_color;

void main() {
    vec4 color = texture(tex, a_uv);
    fragment_color = color;
}