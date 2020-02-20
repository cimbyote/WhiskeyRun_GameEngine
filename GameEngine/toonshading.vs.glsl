#version 410 core

uniform mat4 world_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

layout (location = 0) in vec4 vVert;
layout (location = 1) in vec2 vTexCoord0;
layout (location = 2) in vec3 vNormal;


out VS_OUT
{
    vec3 normal;
    vec3 view;
} vs_out;

void main(void)
{
	mat4 mv_matrix = view_matrix * world_matrix;

    vec4 pos_vs = mv_matrix * vVert;

    // Calculate eye-space normal and position
    vs_out.normal = mat3(mv_matrix) * vNormal;
    vs_out.view = pos_vs.xyz;

    // Send clip-space position to primitive assembly
    gl_Position = proj_matrix * pos_vs;
}
