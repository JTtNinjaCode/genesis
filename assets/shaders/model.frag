#version 460 core
in vec2 a_uv;

struct Material {
    sampler2D diffuse1;
    sampler2D specular1;
};

uniform Material material;

out vec4 fragment_color;

void main() {
    vec3 texture_color = texture(material.diffuse1, a_uv).rgb;
    fragment_color = vec4(texture_color, 1.0);
}