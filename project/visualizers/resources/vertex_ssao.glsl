#version 420 core
layout (location = 0) in vec3 vertex_pos;
layout (location = 1) in vec2 texture_pos;

out vec2 TexCoords;

void main()
{
    TexCoords = texture_pos;
    gl_Position = vec4(vertex_pos, 1.0);
}