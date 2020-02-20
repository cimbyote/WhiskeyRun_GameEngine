#version 410 core

// Uniforms
	uniform mat4 world_matrix;
	uniform mat4 view_matrix;
	uniform mat4 proj_matrix;
	uniform vec3 light_pos;
	//uniform vec4 vColor;

// Attributes
	layout (location = 0) in vec4 vVert;
	layout (location = 1) in vec2 vTexCoord0;
	layout (location = 2) in vec3 vNormal;

// Inputs from vertex shader
out VS_OUT
{
    vec3 N;
    vec3 L;
    vec3 V;
} vs_out;

// Position of light
//uniform vec3 light_pos = vec3(100.0, 100.0, 100.0);

void main(void)
{
	mat4 mvMatrix = view_matrix * world_matrix;

    // Calculate view-space coordinate
    vec4 P = mvMatrix * vVert;

    // Calculate normal in view-space
    vs_out.N = mat3(mvMatrix) * vNormal;

    // Calculate light vector
    //vs_out.L = light_pos - P.xyz;

	// Get vLightDir
		vec4 ecPosition;
		vec3 ecPosition3;
		ecPosition = mvMatrix * vVert;
		ecPosition3 = ecPosition.xyz /ecPosition.w;
		vs_out.L = normalize(light_pos - ecPosition3);

    // Calculate view vector
    vs_out.V = -P.xyz;

    // Calculate the clip-space position of each vertex
    gl_Position = proj_matrix * P;
}
