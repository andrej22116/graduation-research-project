#version 420 core
layout (location = 0) in vec3 vertex_pos;
layout (location = 1) in vec3 texture_pos;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

uniform mat4 resultTransformMatrix;
/*
layout (std140) uniform UniformLayout {
    mat4 resultTransformMatrix;
};
*/
/*
out VS_OUT {
    vec3 FragmentPosition,
    vec3 TexturePosition,
    vec3 Tangent,
    vec3 Tangent,
    vec3 Tangent
} vs_out;
*/

out vec3 fPos;
out vec3 fTex;
out vec3 fNormal;
out vec3 fTan;
out vec3 fBitan;

void main() {
    fPos = vertex_pos;
    fNormal = normal;
    fTan = tangent;
    fBitan = bitangent;
    fTex = texture_pos;
    gl_Position = resultTransformMatrix * vec4(vertex_pos, 1);
}
