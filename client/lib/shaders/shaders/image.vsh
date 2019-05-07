#version 130

out vec2 texture_coordinate;

void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    //texture_coordinate = vec2(gl_TexCoord.xy);
}