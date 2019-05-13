#version 130
#extension GL_ARB_explicit_attrib_location : enable

layout (location = 0) in vec4 vertex;// <vec2 pos, vec2 tex>

out vec2 TexCoords;

void main()
{
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * vec4(vertex.xy, 0.0, 1.0);
    TexCoords = vertex.zw;
}