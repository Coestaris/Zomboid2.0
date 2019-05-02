#version 130
#extension GL_ARB_explicit_attrib_location : enable

layout (location = 0) in vec4 vertex;

out vec2 TexCoords;

uniform mat4 projection;

void main()
{
    gl_Position = vec4(vertex.xy, 0.0, 1.0);
    TexCoords = vertex.zw;
} 