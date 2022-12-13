#version 330

uniform mat4 model_view_proj_mat;
uniform int use_global_alpha;
uniform int has_custom_transform;
uniform mat4 custom_translation_mat;
uniform mat4 custom_rotation_mat;
uniform mat4 custom_scale_mat;
uniform float global_alpha;

layout(location = 0) in vec3 in_vertex;
layout(location = 1) in vec3 vertex_color;
layout(location = 2) in float alpha;

out vec3 fragment_color;
out vec4 coord_out;
out float alpha_out;

void main()
{
    if(has_custom_transform == int(1))
    {
        vec4 transformed_pos = custom_translation_mat * custom_rotation_mat * custom_scale_mat * vec4(in_vertex.x, in_vertex.y, in_vertex.z, 1.0);
        coord_out = transformed_pos;
        gl_Position = model_view_proj_mat * transformed_pos;
    }
    else
    {
        gl_Position = model_view_proj_mat * vec4(in_vertex.x, in_vertex.y, in_vertex.z, 1.0);
        coord_out = vec4(in_vertex.x, in_vertex.y, in_vertex.z, 1.0);
    }
    
    fragment_color = vertex_color;

    if(use_global_alpha == 1)
    {
        alpha_out = global_alpha;
    }
    else
    {
        alpha_out = alpha;
    }
}
