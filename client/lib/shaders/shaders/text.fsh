#version 130

uniform sampler2D text;
uniform vec3 texcolor;

in vec2 TexCoords;
out vec4 color;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    color = sampled;
    //color = vec4(texcolor, 1);
    //color = vec4(texcolor, 1.0) *sampled;
} 
