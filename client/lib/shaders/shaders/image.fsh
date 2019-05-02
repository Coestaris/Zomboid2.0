#version 130

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform vec4 color;

void main()
{
    vec4 texColor = texture(texture1, TexCoord);
    FragColor = texColor;
}