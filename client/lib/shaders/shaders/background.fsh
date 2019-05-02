#version 130

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;

void main()
{
    vec4 color1 = texture(texture1, TexCoord);
    FragColor = color1.rgba;
}