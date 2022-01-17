#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 norm;

out vec4 v_col;
out vec2 v_tex_coord;
out vec3 v_normal;
out vec3 v_frag_pos;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;


void main()
{
    gl_Position = projection * view * model * vec4(pos, 1.0);
    v_col = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);

    v_tex_coord = tex;

    v_normal = mat3(transpose(inverse(model))) * norm;

    v_frag_pos = (model * vec4(pos, 1.0)).xyz;
}   